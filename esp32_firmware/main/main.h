#pragma once
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include "esp_task_wdt.h"
#include "sharedVariables.h"
#include <string.h>

#include "irDecoder.h"
#include "SerialConnection.h"
#include "MotorDriver.h"
#include "esp_log.h"

SerialConnection * Camera;
IrDecoder * irDecoder;
MotorDriver * MotorController;
SharedVariables sharedVariables;

#include "powerManagement.h"
#include "TOFSensor.h"

TOFSensor * tofSensor;
#include "mpu9250.cpp"
#include "wifiConnection.cpp"
#include "program.h"
