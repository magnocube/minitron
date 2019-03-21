#ifndef _FASTWIFIUDP_H_
#define _FASTWIFIUDP_H_
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
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <errno.h>
#include "IPAddress.h"
class FastWiFiUDP {
private:
  int udp_server;
  IPAddress multicast_ip;
  IPAddress remote_ip;
  uint16_t server_port;
  uint16_t remote_port;
  char * tx_buffer;
  size_t tx_buffer_len;
public:
  FastWiFiUDP();
  uint8_t begin(IPAddress a, uint16_t p);
  uint8_t begin(uint16_t p);
  int beginPacket();
  int beginPacket(IPAddress ip, uint16_t port);
  int beginPacket(const char *host, uint16_t port);
  int endPacket();
  size_t write(uint8_t);
  size_t write(const uint8_t *buffer, size_t size);

  int myRead(uint8_t* dataBuffer);

};

#endif /* _FASTWIFIUDP_H_ */
