#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>


boolean connected;

WiFiUDP udp;

const char * networkName = "povGlobe";
const char * networkPswd = "povGlobe";

const char * udpAddress = "192.168.0.255";
const int udpPort = 3333;

void connect(const char * ssid, const char * pwd)
{
  printf("Connecting to WiFi network: %s/n", ssid);

  //register event handler
  //WiFi.onEvent(WiFiEvent);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);
  printf("Waiting for WIFI connection...\n");
}
void WiFiEvent(WiFiEvent_t event)
{
        switch(event) {
        case SYSTEM_EVENT_STA_GOT_IP:
        {
            //When connected set 
            IPAddress ip = WiFi.localIP();
            printf("%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
            //initializes the UDP state
            //This initializes the transfer buffer
            udp.begin(WiFi.localIP(), udpPort);
            connected = true;
            break;
        }
        case SYSTEM_EVENT_STA_DISCONNECTED:
            printf("WiFi lost connection\n");
            connected = false;
            break;
        default:
            break;
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
        udp.beginPacket(udpAddress,udpPort);
        udp.printf("Seconds since boot: %lu", millis()/1000);
        udp.endPacket();
    }
}



