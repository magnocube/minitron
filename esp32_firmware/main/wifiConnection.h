/* BSD Socket API Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>


/* The examples use simple WiFi configuration that you can set via
   'make menuconfig'.
   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
uint8_t EXAMPLE_WIFI_SSID[32];
uint8_t EXAMPLE_WIFI_PASS[64];

#define HOST_IP_ADDR "192.168.137.122"


#define PORT 4210

/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t wifi_event_group;

const int IPV4_GOTIP_BIT = BIT0;
const int IPV6_GOTIP_BIT = BIT1;

static const char *payload = "Message from ESP32 ";

char rx_buffer[128];
char addr_str[128];
int addr_family;
int ip_protocol;
static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        ESP_LOGI(TAG, "SYSTEM_EVENT_STA_START");
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        /* enable ipv6 */
        tcpip_adapter_create_ip6_linklocal(TCPIP_ADAPTER_IF_STA);
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, IPV4_GOTIP_BIT);
        ESP_LOGI(TAG, "SYSTEM_EVENT_STA_GOT_IP");
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently auto-reassociate. */
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, IPV4_GOTIP_BIT);
        xEventGroupClearBits(wifi_event_group, IPV6_GOTIP_BIT);
        break;
    case SYSTEM_EVENT_AP_STA_GOT_IP6:
    {
        xEventGroupSetBits(wifi_event_group, IPV6_GOTIP_BIT);
        ESP_LOGI(TAG, "SYSTEM_EVENT_STA_GOT_IP6");

        char *ip6 = ip6addr_ntoa(&event->event_info.got_ip6.ip6_info.ip);
        ESP_LOGI(TAG, "IPv6: %s", ip6);
    }
    default:
        break;
    }
    return ESP_OK;
}

static void initialise_wifi(void)
{
    printf("init wifi\n");
    tcpip_adapter_init();
    printf("adapter init\n");
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    printf("inited conf default\n");
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    printf("set storage\n");
    wifi_config_t wifi_config; 
    printf("wifi config\n");
    memcpy(wifi_config.sta.ssid,EXAMPLE_WIFI_SSID,32);
    memcpy(wifi_config.sta.password,EXAMPLE_WIFI_PASS,64);
    wifi_config.sta.scan_method = wifi_scan_method_t::WIFI_ALL_CHANNEL_SCAN;
    wifi_config.sta.bssid_set = 0;
    wifi_config.sta.channel = 0;
    wifi_config.sta.listen_interval = 0;
    printf("memcpy\n");

    ESP_LOGI(TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
        printf("mode\n");

    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );

    printf("start\n");
}

static void wait_for_ip()
{
    printf("wait for ip\n");
    uint32_t bits = IPV4_GOTIP_BIT | IPV6_GOTIP_BIT ;

    ESP_LOGI(TAG, "Waiting for AP connection...");
    xEventGroupWaitBits(wifi_event_group, bits, false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connected to AP");
    printf("got ip\n");
}

static void wifiLoop()
{
        printf("loop wifi\n");
        struct sockaddr_in destAddr;
        destAddr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
        destAddr.sin_family = AF_INET;
        destAddr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;
        inet_ntoa_r(destAddr.sin_addr, addr_str, sizeof(addr_str) - 1);


        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
           return;
        }
        ESP_LOGI(TAG, "Socket created");

        while (1) {

            int err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&destAddr, sizeof(destAddr));
            if (err < 0) {
                ESP_LOGE(TAG, "Error occured during sending: errno %d", errno);
                break;
            }
            ESP_LOGI(TAG, "Message sent");

            struct sockaddr_in sourceAddr; // Large enough for both IPv4 or IPv6
            socklen_t socklen = sizeof(sourceAddr);
            int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&sourceAddr, &socklen);

            // Error occured during receiving
            if (len < 0) {
                ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
                break;
            }
            // Data received
            else {
                rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                ESP_LOGI(TAG, "Received %d bytes from %s:", len, addr_str);
                ESP_LOGI(TAG, "%s", rx_buffer);
            }

            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }

        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }

}

void wifiSetup()
{
    esp_log_level_set(TAG,ESP_LOG_VERBOSE);
    memcpy(EXAMPLE_WIFI_SSID,"povGlobe",11);
    memcpy(EXAMPLE_WIFI_PASS,"povGlobe",11);
    for(int i=0;i<32;i++)
    {
        printf("%u ",EXAMPLE_WIFI_SSID[i]);
    }
    ESP_ERROR_CHECK( nvs_flash_init() );
    initialise_wifi();
    wait_for_ip();
}








/*#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


boolean connected;

WiFiUDP udp;

const char * networkName = "povGlobe";
const char * networkPswd = "povGlobe";

const int udpPort = 4210;


void connect(const char * ssid, const char * pwd)
{
    Serial.begin(115200);
      Serial.setDebugOutput(true);
  printf("Connecting to WiFi network: %s\n", ssid);

  // delete old config
  WiFi.disconnect(true);
  
    WiFi.begin(ssid, pwd);

    while (WiFi.status() != WL_CONNECTED){
        vTaskDelay(100);
        printf(".");
    }
    printf("connected\n");
    connected=true;
    if(!udp.begin(udpPort))
    {
      Serial.printf("error starting udp \n");
    }
}
void wifiSetup()
{
    connect(networkName, networkPswd);
}
void wifiLoop()
{
    if(connected){
        //Send a packet
        printf("%d\n",udp.available());
    }
}*/



