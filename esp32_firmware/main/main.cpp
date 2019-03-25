

#include "main.h"


void core0Task( void * pvParameters ){
    mpu9250Setup();
    compassSetup();
    batteryCheckerSetup();

    irDecoder = new IrDecoder(sharedVariables);
    irDecoder->setup();
    //spiSetup();
    tofSensor = new TOFSensor();
    tofSensor->init();
    uint32_t loopCounter=0;
    uint32_t lastTime = 0;
    while(true)
    {
        MotorController->loop();
        mpu9250ReadMotion();//takes 0.65ms
        mpu9250ReadCompass();//takes 0.5ms

        irDecoder->read();//takes 0.005ms
        if(loopCounter%10 == 0)
        {
            tofSensor->measure();
        }
        irDecoder->runProximity();//takes 0.90ms

        checkBattery();
        loopCounter++;
        while(esp_timer_get_time() - lastTime < 2000);
        lastTime = esp_timer_get_time();    }
}

void core1Task( void * pvParameters ){
    wifiSetup();
    while(true)
    {
        wifiLoop();
        if(udpReceived ==  true)
        {
            udpReceived = false;
            if(sharedVariables.inputs.mode == controlModes::MANUAL_WIFI)
            {
                MotorController->steppers = &sharedVariables.inputs.steppers;
                MotorController->calculateInduvidualAcceleration();
                printf("manual wifi %d\n",sharedVariables.inputs.steppers.motor1TargetSpeed);

            }
            else
            {
                MotorController->steppers = &sharedVariables.outputs.steppers;
            }
        }
        if(disconnected)
        {
            printf("disconnected\n");
            MotorController->steppers = &sharedVariables.outputs.steppers;
            if(sharedVariables.inputs.mode == controlModes::MANUAL_WIFI)
            {
                sharedVariables.inputs.mode = controlModes::AUTOMATIC_OBJECT_SEARCH;
            }
        }
        
        vTaskDelay(10/portTICK_PERIOD_MS);
        programLoop();

    }

}
extern "C" void app_main()
{
    printf("minitron firmware started\n");  
    MotorController = new MotorDriver(sharedVariables);
    MotorController->setup();
    MotorController->setMotorDriverEnabled(true);
    
    Camera = new SerialConnection();
    Camera->setup();
    Camera->setCameraAngle(170);
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
