#pragma once

static uint8_t* cameraData;
extern SharedVariables sharedVariables;
extern MotorDriver * MotorController;
extern SerialConnection * Camera;
#define DYSON_PROXIMITY_TARGET 150

controlModes oldMode = controlModes::OFF;
uint64_t lastUpdateXAndYCoordinates = 0;

#define x sharedVariables.outputs.objectX //default x value of target... update with method calculateXandY()
#define y sharedVariables.outputs.objectY //default y value of target... update with method calculateXandY()

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
float cameraAngle=170;
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
    }
    else if(esp_timer_get_time() - lastUpdateXAndYCoordinates > 2000000)
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
    sharedVariables.outputs.servoPosition = cameraAngle;

    Camera->setCameraAngle((int)sharedVariables.outputs.servoPosition);
    
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
            MotorController->setAcceleration(30000);
            speed = 4000;
            steering = 3500;
        }

    }else
    {
        MotorController->setAcceleration(10000);
        steering *= 3 + sharedVariables.outputs.proximityLeft/100;
    }
    
    int leftSpeed = speed + steering;
    int rightSpeed = speed - steering;
    MotorController->setTargetSpeed(leftSpeed, rightSpeed);
    //printf("%d,%d,1000\n",sharedVariables.outputs.proximityLeft, sharedVariables.outputs.proximityRight);

}


