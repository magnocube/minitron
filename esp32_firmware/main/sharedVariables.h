#pragma once
typedef struct{  
	//mpu9250
    float acceleration[3];//x,y,z
    float gyroValues[3];//x,y,z
    float magnetometerValues[3];//x,y,z
    float compassAngle;
    float MPU9250Temperature;
    bool MPU9250ErrorOccured = false;
    bool MPU9250Working = true;

    //tof sensor
    uint16_t TOFSensorDistanceMM;
    bool TOFSensorErrorOccured = false;
    bool TOFSensorWorking = true;

    //ir receiver
    //todo add last command
    bool IRReceiverErrorOccured = false;
    bool IRReceiverWorking = true;

    //ir leds
    //todo add next command

    //proximity sensors 
    uint8_t proximityLeft;
    uint8_t proximityRight;
    uint8_t lightLeft;
    uint8_t lightRight;
    bool proximityErrorOccured = false;
    bool proximityWorking = true;

    //motorcontroller
    bool enabled = true;
    uint32_t steppers1Acceleration;
    uint32_t steppers2Acceleration;
    int16_t steppers1Speed;
    int16_t steppers2Speed;
    uint16_t stepperMaxSpeed;

    //todo add manual control and location

    //balancing
    uint8_t PID_p;
    uint8_t PID_i;
	uint8_t PID_d;

	//camera
	uint8_t cameraFrameRate;
	bool cameraImageAvailable = false;
	bool cameraErrorOccured = false;
    bool cameraWorking = true;
    
    //servo
    uint8_t servoPosition; //in degrees

    //wifi udp
    bool wifiAvailable = false;
    bool wifiConnected = false;
    uint8_t wifiSignalStrength = false;

    //battery
    float voltage;
    bool on = true;

    //modes
    int mode=0;//todo define modes


} SharedVariables;

SharedVariables sharedVariables; //instanciated_struct_of_very_important_variables