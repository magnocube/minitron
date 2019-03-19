#pragma once

static char* cameraData;
extern SharedVariables sharedVariables;
extern MotorDriver * MotorController;
#define DYSON_PROXIMITY_TARGET 150

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
void programLoop(){
    if(sharedVariables.mode == controlModes::AUTOMATIC_DYSON_MODE)
    {
        dysonMode();
    } 

    if(Camera->dataAnvailable()){
          cameraData = Camera->ReadData(); // will also sand a confirmation
    }

}