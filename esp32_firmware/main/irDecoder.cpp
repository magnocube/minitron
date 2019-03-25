#include "irDecoder.h"


void IrDecoder::setupSender()
{
	irSenderConfig.rmt_mode = RMT_MODE_TX;
	irSenderConfig.channel = RMT_CHANNEL_1;
	irSenderConfig.clk_div = 255;
	irSenderConfig.gpio_num = IR_LED_PIN;
	irSenderConfig.mem_block_num = 1;

	irSenderConfig.tx_config.loop_en = false;
	irSenderConfig.tx_config.carrier_freq_hz = 611;
	irSenderConfig.tx_config.carrier_duty_percent = 50;
	irSenderConfig.tx_config.carrier_level =  RMT_CARRIER_LEVEL_HIGH;
	irSenderConfig.tx_config.carrier_en = true;
	irSenderConfig.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
	irSenderConfig.tx_config.idle_output_en = 1;

	//ESP_ERROR_CHECK(rmt_config(&irSenderConfig));
	//ESP_ERROR_CHECK(rmt_driver_install(irSenderConfig.channel, 0, 0));

}
void IrDecoder::setupReceiver()
{
	irDecoderConfig.rmt_mode = RMT_MODE_RX;
	irDecoderConfig.channel = RMT_CHANNEL_0;
	irDecoderConfig.clk_div = 255;
	irDecoderConfig.gpio_num = IR_DECODER_PIN;
	irDecoderConfig.mem_block_num = 1;
	irDecoderConfig.rx_config.filter_en = true;
	irDecoderConfig.rx_config.filter_ticks_thresh = 255;
	irDecoderConfig.rx_config.idle_threshold = 20000 / 10 * ((80000000/100 /100000));
	ESP_ERROR_CHECK(rmt_config(&irDecoderConfig));
	ESP_ERROR_CHECK(rmt_driver_install(irDecoderConfig.channel, 2000, ESP_INTR_FLAG_IRAM));

	ESP_ERROR_CHECK(rmt_get_ringbuf_handle(irDecoderConfig.channel, &rxRingBuffer));
	ESP_ERROR_CHECK(rmt_rx_start(irDecoderConfig.channel, false));
	if (rxRingBuffer == NULL) {
        printf("Failed to create ring buffer\n");
    }

}
void IrDecoder::read()
{
	uint32_t startTime = esp_timer_get_time();
	size_t rx_size = 0;
	//try to receive data from ringbuffer.
	//RMT driver will push all the data it receives to its ringbuffer.
	//We just need to parse the value and return the spaces of ringbuffer.
	rmt_item32_t* item = (rmt_item32_t*) xRingbufferReceiveFromISR(rxRingBuffer, &rx_size);
	if(item) {
		received = true;
		// printf("received %zu\n", rx_size);
		// for(int i=0;i<rx_size;i++)
		// {
		// 	printf("(%d, %d , %d, %d) ", item[i].duration0, item[i].level0, item[i].duration1, item[i].level1);
		// }
		// printf("\n");
		vRingbufferReturnItem(rxRingBuffer, (void*) item);
	}
#ifdef PRINT_DURARIONS
	printf("- readtime: %llu\n",esp_timer_get_time()-startTime);
#endif

}
void IrDecoder::send()
{
	uint32_t startTime=esp_timer_get_time();
	ESP_ERROR_CHECK(rmt_driver_install(irSenderConfig.channel, 0, 0));

	size_t size = sizeof(rmt_item32_t)*10;
	rmt_item32_t* item = (rmt_item32_t*) malloc(size);
	for(int i=0;i<10;i++)
	{
		item[i].duration0=1000;
		item[i].level0=0;
		item[i].duration1=2000;
		item[i].level1=1;
	}

    ESP_ERROR_CHECK(rmt_write_items(RMT_CHANNEL_1, item, 10, false));
    timeUntilLedAvailable = esp_timer_get_time() + size * 8 * 30;
	free(item);
	ESP_ERROR_CHECK(rmt_driver_uninstall(irSenderConfig.channel));
#ifdef PRINT_DURARIONS
	printf("- sendTime: %llu\n",esp_timer_get_time()-startTime);
#endif
}
void IrDecoder::setupProximity()
{
	//set led pin
 	gpio_pad_select_gpio(IR_LED_PIN);
	gpio_set_direction(IR_LED_PIN, GPIO_MODE_OUTPUT);


	//configure adc 12bit max range
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(IR_PHOTODIODE1_PIN, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(IR_PHOTODIODE2_PIN, ADC_ATTEN_DB_11);
}
void IrDecoder::runProximity()
{
	if(esp_timer_get_time() < timeUntilLedAvailable) return;
	uint32_t startTime = esp_timer_get_time();

	//read without led
	int lowLevel1 = adc1_get_raw(IR_PHOTODIODE1_PIN);
	int lowLevel2 = adc1_get_raw(IR_PHOTODIODE2_PIN);

	//turn led on
    gpio_set_level(IR_LED_PIN, 1);

	//read with led
    int highLevel1 = adc1_get_raw(IR_PHOTODIODE1_PIN);
	int highLevel2 = adc1_get_raw(IR_PHOTODIODE2_PIN);

	//turn led off
    gpio_set_level(IR_LED_PIN, 0);

	//add measurements to buffer (to do aditional filtering later)
	left.lowBuffer[bufferIndex] = lowLevel1;
    left.highBuffer[bufferIndex] = highLevel1;
	right.lowBuffer[bufferIndex] = lowLevel2;
    right.highBuffer[bufferIndex] = highLevel2;

	bufferIndex++;
    if(bufferIndex == BUFFER_SIZE)
    {
    	bufferIndex = 0;
    }
	
	//do aditional filtering
	filterProximity(&left);
	filterProximity(&right);

	//save it in shared variables
	//the range is between 0 to 1000
    #define LEFT_DARK_CURRENT 190
	#define RIGHT_DARK_CURRENT 180
	sharedVariables->outputs.proximityLeft = (left.highBufferSort[1] - left.lowBufferSort[1] - LEFT_DARK_CURRENT)/3;
	sharedVariables->outputs.proximityLeft = std::max(0, sharedVariables->outputs.proximityLeft);
	sharedVariables->outputs.proximityLeft = std::min(sharedVariables->outputs.proximityLeft, 1000);
    sharedVariables->outputs.proximityRight = (right.highBufferSort[1] - right.lowBufferSort[1]-RIGHT_DARK_CURRENT)/3;
	sharedVariables->outputs.proximityRight = std::max(0, sharedVariables->outputs.proximityRight);
	sharedVariables->outputs.proximityRight = std::min(sharedVariables->outputs.proximityRight, 1000);

    sharedVariables->outputs.lightLeft = left.lowBufferSort[1]/4;
    sharedVariables->outputs.lightRight = right.lowBufferSort[1]/4;

#ifdef PRINT_PROXIMITY
	printf("%d\n", sharedVariables->outputs.proximityLeft);
#endif
#ifdef PRINT_DURARIONS
	printf("- proximityTime: %llu\n",esp_timer_get_time()-startTime);
#endif
#ifdef PRINT_PROXIMITY_ALL

	printf("%d, %d, 1200\n",right.highBufferSort[1], right.highBufferSort[1] - right.lowBufferSort[1]);
#endif
}

void IrDecoder::filterProximity(ProximitySensor* obj)//this method takes the best measurement out of the buffer as a kind of medium filter
{
	//copy the buffer into a sorted buffer
	for(int i=0;i<BUFFER_SIZE;i++)
	{
		obj->lowBufferSort[i] = obj->lowBuffer[i];
		obj->highBufferSort[i] = obj->highBuffer[i];
	}
	//sort the buffer
	for(int i=0;i<BUFFER_SIZE-1;i++)
	{
		for(int j = i+1;j<BUFFER_SIZE;j++)
		{
			if(obj->lowBufferSort[j]+obj->highBufferSort[j] < obj->lowBufferSort[i]+obj->highBufferSort[i])
			{
				int temp = obj->lowBufferSort[i];
				obj->lowBufferSort[i] = obj->lowBufferSort[j];
				obj->lowBufferSort[j] = temp;

				temp = obj->highBufferSort[i];
				obj->highBufferSort[i] = obj->highBufferSort[j];
				obj->highBufferSort[j] = temp;
			}	
		}
	}
	// if(received == true)
	// {
	// 	receiveStrength = lowBufferSort[BUFFER_SIZE-1]-lowBufferSort[0];
	// 	received = false;
	// }
	// else
	// {
	// 	receiveStrength = 0;
	// }
}