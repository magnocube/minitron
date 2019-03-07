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
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "I2Cbus.hpp"
#include "MPU.hpp"
#include "mpu/math.hpp"
#include "mpu/types.hpp"

#include "Arduino.h"
#include "pins.h"
#include "settings.h"
static const char* TAG = "mpu9250";

static constexpr uint32_t CLOCK_SPEED = 400000;  // range from 100 KHz ~ 400Hz

MPU_t MPU;  // create a default MPU object
mpud::raw_axes_t accelRaw;   // x, y, z axes as int16
mpud::raw_axes_t gyroRaw;    // x, y, z axes as int16
mpud::float_axes_t accelG;   // accel axes in (g) gravity format
mpud::float_axes_t gyroDPS;  // gyro    axes in (DPS) º/s format

void mpu9250Setup (){

    // Initialize I2C on port 0 using I2Cbus interface
    i2c0.begin(SDA_PIN, SCL_PIN, CLOCK_SPEED);
   

   
    MPU.setBus(i2c0);  // set bus port, not really needed since default is i2c0
    MPU.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);  // set address, default is AD0_LOW

    // Great! Let's verify the communication
    // (this also check if the connected MPU supports the implementation of chip selected in the component menu)
    while (esp_err_t err = MPU.testConnection()) {
        ESP_LOGE(TAG, "Failed to connect to the MPU, error=%#X", err);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(TAG, "MPU connection successful!");
    // Initialize
    ESP_ERROR_CHECK(MPU.initialize());  // initialize the chip and set initial configurations
    // Setup with your configurations
    // ESP_ERROR_CHECK(MPU.setSampleRate(50));  // set sample rate to 50 Hz
    // ESP_ERROR_CHECK(MPU.setGyroFullScale(mpud::GYRO_FS_500DPS));
    // ESP_ERROR_CHECK(MPU.setAccelFullScale(mpud::ACCEL_FS_4G));

    MPU.setAuxI2CBypass(true);
    
}
void mpu9250ReadMotion()
{
        uint32_t startTime=micros();
        // Read
        MPU.motion(&accelRaw, &gyroRaw);  // fetch raw data from the registers
        // Convert
        accelG = mpud::accelGravity(accelRaw, mpud::ACCEL_FS_4G);
        gyroDPS = mpud::gyroDegPerSec(gyroRaw, mpud::GYRO_FS_500DPS);
#ifdef PRINT_DURARIONS
        printf("- motionTime: %lu\n",micros()-startTime);
#endif
#ifdef PRINT_ACCEL
        // Debug
        printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", accelG.x, accelG.y, accelG.z);
        printf("gyro: [%+7.2f %+7.2f %+7.2f ] (º/s)\n", gyroDPS[0], gyroDPS[1], gyroDPS[2]);
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
void magSetMode(uint8_t mode) {
  i2c0.writeByte(AK8963_ADDRESS, AK8963_RA_CNTL1 , mode);
  delay(10);
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
   
  magReadAdjustValues();
  magSetMode(MAG_MODE_POWERDOWN);
  magSetMode(MAG_MODE_CONTINUOUS_8HZ);
  delay(10);
}
int16_t magGet(uint8_t high, uint8_t low) {
  return (((int16_t) high) << 8) | low;
}
float adjustMagValue(int16_t value, uint8_t adjust) {
  return ((float) value * (((((float) adjust - 128) * 0.5) / 128) + 1));
}
float compassAngle;
void mpu9250ReadCompass()
{
        uint32_t startTime=micros();

  uint8_t magBuf[7];
  i2c0.readBytes(AK8963_ADDRESS, AK8963_RA_HXL, 7, magBuf);
  float magX = adjustMagValue(magGet(magBuf[1], magBuf[0]), magXAdjust);
  float magY = adjustMagValue(magGet(magBuf[3], magBuf[2]), magYAdjust);
  float magZ = adjustMagValue(magGet(magBuf[5], magBuf[4]), magZAdjust);
  compassAngle = atan2(magX, magY)* 180 / 3.14159;

#ifdef PRINT_DURARIONS
  printf("- compassTime: %lu\n",micros()-startTime);
#endif
  //printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", magX, magY, magZ);
#ifdef PRINT_ACCEL
  printf("%f\n", compassAngle);
#endif
}
