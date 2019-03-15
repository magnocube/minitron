#pragma once

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


#include "pins.h"
#include "settings.h"
#include "sharedVariables.h"

void checkBattery()
{
    int batteryValue = adc1_get_raw(BATTERY_VOLTAGE_PIN);
    const int maxValue = 4096;
    const float r1 = 6000;
    const float r2 = 1000;
    const float vref = 3.6;
    sharedVariables.voltage = ((r1+r2)/r2)*(batteryValue/maxValue)*vref;
#ifdef PRINT_VOLTAGE
    printf("%d\n",sharedVariables.voltage);
#endif
}
void batteryCheckerSetup()
{
    adc1_config_channel_atten(BATTERY_VOLTAGE_PIN, ADC_ATTEN_DB_11);
    checkBattery();
}
