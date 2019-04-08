#pragma once

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


#include "pins.h"
#include "settings.h"
#include "sharedVariables.h"
#include "esp_sleep.h"
#include "esp_bt.h"
#include "esp_wifi.h"

extern MotorDriver* motorController;
extern SharedVariables sharedVariables;
int calculateVoltage()
{
    int batteryValue = adc1_get_raw(BATTERY_VOLTAGE_PIN);
    const int maxValue = 4096;
    const float r1 = 7500;
    const float r2 = 1000;
    const float vref = 3.6;
    return ((r1+r2)/r2)*((float)batteryValue/maxValue)*vref;
}
void checkBattery()
{
    sharedVariables.outputs.voltage  += 0.01*(calculateVoltage() - sharedVariables.outputs.voltage); // smooth it a bit, the input drops sometimes
#ifdef PRINT_VOLTAGE
    printf("%f\n",sharedVariables.outputs.voltage);
#endif
    if((sharedVariables.outputs.voltage < 10) && (sharedVariables.outputs.voltage > 4))//check if voltage > 4 for when the battery is not connected
    {   
        printf("IJKEL.... DE BATTERIJ IS LEEG... RIP PROJECT\n");
        printf("IJKEL.... DE BATTERIJ IS LEEG... RIP PROJECT\n");
        printf("IJKEL.... DE BATTERIJ IS LEEG... RIP PROJECT\n");
        printf("IJKEL.... DE BATTERIJ IS LEEG... RIP PROJECT\n");
        //the battery is emty and will damage when discharged more, turn everything in off or in low power mode
        esp_wifi_stop();
        motorController->setMotorDriverEnabled(false);
        esp_deep_sleep(1000000000000000000);
    }
}
void batteryCheckerSetup()
{
    adc1_config_channel_atten(BATTERY_VOLTAGE_PIN, ADC_ATTEN_DB_11);
    sharedVariables.outputs.voltage = calculateVoltage();
    checkBattery();
}
