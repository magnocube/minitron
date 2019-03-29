// =========================================================================
// Released under the MIT License
// Copyright 2017-2018 Natanael Josue Rabello. All rights reserved.
// For the license information refer to LICENSE file in root directory.
// =========================================================================

/**
 * @file mpu_i2c.cpp
 * Example on how to setup MPU through I2C for basic usage.
 */

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

#include "I2Cbus.hpp"
#include "MPU.hpp"
#include "mpu/math.hpp"
#include "mpu/types.hpp"

#include "pins.h"
#include "settings.h"
#include "sharedVariables.h"

extern SharedVariables sharedVariables;

static constexpr uint32_t CLOCK_SPEED = 400000;  // range from 100 KHz ~ 400Hz

MPU_t MPU;  // create a default MPU object
mpud::raw_axes_t accelRaw;   // x, y, z axes as int16
mpud::raw_axes_t gyroRaw;    // x, y, z axes as int16
mpud::float_axes_t accelG;   // accel axes in (g) gravity format
mpud::float_axes_t gyroDPS;  // gyro    axes in (DPS) º/s format
#define TIME_OUT 4
void mpu9250Setup (){
    // Initialize I2C on port 0 using I2Cbus interface
    i2c0.begin(SDA_PIN, SCL_PIN, CLOCK_SPEED);
   

   
    MPU.setBus(i2c0);  // set bus port, not really needed since default is i2c0
    MPU.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);  // set address, default is AD0_LOW

    // Great! Let's verify the communication
    // (this also check if the connected MPU supports the implementation of chip selected in the component menu)
    int counter=0;
    while (MPU.testConnection()) {
        printf( "Failed to connect to the MPU, error");
        vTaskDelay(50 / portTICK_PERIOD_MS);
        counter++;
        if(counter >= TIME_OUT)
        {
            sharedVariables.outputs.MPU9250Working = false;
            printf( "Can't connect, returning");
            return;
        }
    }
    printf( "MPU connection successful!");
    // Initialize
    ESP_ERROR_CHECK(MPU.initialize());  // initialize the chip and set initial configurations
    // Setup with your configurations
     ESP_ERROR_CHECK(MPU.setFchoice(mpud::FCHOICE_3));
     ESP_ERROR_CHECK(MPU.setDigitalLowPassFilter(mpud::DLPF_256HZ_NOLPF));
     ESP_ERROR_CHECK(MPU.setSampleRate(1000)); 
     ESP_ERROR_CHECK(MPU.setGyroFullScale(mpud::GYRO_FS_500DPS));
     ESP_ERROR_CHECK(MPU.setAccelFullScale(mpud::ACCEL_FS_4G));

    MPU.setAuxI2CBypass(true);
}
void mpu9250ReadMotion()
{
      if(sharedVariables.outputs.MPU9250Working!=true) return;
#ifdef PRINT_DURARIONS
      uint32_t startTime=esp_timer_get_time();
#endif
      // Read
      MPU.motion(&accelRaw, &gyroRaw);  // fetch raw data from the registers

      // Convert
      accelG = mpud::accelGravity(accelRaw, mpud::ACCEL_FS_4G);
      gyroDPS = mpud::gyroDegPerSec(gyroRaw, mpud::GYRO_FS_500DPS);

      
      sharedVariables.outputs.acceleration[0] = accelG.x;
      sharedVariables.outputs.acceleration[1] = accelG.y;
      sharedVariables.outputs.acceleration[2] = accelG.z;
      sharedVariables.outputs.gyroValues[0] = gyroDPS.x + 8.0;//substract measure offset
      sharedVariables.outputs.gyroValues[1] = gyroDPS.y - 1.2;//substract measure offset
      sharedVariables.outputs.gyroValues[2] = gyroDPS.z + 0.7;

      
#ifdef PRINT_DURARIONS
        printf("- motionTime: %llu\n",esp_timer_get_time()-startTime);
#endif
#ifdef PRINT_ACCEL
        // Debug
        //printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", accelG.x, accelG.y, accelG.z);
        printf("gyro: [%+7.2f %+7.2f %+7.2f ] (º/s)\n", gyroDPS[0], gyroDPS[1], gyroDPS[2]);
#endif
#ifdef PRINT_MOTION_VISUAL
        printf("%6.2f %6.2f %6.2f ", accelG.x, accelG.y, accelG.z);
        printf("%7.2f %7.2f %7.2f\n", gyroDPS[0], gyroDPS[1], gyroDPS[2]);
#endif
}




