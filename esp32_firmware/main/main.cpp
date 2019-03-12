

#include "main.h"


void core0Task( void * pvParameters ){
    mpu9250Setup();
    compassSetup();
    irDecoder = new IrDecoder();
    irDecoder->setup();
    //spiSetup();
    tofSensor = new TOFSensor();
    //tofSensor->init();
    uint32_t loopCounter=0;
    while(true)
    {
        mpu9250ReadMotion();//takes 0.65ms
        mpu9250ReadCompass();//takes 0.5ms

        //tofSensor->measure();

        irDecoder->read();//takes 0.005ms
        if(loopCounter%100 == 0)
        {
            irDecoder->send();//takes 0.03ms

        }
        irDecoder->runProximity();//takes 90ms

        loopCounter++;
        vTaskDelay(1);
    }
}
void core1Task( void * pvParameters ){

    wifiSetup();

    while(true)
    {
        wifiLoop();
        
        MotorController->setTargetSpeed(3000,3000);
        vTaskDelay(100/portTICK_PERIOD_MS);
        MotorController->setTargetSpeed(-3000,-3000);
        vTaskDelay(100/portTICK_PERIOD_MS);

        // if(Camera->dataAnvailable()){
        //     Camera->ReadData(); // will also sand a confirmation
        // }
        // MVCamera.setCameraAngle(10);
        // vTaskDelay(800/portTICK_PERIOD_MS);
        // MVCamera.setCameraAngle(170);
        // vTaskDelay(800/portTICK_PERIOD_MS);
    }

}
extern "C" void app_main()
{
    printf("minitron firmware started\n");  
     MotorController = new MotorDriver();
     MotorController->setup();

    // Camera = new SerialConnection();
    // Camera->setup();

    xTaskCreatePinnedToCore(core0Task, "core0Task", 
                    100000,      // Stack size in words 
                    NULL,       // Task input parameter 
                    1,          // Priority of the task 
                    NULL,       // Task handle. 
                    0); //core 0
                    
    /*xTaskCreatePinnedToCore(core1Task, "core1Task", 
                    100000,      // Stack size in words 
                    NULL,       // Task input parameter 
                    1,          // Priority of the task 
                    NULL,       // Task handle. 
                    1); //core 1
*/
    while(true)
    {
        vTaskDelay(portMAX_DELAY);
    }
}
