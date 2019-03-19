#pragma once

static uint8_t* cameraData;
extern SharedVariables sharedVariables;
extern MotorDriver * MotorController;
extern SerialConnection * Camera;
#define DYSON_PROXIMITY_TARGET 150

uint64_t ObjectSearchLastTimeImage = 0;


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
    MotorController->setAcceleration(15000,15000);
    MotorController->setTargetSpeed(50000, 50000);
    //read camera data and estract the coordinates (x and y go form 0 to 100)
    if((esp_timer_get_time() - ObjectSearchLastTimeImage > 10000) && (ObjectSearchLastTimeImage > 0)){ // 10ms
        #ifdef DEBUG_OBJECT_SEARCH
            printf("cameraData (X and Y):   ");
            printf((char*)cameraData);
            printf("\n");
        #endif
        char * X_Index;
        X_Index = strstr ((char*)cameraData,"X:");
        char * Y_Index;
        Y_Index = strstr ((char*)cameraData,"Y:");
        char * End_Index;
        End_Index = strstr ((char*)cameraData,"\n");
        // #ifdef DEBUG_OBJECT_SEARCH
        //     printf("index of variabels (X,Y,END) : %s     %s    %s  \n",X_Index,Y_Index,End_Index);          
        // #endif

        char* XValueString = (char*)malloc(4);
        char* YValueString = (char*)malloc(4);
        XValueString[3] = '\0';
        YValueString[3] = '\0';
        XValueString[2] = '\0';
        YValueString[2] = '\0';
        XValueString[1] = '\0';
        YValueString[1] = '\0';
        strncpy(XValueString, X_Index+2, Y_Index-X_Index-2);
        strncpy(YValueString, Y_Index+2, End_Index-Y_Index-2);

        int x,y;
        x = atoi(XValueString);
        y = atoi(YValueString);
      
        #ifdef DEBUG_OBJECT_SEARCH  
        printf("-----------------\n");
        printf(XValueString);
        printf("\n");
        printf(YValueString);
        printf("\n");
        printf("in integers: %d   %d \n ",x,y);
        printf("-----------------\n");
        #endif


        //adjusting the servo camera
        //camera servo is at zero (normal position) at 170 degrees. target position of X variable is 50
        int ca = Camera->getCameraAngle();
        if(x < 50 && ca <170){
            Camera->setCameraAngle(ca+1);
        } else if(x>50 && ca > 50){
            Camera->setCameraAngle(ca-1);
        }





    }

}
void programLoop(){
    if(Camera->dataAnvailable()){
        cameraData = Camera->ReadData(); //also sends a confirmation which toggles the red led
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