#include "MotorDriver.h"


void MotorDriver::setup(){
    //setup 
    motor1Speed = 0;
    motor2Speed = 0;
    motor1OldSpeed = 0;
    motor2OldSpeed = 0;
    acceleration_motor1 = 15000;
    acceleration_motor2 = 15000;
    

    gpio_pad_select_gpio(MOTOR_ENABLE_PIN);
    gpio_pad_select_gpio(MOTOR_1_DIRECTION_PIN);
    gpio_pad_select_gpio(MOTOR_2_DIRECTION_PIN);
    gpio_pad_select_gpio(MOTOR_MICROSTEP_1);
    gpio_pad_select_gpio(MOTOR_MICROSTEP_2);
    gpio_pad_select_gpio(MOTOR_MICROSTEP_3);
   // gpio_pad_select_gpio(MOTOR_1_STEP_PIN);    //done by ledc driver
   // gpio_pad_select_gpio(MOTOR_2_STEP_PIN);

    gpio_set_direction(MOTOR_ENABLE_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_1_DIRECTION_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_2_DIRECTION_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_MICROSTEP_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_MICROSTEP_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR_MICROSTEP_3, GPIO_MODE_OUTPUT);
  //  gpio_set_direction(MOTOR_1_STEP_PIN, GPIO_MODE_OUTPUT);
  //gpio_set_direction(MOTOR_2_STEP_PIN, GPIO_MODE_OUTPUT);
    
    setMotorDriverEnabled(false);
    gpio_set_level(MOTOR_MICROSTEP_1, 1);
    gpio_set_level(MOTOR_MICROSTEP_2, 1);
    gpio_set_level(MOTOR_MICROSTEP_3, 1);
    gpio_set_level(MOTOR_1_DIRECTION_PIN, FORWARD_MOTOR_1);
    gpio_set_level(MOTOR_2_DIRECTION_PIN, FORWARD_MOTOR_2);
   
    

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
	
    
    ledc_timer_motor_1.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer_motor_1.duty_resolution = LEDC_TIMER_8_BIT;
    ledc_timer_motor_1.timer_num = LEDC_TIMER_0;
    ledc_timer_motor_1.freq_hz = motor1Speed;
	
    
    ledc_timer_motor_2.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer_motor_2.duty_resolution = LEDC_TIMER_8_BIT;
    ledc_timer_motor_2.timer_num = LEDC_TIMER_1;
    ledc_timer_motor_2.freq_hz = motor2Speed;
	
	printf(esp_err_to_name(ledc_channel_config(&ledc_channel_motor_1)));
	printf(esp_err_to_name(ledc_channel_config(&ledc_channel_motor_2)));
	printf(esp_err_to_name(ledc_timer_config(&ledc_timer_motor_1)));
    printf(esp_err_to_name(ledc_timer_config(&ledc_timer_motor_2)));
     printf("drivers configured\n");

}

void MotorDriver::setAcceleration(int a, int a2){
    acceleration_motor1 = a;
    acceleration_motor2 = a2;
}


void MotorDriver::setTargetSpeed(int32_t motor1, int32_t motor2){
    motor1TargetSpeed = motor1;
    motor2TargetSpeed = motor2;

}
void MotorDriver::setSpeed(uint16_t motor1, uint16_t motor2){
    ledc_timer_motor_1.freq_hz = motor1;
    ledc_timer_motor_2.freq_hz = motor2;
    ledc_timer_config(&ledc_timer_motor_1);
    ledc_timer_config(&ledc_timer_motor_2);
    

}
void MotorDriver::loop(){
    uint64_t currentTime = esp_timer_get_time();
    uint32_t deltaT = currentTime - lastTimeSincePreviousLoop;  //if this requires a 64 bit variable there is something good wrong..  (manual driving might cause errors... )
    lastTimeSincePreviousLoop = currentTime;

    float maxSpeedToAddMotor1= acceleration_motor1 * deltaT / 1000000;   //acceleration is in seconds, deltaT is in microSeconds.
    float maxSpeedToAddMotor2= acceleration_motor2 * deltaT / 1000000;   //acceleration is in seconds, deltaT is in microSeconds.
   


    if(abs(motor1TargetSpeed - motor1Speed) > maxSpeedToAddMotor1){  //possible to add full acceleration
        if(motor1TargetSpeed > motor1Speed){ //accelerating
            motor1Speed = motor1Speed + maxSpeedToAddMotor1;
        } else{                              //decelerating
            motor1Speed = motor1Speed - maxSpeedToAddMotor1;
        }        
    } else {
        motor1Speed = motor1TargetSpeed;        
    }

    if(abs(motor2TargetSpeed - motor2Speed) > maxSpeedToAddMotor2){  //possible to add full acceleration
        if(motor2TargetSpeed > motor2Speed){ //accelerating
            motor2Speed = motor2Speed + maxSpeedToAddMotor2;
        } else{                              //decelerating
            motor2Speed = motor2Speed - maxSpeedToAddMotor2;
        }        
    } else {
        motor2Speed = motor2TargetSpeed;        
    }

    if(motor1Speed < 0 && motor1OldSpeed >=0){
        gpio_set_level(MOTOR_1_DIRECTION_PIN, BACKWARD_MOTOR_1);
    } else if(motor1Speed > 0 && motor1OldSpeed <=0){
        gpio_set_level(MOTOR_1_DIRECTION_PIN, FORWARD_MOTOR_1);
    }

    if(motor2Speed < 0 && motor2OldSpeed >=0){
        gpio_set_level(MOTOR_2_DIRECTION_PIN, BACKWARD_MOTOR_2);
    } else if(motor2Speed > 0 && motor2OldSpeed <=0){
        gpio_set_level(MOTOR_2_DIRECTION_PIN, FORWARD_MOTOR_2);
    }
    

    setSpeed(abs((int)motor1Speed),abs((int)motor2Speed));

    motor1OldSpeed = motor1Speed;
    motor2OldSpeed = motor2Speed;

}
	void MotorDriver::setMotorDriverEnabled(bool b){
        motorsEnabled = b;
        //enable signal on IO
        if(motorsEnabled){
            gpio_set_level(MOTOR_ENABLE_PIN, 0);
        }else{
            gpio_set_level(MOTOR_ENABLE_PIN, 1);
        }
        
    }
	bool MotorDriver::isMotorDriverEnabled(){
        return motorsEnabled;
    }
	uint16_t MotorDriver::getMotor1TargetSpeed(){
        return motor1TargetSpeed;
    }
	uint16_t MotorDriver::getMotor2TargetSpeed(){
        return motor2TargetSpeed;
    }
	uint16_t MotorDriver::getMotor1Speed(){
        return motor1Speed;
    }
	uint16_t MotorDriver::getMotor2Speed(){
        return motor2Speed;
    }
