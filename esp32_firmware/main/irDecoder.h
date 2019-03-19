#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/ringbuf.h"
#include "driver/rmt.h"

#include "driver/ledc.h"

#include <rom/ets_sys.h>
#include <driver/adc.h>
#include "math.h"
#include <algorithm>
#include "pins.h"
#include "settings.h"
#include "sharedVariables.h"
#define BUFFER_SIZE 5//larger buffer will filter better, but slow down to reaction speed

class IrDecoder
{
	int bufferIndex = 0;
	struct ProximitySensor
	{
		int lowBuffer[BUFFER_SIZE];
		int highBuffer[BUFFER_SIZE];
		int lowBufferSort[BUFFER_SIZE];
		int highBufferSort[BUFFER_SIZE];
	}left,right;
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
	SharedVariables* sharedVariables;
	IrDecoder(SharedVariables& _sharedVariables)
	{
		sharedVariables = &_sharedVariables;
	}
	void setup()
	{
		setupSender();
		setupReceiver();
		setupProximity();
	}
	void read();
	void send();
	void runProximity();
	void calculateProximity(ProximitySensor* obj);
};
