#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include "driver/uart.h"
#include <stdio.h>
#include <string.h>
#include "freertos/task.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#include "pins.h"



#define SERVO_MIN_PULSEWIDTH 500 //Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2500 //Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 180 //Maximum angle in degree upto which servo can rotate


class SerialConnection
{	
public:	
	void setup();	
	bool dataAnvailable();
	void sendData(char * data);
	char* ReadData();
	void setCameraAngle(int degrees);
	int getCameraAngle();
private:
    int serialIdex;
	const uart_port_t uart_num = UART_NUM_2;
	
	int servoCameraPin = 5;
	int pos = 0;    

	int degreesToPos(int degree_of_rotation);
	

	int minValue        = 1310;  // micro seconds (uS) (65536/50)
	int maxValue        = 2621; // micro seconds (uS)	(65536/50*2)
	
	int duty            = minValue;

};
