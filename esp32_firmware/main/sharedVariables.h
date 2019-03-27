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
    AUTOMAITC_BALANCE_DYSON_MODE = 9,
    MANUAL_WIFI_BALANCE = 10

};
enum class objects
{
    OBJECT_YELLOW_BALL,
    OBJECT_RED_BALL,
    OBJECT_BLUE_BALL
};
struct Steppers
{
    //motorcontroller
    bool instantreaction = false; //if true,, motor will ignore acceleration and set speed instantly to targetSpeed
    bool motorsEnabled = false;
    int32_t motor1TargetSpeed = 0;			//target speed of motor 1
    int32_t motor2TargetSpeed = 0;			//target speed of motor 2
	uint32_t acceleration_motor1 = 1000; 				//acceleration of current speed to target speed in steps/s^1
	uint32_t acceleration_motor2 = 1000; 				//acceleration of current speed to target speed in steps/s^2
    uint32_t acceleration = 1000;
};
typedef struct{  
    
    struct Inputs//esp32 in / gui out
    {
        Steppers steppers;
        //todo add manual control and location

        uint16_t programSpeed = 0;
        uint16_t programAggression = 0;
        uint16_t programSpecificTuning = 0;
        //balancing
        uint8_t PID_p = 30;
        uint8_t PID_i = 4;
        uint8_t PID_d = 50;
        uint8_t workingAngle = 30;//balk 20 - 70
        int pidMaxSpeed = 400;//balk 100 - 1000
        int complementaryFilter = 950;//balk 900 - 999
        int loopDelay = 4000;// balk 1000 - 10000
        int straightUpSetpoint = 10;//balk -20 - 20
        int setPoint = 0;
        int steering = 0;
        //servo
        uint8_t servoPosition = 80; //in degrees

        //modes
        controlModes mode = controlModes::AUTOMATIC_OBJECT_SEARCH;

        //ir send
        uint8_t irFlowNumber = 0;
        uint8_t irAddress=0;
        uint8_t irCommand=0;
    }inputs;
    struct Outputs // esp32 out / gui in
    {
        //mpu9250
        float acceleration[3];//x,y,z
        float gyroValues[3];//x,y,z
        float magnetometerValues[3];//x,y,z
        float compassAngle;
        double roll;
        float MPU9250Temperature;
        bool MPU9250Working = true;

        //tof sensor
        uint16_t TOFSensorDistanceMM;
        bool TOFSensorWorking = true;
        //ir receiver

        uint8_t irFlowNumber = 0;
        uint8_t irLastAddress=0;
        uint8_t irLastCommand=0;


        //proximity sensors 
        int proximityLeft;
        int proximityRight;
        int lightLeft;
        int lightRight;

        Steppers steppers;

        //camera
        uint8_t cameraFrameRate;
        bool cameraImageAvailable = false;
        bool cameraWorking = true;
        uint8_t objectX = 0;
        uint8_t objectY = 0;
        bool objectSeen = false;

        //servo
        uint8_t servoPosition; //in degrees

         //wifi udp
        bool wifiAvailable = false;
        bool wifiConnected = false;
        uint8_t wifiSignalStrength = false;

        //battery
        float voltage=0;
        int loopUpdateRate = 0;
    }outputs;
   

} SharedVariables;
