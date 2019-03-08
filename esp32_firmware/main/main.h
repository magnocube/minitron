#pragma once
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpu9250.cpp"
#include "irDecoder.h"
#include "SerialConnection.h"
#include "MotorDriver.h"
#include "Arduino.h"
#include "esp_log.h"
#include "TOFSensor.h"
#include "sharedVariables.h"
#include "wifiConnection.h"

SerialConnection * Camera;
IrDecoder * irDecoder;
MotorDriver * MotorController;
TOFSensor * tofSensor;
