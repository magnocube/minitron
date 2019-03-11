#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "pins.h"
#include "driver/ledc.h"




class MotorDriver
{	
public:	
	void setup();	
	void setMicroSteppingAutomaticly(bool boolean);
    void setMicroStepping(uint8_t microstep);
	void setSpeed(uint16_t motor1, uint16_t motor2);
	void loop();

private:
    uint16_t motor1Speed;
    uint16_t motor2Speed;
	uint8_t microstep;

};
