

#include "main.h"


void core0Task( void * pvParameters ){
    batteryCheckerSetup();
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
       
        vTaskDelay(10/portTICK_PERIOD_MS);
        MotorController->loop();
        mpu9250ReadMotion();//takes 0.65ms
        mpu9250ReadCompass();//takes 0.5ms

        //tofSensor->measure();

        irDecoder->read();//takes 0.005ms
        if(loopCounter%100 == 0)
        {
            irDecoder->send();//takes 0.03ms

        }
        irDecoder->runProximity();//takes 0.90ms

        loopCounter++;
        
        checkBattery();
    }
}
void core1Task( void * pvParameters ){

    Camera = new SerialConnection();
    Camera->setup();
    Camera->setCameraAngle(10);

    MotorController->setTargetSpeed(65000,65000);
  
    //wifiSetup();

    while(true)
    {
        //wifiLoop();
        

        if(Camera->dataAnvailable()){
            Camera->ReadData(); // will also sand a confirmation
        }
        
        // vTaskDelay(800/portTICK_PERIOD_MS);
        // Camera->setCameraAngle(170);
        // vTaskDelay(800/portTICK_PERIOD_MS);
    }

}
extern "C" void app_main()
{
    printf("minitron firmware started\n");  
    MotorController = new MotorDriver();
    MotorController->setup();

    

    xTaskCreatePinnedToCore(core0Task, "core0Task", 
                    100000,      // Stack size in words 
                    NULL,       // Task input parameter 
                    1,          // Priority of the task 
                    NULL,       // Task handle. 
                    0); //core 0       
    xTaskCreatePinnedToCore(core1Task, "core1Task", 
                    100000,      // Stack size in words 
                    NULL,       // Task input parameter 
                    1,          // Priority of the task 
                    NULL,       // Task handle. 
                    1); //core 1

    while(true)
    {
        vTaskDelay(portMAX_DELAY);
    }
}
