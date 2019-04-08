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
extern MotorDriver * motorController;

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
double controlSetpointSmooth = 0;
void balance()
{
    controlSetpointSmooth += 0.2 * (controlSetpoint - controlSetpointSmooth);//make riding foreward and backward a little bit more smooth

    pid_error_temp = roll - defaultSetpoint - controlSetpointSmooth;
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
    motorController->setAcceleration(_acceleration);
    if(roll > workingAngle || roll < -workingAngle){    //If the robot tips over or the start variable is zero or the battery is empty
        pid_output = 0;                                                         //Set the PID controller output to 0 so the motors stop moving
        pid_i_mem = 0;                                                          //Reset the I-controller memory
        defaultSetpoint = 0;     
        leftSpeed = controlSetpoint * pidMaxSpeed * 2;                                  //Reset the defaultSetpoint variable
        rightSpeed = controlSetpoint * pidMaxSpeed * 2;
        motorController->setAcceleration(_acceleration/20);
    }

    leftSpeed += controlSteering;
    rightSpeed -= controlSteering;

    motorController->setTargetSpeed(leftSpeed, rightSpeed);
}



#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
uint32_t lastTime=0;


void play2()
{
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];
 
      motorController->setSpeed(underworld_melody[thisNote], underworld_melody[thisNote]);
      lastTime = esp_timer_get_time();
      while(esp_timer_get_time() - lastTime < noteDuration * 1000);
       

      motorController->setSpeed(0,0);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      lastTime = esp_timer_get_time();
      while(esp_timer_get_time() - lastTime < pauseBetweenNotes * 1000);
 
 
    }
}
void play()
{
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];
 
      motorController->setSpeed(melody[thisNote], melody[thisNote]);
      lastTime = esp_timer_get_time();
      while(esp_timer_get_time() - lastTime < noteDuration * 1000);
       

      motorController->setSpeed(0,0);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      lastTime = esp_timer_get_time();
      while(esp_timer_get_time() - lastTime < pauseBetweenNotes * 1000);
 
 
    }
}

