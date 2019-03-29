#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"


#include "pins.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "sharedVariables.h"

#define FORWARD_MOTOR_1 1
#define BACKWARD_MOTOR_1 0
#define FORWARD_MOTOR_2 0
#define BACKWARD_MOTOR_2 1



// the stepper is by default always in 1/16 microstepping.. this can be changed in the software. but it seems it would heave no use
class MotorDriver
{	
public:	
    SharedVariables* sharedVariables;
	Steppers* steppers;
	MotorDriver(SharedVariables& _sharedVariables)
	{
		sharedVariables = &_sharedVariables;
		steppers = &sharedVariables->outputs.steppers;
	}
	void setup();	
	void setAcceleration(uint32_t a, uint32_t a2);
	void setAcceleration(uint32_t aceleration);
	void calculateInduvidualAcceleration();
	void setTargetSpeed(int32_t motor1, int32_t motor2);
	void loop();
	void setSpeed(int32_t motor1, int32_t motor2);
	void setMotorDriverEnabled(bool b);

	bool isMotorDriverEnabled();
	int32_t getMotor1TargetSpeed();
	int32_t getMotor2TargetSpeed();
	int32_t getMotor1Speed();
	int32_t getMotor2Speed();
	uint32_t currentAcceleration=0;

	//todo:
	//void moveToXY();
	//void moveBackToStart();

private:
	ledc_timer_config_t ledc_timer_motor_1;
	ledc_timer_config_t ledc_timer_motor_2;

    double motor1Speed;				//current motorspeed
    double motor2Speed;				//current motorspeed

	double motor1OldSpeed;
	double motor2OldSpeed;
	uint64_t lastTimeSincePreviousLoop; //used for calculating the delta-T for the acceleration

};