#define MAG_MODE_POWERDOWN        0x0
#define MAG_MODE_SINGLE           0x1
#define MAG_MODE_CONTINUOUS_8HZ   0x2
#define MAG_MODE_EXTERNAL         0x4
#define MAG_MODE_CONTINUOUS_100HZ 0x6
#define MAG_MODE_SELFTEST         0x8
#define MAG_MODE_FUSEROM          0xF

#define AK8963_ADDRESS  0x0C
#define AK8963_RA_HXL   0x03
#define AK8963_RA_CNTL1 0x0A
#define AK8963_RA_ASAX 0x10
uint32_t compassLastAngleProcessingTime=0;
void magSetMode(uint8_t mode) {
  i2c0.writeByte(AK8963_ADDRESS, AK8963_RA_CNTL1 , mode);
  vTaskDelay(10);
}

uint8_t magXAdjust, magYAdjust, magZAdjust;
void magReadAdjustValues() {
  magSetMode(MAG_MODE_POWERDOWN);
  magSetMode(MAG_MODE_FUSEROM);
  uint8_t buff[3];
  i2c0.readBytes(AK8963_ADDRESS, AK8963_RA_ASAX, 3, buff);
  magXAdjust = buff[0];
  magYAdjust = buff[1];
  magZAdjust = buff[2];
}
void compassSetup() {//setup only possible if mpu9250 is allready initizalized, otherwise the i2c aux bypass isn't set, see datasheet for reference
   
  if(sharedVariables.outputs.MPU9250Working!=true) 
  {
    printf("can't setup compass because the mpu9250 is not working");
    return;
  }
  magReadAdjustValues();
  magSetMode(MAG_MODE_POWERDOWN);
  magSetMode(MAG_MODE_CONTINUOUS_8HZ);
  vTaskDelay(10);
}
int16_t magGet(uint8_t high, uint8_t low) {
  return (((int16_t) high) << 8) | low;
}
float adjustMagValue(int16_t value, uint8_t adjust) {
  return ((float) value * (((((float) adjust - 128) * 0.5) / 128) + 1));
}


#define complementaryFilter sharedVariables.inputs.complementaryFilter
#define gyroZ sharedVariables.outputs.gyroValues[2]
float unfilteredCompassAngle = 0;
void mpu9250ReadCompass()
{
  if(sharedVariables.outputs.MPU9250Working!=true) return;
#ifdef PRINT_DURARIONS
  uint32_t startTime=esp_timer_get_time();
#endif

  uint8_t magBuf[7];
  i2c0.readBytes(AK8963_ADDRESS, AK8963_RA_HXL, 7, magBuf);
  sharedVariables.outputs.magnetometerValues[0] = adjustMagValue(magGet(magBuf[1], magBuf[0]), magXAdjust)+215;
  sharedVariables.outputs.magnetometerValues[1] = adjustMagValue(magGet(magBuf[3], magBuf[2]), magYAdjust)-540;
  sharedVariables.outputs.magnetometerValues[2] = adjustMagValue(magGet(magBuf[5], magBuf[4]), magZAdjust);
  float compassAngle = atan2(sharedVariables.outputs.magnetometerValues[0], sharedVariables.outputs.magnetometerValues[1])* 57.3;

   uint32_t deltaT = esp_timer_get_time() - compassLastAngleProcessingTime;
   compassLastAngleProcessingTime = esp_timer_get_time();
   //int accelPitch = -atan2(accelX, sqrt(accelY*accelY + accelZ*accelZ))* 57.3;
   
   double gyroAngle = unfilteredCompassAngle + (gyroZ * deltaT / 1000000); // convert angle to angle/deltaT and sum it with roll
   float filterValue = (float)complementaryFilter/1000.0;
   unfilteredCompassAngle = gyroAngle * filterValue + compassAngle * (1-filterValue);

   sharedVariables.outputs.compassAngle += 0.04 * (unfilteredCompassAngle - sharedVariables.outputs.compassAngle);
   #ifdef PRINT_COMPLEMENTARY_COMPASS
   printf("%f, %f,%f\n", sharedVariables.outputs.compassAngle, unfilteredCompassAngle, compassAngle);
   #endif

#ifdef PRINT_DURARIONS
  printf("- compassTime: %llu\n",esp_timer_get_time()-startTime);
#endif
  //printf("%6.2f %6.2f \n", sharedVariables.outputs.magnetometerValues[0],sharedVariables.outputs.magnetometerValues[1]);
#ifdef PRINT_COMPASS
  printf("%f\n",  sharedVariables.outputs.compassAngle);
#endif
}
