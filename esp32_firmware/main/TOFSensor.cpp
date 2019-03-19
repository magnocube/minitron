#include "TOFSensor.h"

void TOFSensor::init()
{
	/* initialization */
	sharedVariables.TOFSensorWorking = vl->init();
	vl->startContinuous();
}
void TOFSensor::measure()
{
	if(sharedVariables.TOFSensorWorking == false)return;
		uint32_t startTime = esp_timer_get_time();
		bool res = vl->readContinous(&sharedVariables.TOFSensorDistanceMM);

#ifdef PRINT_TOF_SENSOR
		if (res){
			uint32_t took_ms = esp_timer_get_time() - startTime;
		  printf("Range: %d [mm] took %u  [us]\n", (int)sharedVariables.TOFSensorDistanceMM, took_ms);
		}
		else{
		  printf("Failed to measure :(\n");
		}		
#endif
}