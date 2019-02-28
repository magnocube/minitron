#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include "driver/uart.h"
#include <stdio.h>
#include <string.h>



#include "pins.h"
class SerialConnection
{	
public:	
	void setup();	
	bool dataAnvailable();
	char* ReadData();
private:
    int serialIdex;
};
