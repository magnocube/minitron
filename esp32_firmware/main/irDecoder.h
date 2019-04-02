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
#define BUFFER_SIZE 2//larger buffer will filter better, but slow down to reaction speed

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
    int receiveStrength=0;
	uint32_t timeUntilLedAvailable = 0;//in ms

	rmt_config_t irDecoderConfig;
	rmt_config_t irSenderConfig;
	RingbufHandle_t rxRingBuffer = NULL;

	uint8_t lastFlowNumber = 0;

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
	uint8_t translateByte(rmt_item32_t* item);
	int findPreamble(rmt_item32_t* item, int size);
	void read();
	void send();
	void runProximity();
	void filterProximity(ProximitySensor* obj);

};
