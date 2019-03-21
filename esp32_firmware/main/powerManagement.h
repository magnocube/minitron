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

extern SharedVariables sharedVariables;

void checkBattery()
{
    int batteryValue = adc1_get_raw(BATTERY_VOLTAGE_PIN);
    const int maxValue = 4096;
    const float r1 = 7500;
    const float r2 = 1000;
    const float vref = 3.6;
    sharedVariables.outputs.voltage = ((r1+r2)/r2)*((float)batteryValue/maxValue)*vref;
#ifdef PRINT_VOLTAGE
    printf("%f, %d\n",sharedVariables.outputs.voltage, batteryValue);
#endif
    if(sharedVariables.outputs.voltage < 10.50)
    {   
        printf("IJKEL.... DE BATTERIJ IS LEEG... RIP PROJECT\n");
        printf("IJKEL.... DE BATTERIJ IS LEEG... RIP PROJECT\n");
        printf("IJKEL.... DE BATTERIJ IS LEEG... RIP PROJECT\n");
        printf("IJKEL.... DE BATTERIJ IS LEEG... RIP PROJECT\n");
            esp_deep_sleep(1000000000000000000);
            esp_bt_controller_disable();
            esp_wifi_stop();

    }
}
void batteryCheckerSetup()
{
    adc1_config_channel_atten(BATTERY_VOLTAGE_PIN, ADC_ATTEN_DB_11);
    checkBattery();
}
