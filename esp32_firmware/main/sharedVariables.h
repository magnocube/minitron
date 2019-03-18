#pragma once

enum class controlModes{
    MANUAL_WIFI = 0,
    MANUAL_IR = 1,
    OFF = 2,
    AUTOMATIC_OBJECT_SEARCH = 3,
    AUTOMATIC_DYSON_MODE = 4,
    AUTOMATIC_BATTLE_MODE = 5,
    AUTOMATIC_HEADLESS_MODE = 6,
    AUTOMATIC_EPILEPTIC_MODE = 7,
    AUTOMATIC_BALANCE_OBJECT_SEARCH = 8,
    AUTOMAITC_BALANCE_DYSON_MODE = 9
};
enum class objects
{
    OBJECT_YELLOW_BALL,
    OBJECT_RED_BALL,
    OBJECT_BLUE_BALL
};
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
    int proximityLeft;
    int proximityRight;
    int lightLeft;
    int lightRight;
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
    controlModes mode=controlModes::AUTOMATIC_DYSON_MODE;


} SharedVariables;

static SharedVariables sharedVariables; //instanciated_struct_of_very_important_variables   --> isoviv