#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpu9250.cpp"
#include "irDecoder.h"
#include "SerialConnection.h"
#include "MotorDriver.h"
#include "Arduino.h"
#include "esp_log.h"

typedef struct{  
    SerialConnection * Camera;
    IrDecoder * irDecoder;
    MotorDriver * MotorController;
    uint16_t lastCompassValues[3];
} very_important_variables;

very_important_variables isoviv; //instanciated_struct_of_very_important_variables