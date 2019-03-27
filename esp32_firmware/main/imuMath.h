#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "pins.h"
#include "settings.h"
#include "sharedVariables.h"
extern SharedVariables sharedVariables;
extern MotorDriver * MotorController;

uint32_t lastAngleProcessingTime = 0;

#define accelX sharedVariables.outputs.acceleration[0]
#define accelY sharedVariables.outputs.acceleration[1]
#define accelZ sharedVariables.outputs.acceleration[2]
#define gyroX sharedVariables.outputs.gyroValues[0]
#define gyroY sharedVariables.outputs.gyroValues[1]
#define gyroZ sharedVariables.outputs.gyroValues[2]
#define roll sharedVariables.outputs.roll 
#define pid_p (sharedVariables.inputs.PID_p/10.0)
#define pid_i (sharedVariables.inputs.PID_i/10.0)
#define pid_d (sharedVariables.inputs.PID_d/10.0)
#define workingAngle sharedVariables.inputs.workingAngle
#define pidMaxSpeed sharedVariables.inputs.pidMaxSpeed
void imuMathSetup()
{
    lastAngleProcessingTime = esp_timer_get_time();
}
void imuCalculateAngle()
{

   uint32_t deltaT = esp_timer_get_time() - lastAngleProcessingTime;
   lastAngleProcessingTime = esp_timer_get_time();
   //int accelPitch = -atan2(accelX, sqrt(accelY*accelY + accelZ*accelZ))* 57.3;
   double accelRoll =  90 - atan2(accelY, accelZ) * -57.3 ;
   
   double gyroRoll = roll + (gyroX * deltaT / 1000000); // convert angle to angle/deltaT and sum it with roll
   roll = gyroRoll * 0.95 + accelRoll * 0.05;
   #ifdef PRINT_COMPLEMENTARY
   printf("%f, %f     %f\n", accelRoll, gyroRoll, roll);
   #endif
}
float self_balance_pid_setpoint=0;
float pid_setpoint = 10;
float pid_output = 0;
float pid_error_temp = 0;
float pid_i_mem=0;
float pid_last_d_error=0;
void balance()
{
    pid_error_temp = roll - self_balance_pid_setpoint - pid_setpoint;
    if(pid_output > 10 || pid_output < -10)pid_error_temp += pid_output * 0.015 ;

    pid_i_mem += pid_i * pid_error_temp;                                 //Calculate the I-controller value and add it to the pid_i_mem variable
    if(pid_i_mem > pidMaxSpeed)pid_i_mem = pidMaxSpeed;                                       //Limit the I-controller to the maximum controller output
    else if(pid_i_mem < -pidMaxSpeed)pid_i_mem = -pidMaxSpeed;
    //Calculate the PID output value
    pid_output = pid_p * pid_error_temp + pid_i_mem + pid_d * (pid_error_temp - pid_last_d_error);
    if(pid_output > pidMaxSpeed)pid_output = pidMaxSpeed;                                     //Limit the PI-controller to the maximum controller output
    else if(pid_output < -pidMaxSpeed)pid_output = -pidMaxSpeed;

    pid_last_d_error = pid_error_temp;                                        //Store the error for the next loop

    if(roll > workingAngle || roll < -1*workingAngle){    //If the robot tips over or the start variable is zero or the battery is empty
        pid_output = 0;                                                         //Set the PID controller output to 0 so the motors stop moving
        pid_i_mem = 0;                                                          //Reset the I-controller memory
        self_balance_pid_setpoint = 0;                                          //Reset the self_balance_pid_setpoint variable
    }
    MotorController->setAcceleration(100000000);
    MotorController->setTargetSpeed(pid_output*40, pid_output*40);
}