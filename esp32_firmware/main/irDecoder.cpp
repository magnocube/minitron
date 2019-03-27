#include "irDecoder.h"


void IrDecoder::setupSender()
{
	printf("setup ir sender\n");
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
	printf("setup ir receiver\n");
	irDecoderConfig.rmt_mode = RMT_MODE_RX;
	irDecoderConfig.channel = RMT_CHANNEL_0;
	irDecoderConfig.clk_div = 255;
	irDecoderConfig.gpio_num = IR_DECODER_PIN;
	irDecoderConfig.mem_block_num = 1;
	irDecoderConfig.rx_config.filter_en = true;
	irDecoderConfig.rx_config.filter_ticks_thresh = 150;
	irDecoderConfig.rx_config.idle_threshold = 3000;
	ESP_ERROR_CHECK(rmt_config(&irDecoderConfig));
	ESP_ERROR_CHECK(rmt_driver_install(irDecoderConfig.channel, 2000, 0));

	ESP_ERROR_CHECK(rmt_get_ringbuf_handle(irDecoderConfig.channel, &rxRingBuffer));
	ESP_ERROR_CHECK(rmt_rx_start(irDecoderConfig.channel, true));
	if (rxRingBuffer == NULL) {
        printf("Failed to create ring buffer\n");
    }

}
//for nec protocol reference
//https://www.sbprojects.net/knowledge/ir/nec.php
#define TICKS_TO_MS 1.0/(80.0/255.0)
#define MS_TO_TICKS (80.0/255.0)
bool IrDecoder::verifyReceivedData(rmt_item32_t* item)
{
	if((item[0].duration0*TICKS_TO_MS > 8500) && (item[0].duration0*TICKS_TO_MS < 9500))
	{
		#ifdef PRINT_IR_RECEIVE_VERBOSE
		printf("preamble 9ms verified\n");
		#endif
	}
	else
	{
		return false;
	}
	if((item[0].duration1 * TICKS_TO_MS > 4250) &&( item[0].duration1 * TICKS_TO_MS < 4750))
	{
		#ifdef PRINT_IR_RECEIVE_VERBOSE
		printf("preamble 4.5ms verified\n");
		#endif
	}
	else
	{
		return false;
	}
	return true;
	
}
uint8_t IrDecoder::translateByte(rmt_item32_t* item)
{
	uint8_t result = 0;
	for(int i=0;i<8;i++)
	{
		if((item[0].level0 == 1) || (item[0].level1 == 0)) //validation
		{
			#ifdef PRINT_IR_RECEIVE_VERBOSE
			printf("item can't have the same level\n");
			#endif
			return 0;
		}
		if((item[0].duration0 * TICKS_TO_MS < 400) || (item[0].duration0 * TICKS_TO_MS >800)) //validation
		{
			#ifdef PRINT_IR_RECEIVE_VERBOSE
			printf("high signal should be 560us\n");
			#endif
			return 0;
		}
		if(((item[0].duration0 + item[i].duration1) * TICKS_TO_MS > 1000) && ((item[i].duration0 + item[i].duration1) * TICKS_TO_MS < 1200))
		{
			#ifdef PRINT_IR_RECEIVE_VERBOSE
			printf("0 ");
			#endif
			result += 0<<i;
		}
		else if(((item[0].duration0 + item[i].duration1) * TICKS_TO_MS > 2000) && ((item[i].duration0 + item[i].duration1) * TICKS_TO_MS < 2500))
		{
			#ifdef PRINT_IR_RECEIVE_VERBOSE
			printf("1 ");
			#endif
			result += 1<<i;
		}
		else
		{
			#ifdef PRINT_IR_RECEIVE_VERBOSE
			printf("a bit should be between 1.12 and 2.25ms\n");
			#endif
			return 0;
		}
	}
	#ifdef PRINT_IR_RECEIVE_VERBOSE
	printf("\n");
	#endif
	return result;
}
void IrDecoder::read()
{
#ifdef PRINT_DURARIONS
	uint32_t startTime = esp_timer_get_time();
#endif
	size_t rx_size = 0;
	//try to receive data from ringbuffer.
	//RMT driver will push all the data it receives to its ringbuffer.
	//We just need to parse the value and return the spaces of ringbuffer.
	rmt_item32_t* item = (rmt_item32_t*) xRingbufferReceiveFromISR(rxRingBuffer, &rx_size);
	if(item) {
		 
		#ifdef PRINT_IR_RECEIVE_VERBOSE
		 printf("received %zu\n", rx_size);
		#endif
		 if(rx_size > 132)//4*(1+4*8)
		 {
			#ifdef PRINT_IR_RECEIVE_VERBOSE
			for(int i=0;i<rx_size;i++)
			{
				printf("(%f, %d , %f, %d) ", item[i].duration0 * TICKS_TO_MS, item[i].level0, item[i].duration1 * TICKS_TO_MS, item[i].level1);
			}
			printf("\n");
			#endif
			if(verifyReceivedData(item))
			{
				uint8_t address = translateByte(item+1);
				uint8_t invert_address = translateByte(item+9);
				uint8_t command = translateByte(item+17);
				uint8_t invert_command = translateByte(item+25);
				#ifdef PRINT_IR_RECEIVE_VERBOSE
				if(address != 255-invert_address)
				{
					printf("inverted address doesn't match, probably this is extended NEC\n");
				}
				#endif
				#ifdef PRINT_IR_RECEIVE
				if(command == 255 - invert_command)
				{
					printf("address: %hhu command: %hhu\n", address, command);
					sharedVariables->outputs.irLastAddress = address;
					sharedVariables->outputs.irLastCommand = command;
					sharedVariables->outputs.irFlowNumber++;
				}
				else
				{
					printf("error, inverted command doesn't match\n");
				}
				#endif
				
			}
			
		 }
		vRingbufferReturnItemFromISR(rxRingBuffer, (void*) item, NULL);
	}
#ifdef PRINT_DURARIONS
	printf("- readtime: %llu\n",esp_timer_get_time()-startTime);
#endif
}
void IrDecoderWriteByte(rmt_item32_t* item, uint8_t value)
{
	for(int i=0;i<8;i++)
	{
		item[i].duration0 = 560 * MS_TO_TICKS;
		item[i].level0 = 0;
		item[i].level1 = 1;
		if(((value>>i) & BIT0) == 0) //logic 0
		{
			item[i].duration1 = 560 * MS_TO_TICKS;
		}
		else // logic 1
		{
			item[i].duration1 = 1572 * MS_TO_TICKS;
		}
	}
}
void IrDecoder::send()
{
	if(esp_timer_get_time() < timeUntilLedAvailable) return;
#ifdef PRINT_DURARIONS
	uint32_t startTime=esp_timer_get_time();
#endif
	ESP_ERROR_CHECK(rmt_driver_install(irSenderConfig.channel, 0, 0));

	int items = 1+8*4;
	size_t size = sizeof(rmt_item32_t)*(items);
	rmt_item32_t* item = (rmt_item32_t*) malloc(size);
	
	item[0].duration0 = 9000 * MS_TO_TICKS;
	item[0].level0 = 0;
	item[0].duration1 = 4500 * MS_TO_TICKS;
	item[0].level1 = 1;
	uint8_t address = 10;
	uint8_t command = 100;
	IrDecoderWriteByte(item + 1, address);
	IrDecoderWriteByte(item + 9, 255 - address);
	IrDecoderWriteByte(item + 17, command);
	IrDecoderWriteByte(item + 25, 255 - command);

    ESP_ERROR_CHECK(rmt_write_items(RMT_CHANNEL_1, item, 10, false));
	#ifdef PRINT_IR_SEND
		printf("ir address: %hhu command %hhu sended\n", address, command);
	#endif
    timeUntilLedAvailable = esp_timer_get_time() + size * 8 * 30;
	free(item);
	ESP_ERROR_CHECK(rmt_driver_uninstall(irSenderConfig.channel));
#ifdef PRINT_DURARIONS
	printf("- sendTime: %llu\n",esp_timer_get_time()-startTime);
#endif
}
void IrDecoder::setupProximity()
{
	printf("setup proximity\n");
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
#ifdef PRINT_DURARIONS
	uint32_t startTime = esp_timer_get_time();
#endif

	//read without led
	int lowLevel1 = adc1_get_raw(IR_PHOTODIODE1_PIN);
	int lowLevel2 = adc1_get_raw(IR_PHOTODIODE2_PIN);

	
	//turn led on
    gpio_set_level(IR_LED_PIN, 1);

	uint32_t startTime = esp_timer_get_time();
	while(esp_timer_get_time() - startTime < 100);
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
    #define LEFT_DARK_CURRENT 220
	#define RIGHT_DARK_CURRENT 200
	sharedVariables->outputs.proximityLeft = (left.highBufferSort[1] - left.lowBufferSort[1] - LEFT_DARK_CURRENT);
	sharedVariables->outputs.proximityLeft = std::max(0, sharedVariables->outputs.proximityLeft);
	sharedVariables->outputs.proximityLeft = std::min(sharedVariables->outputs.proximityLeft, 1000);
    sharedVariables->outputs.proximityRight = (right.highBufferSort[1] - right.lowBufferSort[1]-RIGHT_DARK_CURRENT);
	sharedVariables->outputs.proximityRight = std::max(0, sharedVariables->outputs.proximityRight);
	sharedVariables->outputs.proximityRight = std::min(sharedVariables->outputs.proximityRight, 1000);

    sharedVariables->outputs.lightLeft = left.lowBufferSort[1];
    sharedVariables->outputs.lightRight = right.lowBufferSort[1];

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