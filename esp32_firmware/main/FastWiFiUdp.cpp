/*
  Udp.cpp - UDP class for Raspberry Pi
  Copyright (c) 2016 Hristo Gochkov  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "FastWiFiUDP.h"

#undef write
#undef read

FastWiFiUDP::FastWiFiUDP()
: udp_server(-1)
, server_port(0)
, remote_port(0)
, tx_buffer(0)
, tx_buffer_len(0)
{}


uint8_t FastWiFiUDP::begin(IPAddress address, uint16_t port){

  server_port = port;

  tx_buffer = new char[100];
  if(!tx_buffer){
    printf("could not create tx buffer: %d", errno);
    return 0;
  }

  if ((udp_server=socket(AF_INET, SOCK_DGRAM, 0)) == -1){
    printf("could not create socket: %d", errno);
    return 0;
  }

  int yes = 1;
  if (setsockopt(udp_server,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
      printf("could not set socket option: %d", errno);
      return 0;
  }

  struct sockaddr_in addr;
  memset((char *) &addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(server_port);
  addr.sin_addr.s_addr = (in_addr_t)address;
  if(bind(udp_server , (struct sockaddr*)&addr, sizeof(addr)) == -1){
    printf("could not bind socket: %d", errno);
    return 0;
  }
  fcntl(udp_server, F_SETFL, O_NONBLOCK);
  return 1;
}

uint8_t FastWiFiUDP::begin(uint16_t p){
  return begin(IPAddress(INADDR_ANY), p);
}


int FastWiFiUDP::beginPacket(){
  if(!remote_port)
    return 0;

  // allocate tx_buffer if is necessary
  if(!tx_buffer){
    tx_buffer = new char[1460];
    if(!tx_buffer){
      printf("could not create tx buffer: %d", errno);
      return 0;
    }
  }

  tx_buffer_len = 0;

  // check whereas socket is already open
  if (udp_server != -1)
    return 1;

  if ((udp_server=socket(AF_INET, SOCK_DGRAM, 0)) == -1){
    printf("could not create socket: %d", errno);
    return 0;
  }

  fcntl(udp_server, F_SETFL, O_NONBLOCK);

  return 1;
}

int FastWiFiUDP::beginPacket(IPAddress ip, uint16_t port){
  remote_ip = ip;
  remote_port = port;
  return beginPacket();
}

int FastWiFiUDP::beginPacket(const char *host, uint16_t port){
  struct hostent *server;
  server = gethostbyname(host);
  if (server == NULL){
    printf("could not get host from dns: %d", errno);
    return 0;
  }
  return beginPacket(IPAddress((const uint8_t *)(server->h_addr_list[0])), port);
}

int FastWiFiUDP::endPacket(){
  struct sockaddr_in recipient;
  recipient.sin_addr.s_addr = (uint32_t)remote_ip;
  recipient.sin_family = AF_INET;
  recipient.sin_port = htons(remote_port);
  int sent = sendto(udp_server, tx_buffer, tx_buffer_len, 0, (struct sockaddr*) &recipient, sizeof(recipient));
  if(sent < 0){
    printf("could not send data: %d", errno);
    return 0;
  }
  return 1;
}

size_t FastWiFiUDP::write(uint8_t data){
  if(tx_buffer_len == 1460){
    endPacket();
    tx_buffer_len = 0;
  }
  tx_buffer[tx_buffer_len++] = data;
  return 1;
}

size_t FastWiFiUDP::write(const uint8_t *buffer, size_t size){
  size_t i;
  for(i=0;i<size;i++)
    write(buffer[i]);
  return i;
}

int FastWiFiUDP::myRead(uint8_t* dataBuffer){
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
