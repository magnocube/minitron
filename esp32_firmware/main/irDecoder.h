#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include "FreeRTOS.h"
#include "freertos/ringbuf.h"
#include "driver/rmt.h"

#include "driver/ledc.h"

#include "Arduino.h"
#include <rom/ets_sys.h>
#include <driver/adc.h>

#include "pins.h"
#include "settings.h"
#include "freertos/ringbuf.h"
#define BUFFER_SIZE 15

class IrDecoder
{

	int bufferIndex = 0;
    int lowBuffer[BUFFER_SIZE];
    int highBuffer[BUFFER_SIZE];
	int lowBufferSort[BUFFER_SIZE];
    int highBufferSort[BUFFER_SIZE];

    bool received = false;
    int receiveStrength=0;
	uint32_t timeUntilLedAvailable = 0;//in ms

	rmt_config_t irDecoderConfig;
	rmt_config_t irSenderConfig;
	RingbufHandle_t rxRingBuffer = NULL;


	void setupReceiver();
	void setupSender();
	void setupProximity();
public:
	
	void setup()
	{
		setupSender();
		setupReceiver();
		setupProximity();
	}
	void read();
	void send();
	void runProximity();
};
