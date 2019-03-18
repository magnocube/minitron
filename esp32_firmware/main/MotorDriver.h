#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"


#include "pins.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define FORWARD_MOTOR_1 0
#define BACKWARD_MOTOR_1 1
#define FORWARD_MOTOR_2 1
#define BACKWARD_MOTOR_2 0



// the stepper is by default always in 1/16 microstepping.. this can be changed in the software. but it seems it would heave no use
class MotorDriver
{	
public:	
	void setup();	
	void setAcceleration(int a, int a2);
	void setTargetSpeed(int32_t motor1, int32_t motor2);
	void loop();
	void setSpeed(uint16_t motor1, uint16_t motor2);
	void setMotorDriverEnabled(bool b);

	bool isMotorDriverEnabled();
	uint16_t getMotor1TargetSpeed();
	uint16_t getMotor2TargetSpeed();
	uint16_t getMotor1Speed();
	uint16_t getMotor2Speed();

	//todo:
	//void moveToXY();
	//void moveBackToStart();

private:
	bool motorsEnabled;
	ledc_timer_config_t ledc_timer_motor_1;
	ledc_timer_config_t ledc_timer_motor_2;

    float motor1Speed;				//current motorspeed
    float motor2Speed;				//current motorspeed
	float motor1OldSpeed;
	float motor2OldSpeed;
	int32_t motor1TargetSpeed;			//target speed of motor 1
    int32_t motor2TargetSpeed;			//target speed of motor 2
	uint32_t acceleration_motor1; 				//acceleration of current speed to target speed in steps/s^1
	uint32_t acceleration_motor2; 				//acceleration of current speed to target speed in steps/s^2
	uint64_t lastTimeSincePreviousLoop; //used for calculating the delta-T for the acceleration

};
