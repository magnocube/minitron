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
#define pid_p (sharedVariables.inputs.PID_p/5.0)
#define pid_i (sharedVariables.inputs.PID_i/10.0)
#define pid_d (sharedVariables.inputs.PID_d/5.0)
#define workingAngle sharedVariables.inputs.workingAngle
#define pidMaxSpeed sharedVariables.inputs.pidMaxSpeed
#define defaultSetpoint sharedVariables.inputs.defaultSetpoint
#define controlSetpoint sharedVariables.inputs.setPoint / 5
#define controlSteering sharedVariables.inputs.steering


#define complementaryFilter sharedVariables.inputs.complementaryFilter
#define standStillAngle sharedVariables.inputs.standStillAngle
#define _acceleration sharedVariables.inputs.steppers.acceleration


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
   double filterValue = (double)complementaryFilter/1000.0;
   roll = gyroRoll * filterValue + accelRoll * (1-filterValue);
   #ifdef PRINT_COMPLEMENTARY
   printf("%f, %f     %f\n", accelRoll, gyroRoll, roll);
   #endif
}
double pid_output = 0;
double pid_error_temp = 0;
double pid_i_mem=0;
double pid_last_d_error=0;
void balance()
{
    pid_error_temp = roll - defaultSetpoint - controlSetpoint;
    if(pid_output > standStillAngle || pid_output < -1 * standStillAngle)pid_error_temp += pid_output * (standStillAngle/1000.0);

    pid_i_mem += pid_i * pid_error_temp;                                 //Calculate the I-controller value and add it to the pid_i_mem variable
    if(pid_i_mem > pidMaxSpeed)pid_i_mem = pidMaxSpeed;                                       //Limit the I-controller to the maximum controller output
    else if(pid_i_mem < -pidMaxSpeed)pid_i_mem = -1*pidMaxSpeed;
    //Calculate the PID output value
    pid_output = pid_p * pid_error_temp + pid_i_mem + pid_d * (pid_error_temp - pid_last_d_error);
    if(pid_output > pidMaxSpeed)pid_output = pidMaxSpeed;                                     //Limit the PI-controller to the maximum controller output
    else if(pid_output < -pidMaxSpeed)pid_output = -1*pidMaxSpeed;

    pid_last_d_error = pid_error_temp;                                        //Store the error for the next loop

    double leftSpeed = pid_output * 50;
    double rightSpeed = pid_output * 50;
    MotorController->setAcceleration(_acceleration);
    if(roll > workingAngle || roll < -workingAngle){    //If the robot tips over or the start variable is zero or the battery is empty
        pid_output = 0;                                                         //Set the PID controller output to 0 so the motors stop moving
        pid_i_mem = 0;                                                          //Reset the I-controller memory
        defaultSetpoint = 0;     
        leftSpeed = controlSetpoint * pidMaxSpeed;                                  //Reset the defaultSetpoint variable
        rightSpeed = controlSetpoint * pidMaxSpeed;
        MotorController->setAcceleration(_acceleration/10);
    }

    leftSpeed += controlSteering;
    rightSpeed -= controlSteering;

    MotorController->setTargetSpeed(leftSpeed, rightSpeed);
}
