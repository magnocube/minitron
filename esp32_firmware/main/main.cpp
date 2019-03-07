
#include "main.h"




void core0Task( void * pvParameters ){
     //mpu9250Setup();
     //compassSetup();
     //irDecoder.setup();
    //spiSetup();
     uint32_t loopCounter=0;
    while(true)
    {
        //mpu9250ReadMotion();//takes 0.65ms
        //mpu9250ReadCompass();//takes 0.5ms

        irDecoder.read();//takes 0.005ms
        if(loopCounter%100 == 0)
        {
            //irDecoder.send();//takes 0.03ms

        }
        //irDecoder.runProximity();//takes 90ms

        loopCounter++;
        printf("test\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void core1Task( void * pvParameters ){

    

    while(true)
    {
        vTaskDelay(10/portTICK_PERIOD_MS);
        if(isoviv.Camera->dataAnvailable()){
            isoviv.Camera->ReadData(); // will also sand a confirmation
        }
        // MVCamera.setCameraAngle(10);
        // vTaskDelay(800/portTICK_PERIOD_MS);
        // MVCamera.setCameraAngle(170);
        // vTaskDelay(800/portTICK_PERIOD_MS);
    }

}
extern "C" void app_main()
{
    printf("minitron firmware started\n");
    isoviv.MotorController = new MotorDriver();
    isoviv.MotorController->setup();

    isoviv.Camera = new SerialConnection();
    isoviv.Camera->setup();

    xTaskCreatePinnedToCore(core0Task, "core0Task", 
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    1,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    0); //core 0
    /*xTaskCreatePinnedToCore(core1Task, "core1Task", 
                    10000,      // Stack size in words 
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