#define RIGHT 0
#define LEFT 1
#define PROXYDESIREDVALUE 110
#define ROTATIONSPEED 5000
#define ROTATIONDELAYS 260
#define ROTATIONACCELERATION 45000
struct followWallHelperStruct{
    uint64_t lastTimeWallSeen = 0;
    uint64_t lastTimeLookedAround = 0;
    bool lastWallFollowed = RIGHT; // default value (for looking around)

}FHS;
struct searchHelperStruct{
    bool isSearching = false;
    int lastYLocation = 50; // for determining the search direction
    
}SHS;
void stickToWall(bool direction,int sensorValue){
    int error  = abs(PROXYDESIREDVALUE - sensorValue) * 4; //error times error multiplyer
    if(direction == RIGHT){
        if(sensorValue >PROXYDESIREDVALUE){
            #ifdef DEBUG_WALL_SEARCH
            printf("RsgL\n"); //was not searching... is following target now
            #endif
            MotorController->setTargetSpeed(3000+error,3000-error); // motors are somehow inverted
        }else{
            #ifdef DEBUG_WALL_SEARCH
            printf("RsgR\n"); //was not searching... is following target now
            #endif
            MotorController->setTargetSpeed(3000-error,3000+error); // motors are somehow inverted
        }
        
    }else{
         if(sensorValue >PROXYDESIREDVALUE){
             #ifdef DEBUG_WALL_SEARCH
            printf("LsgR\n"); //was not searching... is following target now
            #endif
            MotorController->setTargetSpeed(3000-error,3000+error); // motors are somehow inverted
        }else{
            #ifdef DEBUG_WALL_SEARCH
            printf("LsgL\n"); //was not searching... is following target now
            #endif
            MotorController->setTargetSpeed(3000+error,3000-error);// motors are somehow inverted
        }
    }
}
void followWalls(){
    // this method will be called mostly after automaticObjectSearch cant find a target
    int speed = 7000;
    int m1Speed = speed;
    int m2Speed = speed;
       


    int proxyLeft = sharedVariables.outputs.proximityLeft;
    int proxyRight = sharedVariables.outputs.proximityRight;
    if(proxyLeft >= 25 || proxyRight >= 25){
        FHS.lastTimeWallSeen = esp_timer_get_time();
    }

    if(esp_timer_get_time() - FHS.lastTimeWallSeen < 500000) {
        //within 500 milliseconds of detecting a wall
        if(esp_timer_get_time() - FHS.lastTimeLookedAround > 5000000){
            

            //when 8 seconds have passed
            FHS.lastTimeLookedAround = esp_timer_get_time();
            //stop before looking around
            MotorController->setAcceleration(10000000);
            MotorController->setTargetSpeed(0,0);
            vTaskDelay(100/portTICK_PERIOD_MS);
            //look around in case the target is found
            //will have a delay... dont worry, it wont take long
            MotorController->setAcceleration(ROTATIONACCELERATION);
            if(FHS.lastWallFollowed == RIGHT){
                //look left
                MotorController->setTargetSpeed(ROTATIONSPEED,-ROTATIONSPEED);
                vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                MotorController->setTargetSpeed(0,0);
                vTaskDelay(ROTATIONDELAYS*3/portTICK_PERIOD_MS);
                //read uard buffer before returning to first value
                if(Camera->dataAnvailable()){
                    cameraData = Camera->ReadData(); //also sends a confirmation which toggles the red led
                    calculateXandY();
                    return; // dont look back... otherwise the target can not be fond with automaticObjectSearch
                }
                //look back
                MotorController->setTargetSpeed(-ROTATIONSPEED,ROTATIONSPEED);
                vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                MotorController->setTargetSpeed(0,0);
                vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);

            }else{
                //look right
                MotorController->setTargetSpeed(-ROTATIONSPEED,ROTATIONSPEED);
                vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                MotorController->setTargetSpeed(0,0);
                vTaskDelay(ROTATIONDELAYS*3/portTICK_PERIOD_MS);
                //read uard buffer before returning to first value
                if(Camera->dataAnvailable()){
                    cameraData = Camera->ReadData(); //also sends a confirmation which toggles the red led
                    calculateXandY();
                    return; // dont look back... otherwise the target can not be fond with automaticObjectSearch
                }
                //look back
                MotorController->setTargetSpeed(ROTATIONSPEED,-ROTATIONSPEED);
                vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                MotorController->setTargetSpeed(0,0);
                vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);

            }
            return; // return, continue next loop
        }

        //when not searching for a target,,, just drive close to the wall
            if(proxyLeft > proxyRight){
                //stick to left wall
                FHS.lastWallFollowed = LEFT;
                stickToWall(LEFT,sharedVariables.outputs.proximityLeft);
                
            }else{
                //stick to right wall
                FHS.lastWallFollowed = RIGHT;
                stickToWall(RIGHT,sharedVariables.outputs.proximityRight);
                
            }

            if(sharedVariables.outputs.TOFSensorDistanceMM < 65){   // when detecting a wall in fron while fillowing a wall
                 MotorController->setAcceleration(10000000);
                MotorController->setTargetSpeed(0,0);
                vTaskDelay(100/portTICK_PERIOD_MS);
                MotorController->setAcceleration(ROTATIONACCELERATION);
                if(FHS.lastWallFollowed == RIGHT){
                    MotorController->setTargetSpeed(ROTATIONSPEED,-ROTATIONSPEED);  //LOOK LEFT
                    vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                    MotorController->setTargetSpeed(0,0);
                    vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                }else{  //left
                    MotorController->setTargetSpeed(-ROTATIONSPEED,ROTATIONSPEED); //LOOK RIGHT
                    vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                    MotorController->setTargetSpeed(0,0);
                    vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                }
                return;
            }
        


        // no wall in the last 500ms, and no target in sight,, go search for a wall
    } else{
        //no wall nearby.. go search for a wall
        MotorController->setTargetSpeed(3000,3000);
        if(sharedVariables.outputs.TOFSensorDistanceMM < 65){   
                 MotorController->setAcceleration(10000000);
                MotorController->setTargetSpeed(0,0);
                vTaskDelay(100/portTICK_PERIOD_MS);
                MotorController->setAcceleration(ROTATIONACCELERATION);
                MotorController->setTargetSpeed(-ROTATIONSPEED,ROTATIONSPEED);  //LOOK RIGHT
                vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                MotorController->setTargetSpeed(0,0);
                vTaskDelay(ROTATIONDELAYS/portTICK_PERIOD_MS);
                
            return;
        }

    }


}
void AutomaticObjectSearch()
{   
    //this method will contain blocking functions
    MotorController->setAcceleration(10000);
    
    //adjust servo to camera object direction
    automaticServoAim();

    //folllow a target
    int speed = 7000;
    int m1Speed = speed;
    int m2Speed = speed;
    //when it finds a target within 200 ms,,, drive towards it
    if((esp_timer_get_time() - lastUpdateXAndYCoordinates < 200000) && (lastUpdateXAndYCoordinates > 0)){
        #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
        printf("1");  // target found in 200ms
        #endif
        if(SHS.isSearching == true){
            #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
            printf("2"); // it was searching before... come to a inmediate stop
            #endif
            SHS.isSearching = false;
            //brake and stop
            m1Speed = 0;
            m2Speed = 0;
            MotorController->setAcceleration(2147483647); // will go back to default value on next loop
        } else{
            #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
            printf("3"); //was not searching... is following target now
            #endif
            m1Speed += (50-y) * 50;
            m2Speed -= (50-y)  * 50;
        }
        
        if(sharedVariables.outputs.proximityLeft > 20)
        {  
            m1Speed = m2Speed / ((float)sharedVariables.outputs.proximityLeft/50.0);
        }
        if(sharedVariables.outputs.proximityRight > 20)
        {
            m2Speed = m1Speed / ((float)sharedVariables.outputs.proximityRight/50.0);
        }
        if(sharedVariables.outputs.TOFSensorDistanceMM < 200){  //within 20cm of target, slow down
        #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
        printf("4"); //stop... tof ir sensor in front
        #endif
            m1Speed /= 2;
            m2Speed /= 2;
        } 
        //if very close to the target.... stop
        if(sharedVariables.outputs.TOFSensorDistanceMM < 100){  //within 10cm of target
        #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
        printf("4"); //stop... tof ir sensor in front
        #endif
            m1Speed = 0;
            m2Speed = 0;
            MotorController->setAcceleration(10000000); // will go back to default value on next loop
        } 


    } else{
        #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
        printf("5"); // target not found (in last 200ms)
        #endif
        // when the target is not found in the last 200 ms,, stop (for max 0.5 second)
        if((esp_timer_get_time() - lastUpdateXAndYCoordinates < 500000) && (lastUpdateXAndYCoordinates > 0)){
            #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
            printf("6"); // not moving because target is not found... might beccome visible soon
            #endif
            m1Speed = 0;
            m2Speed = 0;
            MotorController->setAcceleration(1000000); // will go back to default value on next loop
        }
        else if((esp_timer_get_time() - lastUpdateXAndYCoordinates < 6000000) && (lastUpdateXAndYCoordinates > 0))
        {   
            #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
            printf("7");  // 0.5 seconds no target... just start searching
            #endif
       
            if(sharedVariables.outputs.proximityLeft > 100)
            {  //when this happens the robot will rotate in the other direction
                y = 51;
            }
            if(sharedVariables.outputs.proximityRight > 100)
            {   //when this happens the robot will rotate in the other direction
                y = 49;
            }
            SHS.isSearching = true;
            SHS.lastYLocation = y;
            if(SHS.lastYLocation < 50){
                m1Speed = 2000;
                m2Speed = -2000;
            }else{
                m1Speed = -2000;
                m2Speed = 2000;
            }
            

           
        } else { // 6 seconds... just start driving now
            
              #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
            printf("WF\n");
            #endif
            followWalls();
            return; // dont want to update the motors again
        }        
        
        
    }
    MotorController->setTargetSpeed(m1Speed, m2Speed);
    SHS.lastYLocation = y;
    #ifdef DEBUG_BADLY_PROGRAMMED_ALGORITM
        printf("\n");
        #endif

}
void programLoop(){
    if(Camera->dataAnvailable()){
        cameraData = Camera->ReadData(); //also sends a confirmation which toggles the red led
        calculateXandY();
    }

    if(sharedVariables.inputs.mode != controlModes::AUTOMATIC_OBJECT_SEARCH)
    {
         Camera->setCameraAngle((int)sharedVariables.inputs.servoPosition);
    }

    if(sharedVariables.inputs.mode == controlModes::AUTOMATIC_DYSON_MODE)
    {
        dysonMode();
    } else if(sharedVariables.inputs.mode == controlModes::AUTOMATIC_OBJECT_SEARCH){
        AutomaticObjectSearch();
    }
    else if(sharedVariables.inputs.mode == controlModes::MANUAL_WIFI)
    {
        Camera->setCameraAngle((int)sharedVariables.inputs.servoPosition);
    }
    else if(sharedVariables.inputs.mode == controlModes::AUTOMATIC_HEADLESS_MODE)
    {
        followWalls();
    }
    else
    {
        MotorController->setTargetSpeed(0,0);
    }
    
    if(oldMode != sharedVariables.inputs.mode)
    {
        if(sharedVariables.inputs.mode == controlModes::MANUAL_WIFI_BALANCE)
        {
            MotorController->setAcceleration(10000000);
        }
    }
    oldMode = sharedVariables.inputs.mode;
    if(Camera->dataAnvailable()){
         cameraData = Camera->ReadData(); // will also sand a confirmation
    }

}