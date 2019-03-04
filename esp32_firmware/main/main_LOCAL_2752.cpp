/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mpu9250.cpp"
#include "irDecoder.h"
#include "Arduino.h"

IrDecoder irDecoder;

int hz50=0;

void core0Task( void * pvParameters ){
    mpu9250Setup();
    compassSetup();
    irDecoder.setup();
    uint32_t loopCounter=0;
    while(true)
    {
        mpu9250ReadMotion();//takes 0.65ms
        mpu9250ReadCompass();//takes 0.5ms

        irDecoder.read();//takes 0.005ms
        if(loopCounter%100 == 0)
        {
            //irDecoder.send();//takes 0.03ms
            irDecoder.runProximity();//takes 90ms

        }
        
        loopCounter++;
    }
}
void core1Task( void * pvParameters ){
    while(true)
    {
        vTaskDelay(1000/portMAX_DELAY);
    }
}
extern "C" void app_main()
{
    printf("minitron firmware started\n");
    xTaskCreatePinnedToCore(core0Task, "core0Task", 
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    1,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    0); //core 0
    xTaskCreatePinnedToCore(core1Task, "core1Task", 
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    1,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    1); //core 1
    while(true)
    {
        vTaskDelay(portMAX_DELAY);
    }
}