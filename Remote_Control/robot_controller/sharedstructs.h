#include <QObject>
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
    bool motorsEnabled = false;
    int32_t motor1TargetSpeed = 0;			//target speed of motor 1
    int32_t motor2TargetSpeed = 0;			//target speed of motor 2
    uint32_t acceleration_motor1 = 1000; 				//acceleration of current speed to target speed in steps/s^1
    uint32_t acceleration_motor2 = 1000; 				//acceleration of current speed to target speed in steps/s^2
};
typedef struct{

    struct Inputs
    {
        Steppers steppers;
        //todo add manual control and location

        //balancing
        uint8_t PID_p = 0;
        uint8_t PID_i = 0;
        uint8_t PID_d = 0;

        //servo
        uint8_t servoPosition = 80; //in degrees

        //modes
        controlModes mode = controlModes::AUTOMATIC_OBJECT_SEARCH;
    }inputs;
    struct Outputs
    {
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

        Steppers steppers;

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
        float voltage=0;
        bool on = true;

    }outputs;


} SharedVariables;
