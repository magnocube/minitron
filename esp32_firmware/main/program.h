#pragma once

static uint8_t* cameraData;
extern SharedVariables sharedVariables;
extern MotorDriver * MotorController;
extern SerialConnection * Camera;
#define DYSON_PROXIMITY_TARGET 150

uint64_t ObjectSearchLastTimeImage;


void dysonMode()
{   
    int speed = 6000;
    int steering = (DYSON_PROXIMITY_TARGET - sharedVariables.proximityLeft);
    if(steering>0)
    {
        steering *=2;
        if(sharedVariables.proximityLeft<80)
        {
            MotorController->setAcceleration(30000,30000);
            speed = 4000;
            steering = 3500;
        }

    }else
    {
        MotorController->setAcceleration(10000,10000);
        steering *= 3 + sharedVariables.proximityLeft/100;
    }
    
    int leftSpeed = speed + steering;
    int rightSpeed = speed - steering;
    MotorController->setTargetSpeed(leftSpeed, rightSpeed);
    printf("%d,%d,1000\n",sharedVariables.proximityLeft, sharedVariables.proximityRight);

}

void AutomaticObjectSearch()
{   
    MotorController->setTargetSpeed(5000, 5000);
    //read camera data and estract the coordinates (x and y go form 0 to 100)
    #define DEBUG_OBJECT_SEARCH

}
void programLoop(){
    if(Camera->dataAnvailable()){
        cameraData = Camera->ReadData();
        ObjectSearchLastTimeImage = esp_timer_get_time();
    }

    if(sharedVariables.mode == controlModes::AUTOMATIC_DYSON_MODE)
    {
        dysonMode();
    } else if(sharedVariables.mode == controlModes::AUTOMATIC_OBJECT_SEARCH){
        AutomaticObjectSearch();
    }

    if(Camera->dataAnvailable()){
         cameraData = Camera->ReadData(); // will also sand a confirmation
    }

}