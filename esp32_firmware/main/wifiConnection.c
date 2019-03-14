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
#define EXAMPLE_WIFI_SSID "minitron1"
#define EXAMPLE_WIFI_PASS "minitron1"

#define HOST_IP_ADDR "192.168.137.1"

static const char *WIFI_TAG = "example";
#define PORT 4210

/* FreeRTOS event group to signal when we are connected & ready to make a request */
static EventGroupHandle_t wifi_event_group;

const int IPV4_GOTIP_BIT = BIT0;
const int IPV6_GOTIP_BIT = BIT1;

static const char *payload = "Message from ESP32 ";

char rx_buffer[1460];
char addr_str[128];
int addr_family;
int ip_protocol;
static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        ESP_LOGI(WIFI_TAG, "SYSTEM_EVENT_STA_START");
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        /* enable ipv6 */
        tcpip_adapter_create_ip6_linklocal(TCPIP_ADAPTER_IF_STA);
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, IPV4_GOTIP_BIT);
        ESP_LOGI(WIFI_TAG, "SYSTEM_EVENT_STA_GOT_IP");
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
        ESP_LOGI(WIFI_TAG, "SYSTEM_EVENT_STA_GOT_IP6");

        char *ip6 = ip6addr_ntoa(&event->event_info.got_ip6.ip6_info.ip);
        ESP_LOGI(WIFI_TAG, "IPv6: %s", ip6);
    }
    default:
        break;
    }
    return ESP_OK;
}
    static void initialise_wifi(void)
    {
        tcpip_adapter_init();
        wifi_event_group = xEventGroupCreate();
        ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
        ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
        wifi_config_t wifi_config;

        for(int i=0;i<8;i++)
        {
            wifi_config.sta.ssid[i] = (uint8_t)EXAMPLE_WIFI_SSID[i];
            wifi_config.sta.password[i] = (uint8_t)EXAMPLE_WIFI_PASS[i];
        }
        wifi_config.sta.ssid[8] = 0;
        wifi_config.sta.password[8] = 0;
        wifi_config.sta.bssid_set = 0;
        wifi_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;

        wifi_config.sta.threshold.rssi = -127;
        wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
        wifi_config.sta.listen_interval = 3; // this is the main setting, 3 is lowest

        ESP_LOGI(WIFI_TAG, "Setting WiFi configuration SSID %s...", wifi_config.sta.ssid);
        ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
        ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
        ESP_ERROR_CHECK( esp_wifi_start() );
    }

static void wait_for_ip()
{
    printf("wait for ip\n");
    uint32_t bits = IPV4_GOTIP_BIT | IPV6_GOTIP_BIT ;

    ESP_LOGI(WIFI_TAG, "Waiting for AP connection...");
    xEventGroupWaitBits(wifi_event_group, bits, false, true, portMAX_DELAY);
    ESP_LOGI(WIFI_TAG, "Connected to AP");
    printf("got ip\n");
}
int udp_server;
static uint8_t setupUDP()
{
        printf("setup udp \n");
        //stop();

        //tx_buffer = new char[100];
        // if(!tx_buffer){
        //     printf("could not create tx buffer\n");
        //     return 0;
        // }

        if ((udp_server=socket(AF_INET, SOCK_DGRAM, 0)) == -1){
            printf("could not create socket\n");
            return 0;
        }

        int yes = 1;
        if (setsockopt(udp_server,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
            printf("could not set socket option\n");
            //stop();
            return 0;
        }

        struct sockaddr_in addr;
        memset((char *) &addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = INADDR_ANY;
        if(bind(udp_server , (struct sockaddr*)&addr, sizeof(addr)) == -1){
            printf("could not bind socket\n");
            //stop();
            return 0;
        }
        fcntl(udp_server, F_SETFL, O_NONBLOCK);
        return 1;
}
int readUDP(uint8_t* dataBuffer)
{
  struct sockaddr_in si_other;
  int slen = sizeof(si_other) , len;

  if ((len = recvfrom(udp_server, dataBuffer, 1460, MSG_DONTWAIT, (struct sockaddr *) &si_other, (socklen_t *)&slen)) == -1){
    if(errno == EWOULDBLOCK){
      return -1;
    }
    return 0;
  }
  return len;
}
uint8_t incomingPacket[1460];
void wifiLoop()
{
        printf(".");
        int len  = readUDP(incomingPacket);
        if(len > 0)
        {
            printf("received\n");
        }
        //     int err = sendto(sock, payload, strlen(payload), 0, (struct sockaddr *)&destAddr, sizeof(destAddr));
        //     if (err < 0) {
        //         printf("Error occured during sending: errno %d\n", errno);
        //         break;
        //     }
        //     printf("Message sent\n");

        //      // Large enough for both IPv4 or IPv6
        //     struct sockaddr_in sourceAddr; // Large enough for both IPv4 or IPv6
        //     socklen_t socklen = sizeof(sourceAddr);
        //     int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, MSG_DONTWAIT, (struct sockaddr *)&sourceAddr, &socklen);

        //     // Error occured during receiving
        //     if (len < 0) {
        //         printf("recvfrom failed: errno %d\n", errno);
                
        //     }
        //     // Data received
        //     else {
        //         rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
        //         printf("Received %d bytes from %s:\n", len, addr_str);
        //         printf("%s", rx_buffer);
        //     }

        //     vTaskDelay(2000 / portTICK_PERIOD_MS);

        // if (sock != -1) {
        //     printf("Shutting down socket and restarting...\n");
        //     shutdown(sock, 0);
        //     close(sock);
        // }

}

void wifiSetup()
{

    ESP_ERROR_CHECK( nvs_flash_init() );
    initialise_wifi();
    wait_for_ip();
    setupUDP();
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


