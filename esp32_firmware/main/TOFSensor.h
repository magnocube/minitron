#pragma once
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#include "I2Cbus.hpp"
#include "driver/gpio.h"
#include "driver/i2c.h"

#include "pins.h"
#include "settings.h"

#include "VL53L0X.h"

#define I2C_PORT I2C_NUM_0

class TOFSensor{
private:
	VL53L0X* vl = new VL53L0X(I2C_PORT);
public:

	void init();
	void measure();
};