#include "irDecoder.h"

void IrDecoder::setupSender()
{
	irSenderConfig.rmt_mode = RMT_MODE_TX;
	irSenderConfig.channel = RMT_CHANNEL_1;
	irSenderConfig.clk_div = 255;
	irSenderConfig.gpio_num = IR_LED1_PIN;
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
	irDecoderConfig.rx_config.filter_ticks_thresh = 100;
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
	uint32_t startTime = micros();
	size_t rx_size = 0;
	//try to receive data from ringbuffer.
	//RMT driver will push all the data it receives to its ringbuffer.
	//We just need to parse the value and return the spaces of ringbuffer.
	rmt_item32_t* item = (rmt_item32_t*) xRingbufferReceiveFromISR(rxRingBuffer, &rx_size);
	if(item) {
		received = true;
		printf("received %zu\n", rx_size);
		for(int i=0;i<rx_size;i++)
		{
			printf("(%d, %d , %d, %d) ", item[i].duration0, item[i].level0, item[i].duration1, item[i].level1);
		}
		printf("\n");
		vRingbufferReturnItem(rxRingBuffer, (void*) item);
	}
#ifdef PRINT_DURARIONS
	printf("- readtime: %lu\n",micros()-startTime);
#endif

}
void IrDecoder::send()
{
	uint32_t startTime=micros();
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
    timeUntilLedAvailable = micros() + size * 8 * 30;
	free(item);
	ESP_ERROR_CHECK(rmt_driver_uninstall(irSenderConfig.channel));
#ifdef PRINT_DURARIONS
	printf("- sendTime: %lu\n",micros()-startTime);
#endif
}
void IrDecoder::setupProximity()
{
	pinMode(IR_LED1_PIN,OUTPUT);

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(IR_PHOTODIODE1_PIN, ADC_ATTEN_DB_6);
}
void IrDecoder::runProximity()
{
	if(micros() < timeUntilLedAvailable) return;
	uint32_t startTime = micros();



    int lowLevel =0;//= adc1_get_raw(IR_PHOTODIODE1_PIN);
    digitalWrite(IR_LED1_PIN, HIGH);
    int highLevel =0;//= adc1_get_raw(IR_PHOTODIODE1_PIN);
    digitalWrite(IR_LED1_PIN, LOW);

    lowBuffer[bufferIndex] = lowLevel;
    highBuffer[bufferIndex] = highLevel;
    bufferIndex++;
    if(bufferIndex == BUFFER_SIZE)
    {
    	bufferIndex = 0;
    }
#ifdef PRINT_DURARIONS
	printf("- proximityTime: %lu\n",micros()-startTime);
#endif
#ifdef PRINT_PROXIMITY
	printf("%d\n", highLevel-lowLevel);
#endif
#ifdef PRINT_PROXIMITY_ALL
	// if(oldHighLevel<highLevel)
	// {
	// 	printf("%d,%d,%d,1200\n",oldLowLevel,oldHighLevel,(oldHighLevel-oldLowLevel));
	// }
	// else
	// {
	// 	printf("%d,%d,%d,1200\n",lowLevel,highLevel,(highLevel-lowLevel));
	// }
	// oldLowLevel = lowLevel;
	// oldHighLevel = highLevel;

	for(int i=0;i<BUFFER_SIZE;i++)
	{
		lowBufferSort[i] = lowBuffer[i];
		highBufferSort[i] = highBuffer[i];
	}
	for(int i=0;i<BUFFER_SIZE-1;i++)
	{
		for(int j = i+1;j<BUFFER_SIZE;j++)
		{
			if(lowBufferSort[j]+highBufferSort[j] < lowBufferSort[i]+highBufferSort[i])
			{
				int temp = lowBufferSort[i];
				lowBufferSort[i] = lowBufferSort[j];
				lowBufferSort[j] = temp;

				temp = highBufferSort[i];
				highBufferSort[i] = highBufferSort[j];
				highBufferSort[j] = temp;
			}
		}
	}
	if(received == true)
	{
		receiveStrength = (highBufferSort[BUFFER_SIZE] + highBufferSort[0]);
	}
	else
	{
		receiveStrength = 0;
	}
	printf("%d,%d,%d, %d,1200\n",lowBufferSort[0],highBufferSort[0],(highBufferSort[0]+highBufferSort[0]), receiveStrength);


  
#endif
}