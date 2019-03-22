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

#include "settings.h"
#include "sharedVariables.h"
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


char addr_str[128];
int addr_family;
int ip_protocol;

extern SharedVariables sharedVariables;

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        printf("SYSTEM_EVENT_STA_START\n");
        break;
    case SYSTEM_EVENT_STA_CONNECTED:
        /* enable ipv6 */
        tcpip_adapter_create_ip6_linklocal(TCPIP_ADAPTER_IF_STA);
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, IPV4_GOTIP_BIT);
        printf("SYSTEM_EVENT_STA_GOT_IP\n");
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
        printf("SYSTEM_EVENT_STA_GOT_IP6\n");

        char *ip6 = ip6addr_ntoa(&event->event_info.got_ip6.ip6_info.ip);
        printf("IPv6: %s\n", ip6);
    }
    default:
        break;
    }
    return ESP_OK;
}
    static void initialise_wifi(void)
    {
        tcpip_adapter_init();
        tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP);

        tcpip_adapter_ip_info_t ip_info;
        IP4_ADDR(&ip_info.ip,192,168,1,99);
        IP4_ADDR(&ip_info.gw,192,168,1,1);
        IP4_ADDR(&ip_info.netmask,255,255,255,0);
        printf("set ip ret: %d\n", tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &ip_info)); //set static IP

        tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP);



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
        //set the \0 terminator
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
            return 0;
        }

        struct sockaddr_in addr;
        memset((char *) &addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = INADDR_ANY;
        if(bind(udp_server , (struct sockaddr*)&addr, sizeof(addr)) == -1){
            printf("could not bind socket\n");
            return 0;
        }
        fcntl(udp_server, F_SETFL, O_NONBLOCK);
        return 1;
}

    struct sockaddr_in si_other;
    int slen = sizeof(si_other);

#define rx_buffer_len 512
uint8_t rx_buffer[512];
bool udpReceived = false;
int readUDP()
{

    int len=0;
  if ((len = recvfrom(udp_server, rx_buffer, rx_buffer_len, MSG_DONTWAIT, (struct sockaddr *) &si_other, (socklen_t *)&slen)) == -1){
     if(errno == EWOULDBLOCK){
       return -1;
     }   
     return 0;
    }
    //receive serialized sharedvariables struct
  memcpy((void*)&sharedVariables.inputs, rx_buffer, sizeof(sharedVariables.inputs));
  udpReceived = true;
  return 1;
}
int tx_buffer_len = sizeof(sharedVariables.outputs);
uint8_t tx_buffer[sizeof(sharedVariables.outputs)];

int sendUDP()
{
    if(si_other.sin_addr.s_addr == 0)
    {
        printf("missing ip\n");
        return 0;
    }
    struct sockaddr_in recipient;
    recipient.sin_addr.s_addr = si_other.sin_addr.s_addr;
    recipient.sin_family = AF_INET;
    recipient.sin_port = htons(PORT);
    //send serialized sharedvariables struct
    int sent = sendto(udp_server, reinterpret_cast<char*>(&sharedVariables.outputs), tx_buffer_len, MSG_DONTWAIT, (struct sockaddr*) &recipient, sizeof(recipient));
    if(sent < 0){
        printf("could not send data\n");
        return 0;
    }
    return 1;
}
void wifiLoop()
{
        int len  = readUDP();
        if(len > 0)
        {
            #ifdef PRINT_WIFI
                printf("udp message received succesfully\n");
            #endif
        }
        if(sendUDP())
        {
            #ifdef PRINT_WIFI
                printf("udp message sended succesfully\n");
            #endif
        }
}

void wifiSetup()
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    initialise_wifi();
    wait_for_ip();
    setupUDP();
}
