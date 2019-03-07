#include "MotorDriver.h"


void MotorDriver::setup(){
    //setup 
     printf("setup led drivers\n");

    ledc_channel_config_t ledc_channel_motor_1;
    ledc_channel_motor_1.gpio_num = 2;
    ledc_channel_motor_1.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_motor_1.channel = LEDC_CHANNEL_0;
    ledc_channel_motor_1.intr_type = LEDC_INTR_DISABLE;
    ledc_channel_motor_1.timer_sel = LEDC_TIMER_0;
    ledc_channel_motor_1.duty = 128;
    ledc_channel_motor_1.hpoint = 0;
	
    ledc_channel_config_t ledc_channel_motor_2;
    ledc_channel_motor_2.gpio_num = 12;
    ledc_channel_motor_2.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_motor_2.channel = LEDC_CHANNEL_1;
    ledc_channel_motor_2.intr_type = LEDC_INTR_DISABLE;
    ledc_channel_motor_2.timer_sel = LEDC_TIMER_1;
    ledc_channel_motor_2.duty = 128;
    ledc_channel_motor_2.hpoint = 0;
	
    ledc_timer_config_t ledc_timer_motor_1;
    ledc_timer_motor_1.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer_motor_1.duty_resolution = LEDC_TIMER_8_BIT;
    ledc_timer_motor_1.timer_num = LEDC_TIMER_0;
    ledc_timer_motor_1.freq_hz = 50;
	
    ledc_timer_config_t ledc_timer_motor_2;
    ledc_timer_motor_2.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer_motor_2.duty_resolution = LEDC_TIMER_8_BIT;
    ledc_timer_motor_2.timer_num = LEDC_TIMER_1;
    ledc_timer_motor_2.freq_hz = 50;
	
	printf(esp_err_to_name(ledc_channel_config(&ledc_channel_motor_1)));
	printf(esp_err_to_name(ledc_channel_config(&ledc_channel_motor_2)));
	printf(esp_err_to_name(ledc_timer_config(&ledc_timer_motor_1)));
    printf(esp_err_to_name(ledc_timer_config(&ledc_timer_motor_2)));
     printf("drivers configured\n");

}
void MotorDriver::setMicroSteppingAutomaticly(bool boolean){

}
void MotorDriver::setMicroStepping(uint8_t microstep){

}
void MotorDriver::setSpeed(uint16_t motor1, uint16_t motor2){

}
void MotorDriver::loop(){
    
}