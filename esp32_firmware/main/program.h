#pragma once

static char* cameraData;
void dysonMode()
{   
    MotorController->setTargetSpeed(sharedVariables.proximityLeft*10, sharedVariables.proximityRight*10);
    printf("dyson mode\n");
}
void programLoop(){
    if(sharedVariables.mode == controlModes::AUTOMATIC_DYSON_MODE)
    {
        dysonMode();
    }

    // if(Camera->dataAnvailable()){
    //       cameraData = Camera->ReadData(); // will also sand a confirmation
    // }

}