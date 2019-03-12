#include "TOFSensor.h"

void TOFSensor::init()
{
	/* initialization */
	vl->init();
	vl->startContinuous();
}
void TOFSensor::measure()
{
	    vTaskDelay(50 / portTICK_PERIOD_MS);

		uint16_t result_mm = 0;
		uint32_t startTime = esp_timer_get_time();
		bool res = vl->readContinous(&result_mm);
		uint32_t took_ms = esp_timer_get_time() - startTime;

#ifdef PRINT_TOF_SENSOR
		if (res){
		  printf("Range: %d [mm] took %u  [us]\n", (int)result_mm, took_ms);
		}
		else{
		  printf("Failed to measure :(\n");
		}		
#endif
}