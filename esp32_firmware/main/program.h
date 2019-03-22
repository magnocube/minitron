#pragma once

static uint8_t* cameraData;
extern SharedVariables sharedVariables;
extern MotorDriver * MotorController;
extern SerialConnection * Camera;
#define DYSON_PROXIMITY_TARGET 150

bool isSearching = false;
uint64_t lastUpdateXAndYCoordinates = 0;
int x = 50; //default x value of target... update with method calculateXandY()
int y = 50; //default y value of target... update with method calculateXandY()

//will attempt to aim the servo with the camera to the target  (basics will work... but a lot of work has to be done)
void calculateXandY(){
    //uint32_t deltaT = esp_timer_get_time() - ObjectSearchLastTimeImage;  //in microseconds

   
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

        //x and y are global variables declared at the top of this file
        x = atoi(XValueString);
        y = atoi(YValueString);
        lastUpdateXAndYCoordinates = esp_timer_get_time();
      

}
float cameraAngle = 170;
float desiredCameraAngle = 170;
void automaticServoAim(){
    if(esp_timer_get_time() - lastUpdateXAndYCoordinates < 300000){ // max 500 ms since last time target seen    // just for the servo

        //adjusting the servo camera
        //camera servo is at zero (normal position) at 170 degrees. target position of X variable is 50
        if(x < 50){
            desiredCameraAngle += 1+(50-x)/50;
        }
        else if(x > 50){
            desiredCameraAngle -= 1+(x-50)/50;
        }
        printf(" %f, %f, %d\n", cameraAngle, desiredCameraAngle,x);
    }
    else if(esp_timer_get_time() - lastUpdateXAndYCoordinates < 5000000)
    {
        desiredCameraAngle = 170;
    }
    
    
    cameraAngle += 0.2 * (desiredCameraAngle - cameraAngle);
    if(cameraAngle > 170)
    {
        cameraAngle = 170;
    }
    else if(cameraAngle < 50)
    {
        cameraAngle = 50;
    }
    if(desiredCameraAngle > 170)
    {
        desiredCameraAngle = 170;
    }
    else if(desiredCameraAngle < 50)
    {
        desiredCameraAngle = 50;
    }
    Camera->setCameraAngle((int)desiredCameraAngle);
    
}
void dysonMode()
{   
    int speed = 6000;
    int steering = (DYSON_PROXIMITY_TARGET - sharedVariables.outputs.proximityLeft);
    if(steering>0)
    {
        steering *=2;
        if(sharedVariables.outputs.proximityLeft<80)
        {
            MotorController->setAcceleration(30000,30000);
            speed = 4000;
            steering = 3500;
        }

    }else
    {
        MotorController->setAcceleration(10000,10000);
        steering *= 3 + sharedVariables.outputs.proximityLeft/100;
    }
    
    int leftSpeed = speed + steering;
    int rightSpeed = speed - steering;
    MotorController->setTargetSpeed(leftSpeed, rightSpeed);
    printf("%d,%d,1000\n",sharedVariables.outputs.proximityLeft, sharedVariables.outputs.proximityRight);

}

void AutomaticObjectSearch()
{   
    MotorController->setAcceleration(10000,10000);
    
    
    //read camera data and estract the coordinates (x and y go form 0 to 100)
    automaticServoAim();
    int speed = 7000;
    int m1Speed = speed;
    int m2Speed = speed;
    if((esp_timer_get_time() - lastUpdateXAndYCoordinates < 200000) && (lastUpdateXAndYCoordinates > 0)){
        if(isSearching == true){
            MotorController->setSpeed(100,100);
            MotorController->steppers->motor1TargetSpeed = 100;
            MotorController->steppers->motor2TargetSpeed = 100;
            vTaskDelay(200/portTICK_PERIOD_MS);
        }
        isSearching = false;
        m1Speed += (50-y) * 100;
        m2Speed -= (50-y)  * 100;
        

    } else{
        if((esp_timer_get_time() - lastUpdateXAndYCoordinates < 2000000) && (lastUpdateXAndYCoordinates > 0)){
            m1Speed = 0;
            m2Speed = 0;
        }
        else
        {
            isSearching = true;
           m1Speed = 2000;
           m2Speed = -2000;
           
        }
        
    }
    MotorController->setTargetSpeed(m1Speed, m2Speed);

}
void programLoop(){
    if(Camera->dataAnvailable()){
        cameraData = Camera->ReadData(); //also sends a confirmation which toggles the red led
        calculateXandY();
    }

    if(sharedVariables.inputs.mode == controlModes::AUTOMATIC_DYSON_MODE)
    {
        dysonMode();
    } else if(sharedVariables.inputs.mode == controlModes::AUTOMATIC_OBJECT_SEARCH){
        AutomaticObjectSearch();
    }
    else if(sharedVariables.inputs.mode == controlModes::MANUAL_WIFI)
    {

    }
    else
    {
        MotorController->setTargetSpeed(0,0);
    }
    
    if(Camera->dataAnvailable()){
         cameraData = Camera->ReadData(); // will also sand a confirmation
    }

}