#include "MotorDriver.h"


void MotorDriver::setup(){
    //setup 
    motor1Speed = 0;
    motor2Speed = 0;
    motor1OldSpeed = 0;
    motor2OldSpeed = 0;
    steppers->acceleration = 15000;
    steppers->acceleration_motor1 = 15000;
    steppers->acceleration_motor2 = 15000;
    

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

void MotorDriver::setAcceleration(uint32_t a, uint32_t a2){
    steppers->acceleration_motor1 = a;
    steppers->acceleration_motor2 = a2;
}
void MotorDriver::setAcceleration(uint32_t acceleration){
    steppers->acceleration = acceleration;
    calculateInduvidualAcceleration();
}

void MotorDriver::setTargetSpeed(int32_t motor1, int32_t motor2){
    steppers->motor1TargetSpeed = motor1;
    steppers->motor2TargetSpeed = motor2;
    calculateInduvidualAcceleration();
}
void MotorDriver::calculateInduvidualAcceleration()
{
    double delta1 = abs(steppers->motor1TargetSpeed - motor1Speed);
    double delta2 = abs(steppers->motor2TargetSpeed - motor2Speed);

    if(delta1 > delta2)
    {
        steppers->acceleration_motor1  = steppers->acceleration;
        steppers->acceleration_motor2  = steppers->acceleration * (delta2 / delta1);
    }
    else if(delta1 < delta2)
    {
        steppers->acceleration_motor2  = steppers->acceleration;
        steppers->acceleration_motor1  = steppers->acceleration * (delta1 / delta2);
    }
    else
    {
        steppers->acceleration_motor1  = steppers->acceleration;
        steppers->acceleration_motor2  = steppers->acceleration;
    }
    
}
void MotorDriver::setSpeed(int32_t motor1, int32_t motor2){
    if(motor1==0)
    {
        motor1=10;
    }
    if(motor2==0)
    {
        motor2=10;
    }
    ledc_timer_motor_1.freq_hz = motor1;
    ledc_timer_config(&ledc_timer_motor_1);
    ledc_timer_motor_2.freq_hz = motor2;
    ledc_timer_config(&ledc_timer_motor_2);
}
void MotorDriver::loop(){
    uint64_t currentTime = esp_timer_get_time();
    uint32_t deltaT = currentTime - lastTimeSincePreviousLoop;  //if this requires a 64 bit variable there is something good wrong..  (manual driving might cause errors... )
    lastTimeSincePreviousLoop = currentTime;

    double maxSpeedToAddMotor1= steppers->acceleration_motor1 * deltaT / 1000000;   //acceleration is in seconds, deltaT is in microSeconds.
    double maxSpeedToAddMotor2= steppers->acceleration_motor2 * deltaT / 1000000;   //acceleration is in seconds, deltaT is in microSeconds.
   


    if(abs(steppers->motor1TargetSpeed - motor1Speed) > maxSpeedToAddMotor1){  //possible to add full acceleration
        if(steppers->motor1TargetSpeed > motor1Speed){ //accelerating
            motor1Speed += maxSpeedToAddMotor1;
        } else{                              //decelerating
            motor1Speed -= maxSpeedToAddMotor1;
        }        
    } else {
        motor1Speed = steppers->motor1TargetSpeed;
    }

    if(abs(steppers->motor2TargetSpeed - motor2Speed) > maxSpeedToAddMotor2){  //possible to add full acceleration
        if(steppers->motor2TargetSpeed > motor2Speed){ //accelerating
            motor2Speed += maxSpeedToAddMotor2;
        } else{                              //decelerating
            motor2Speed -= maxSpeedToAddMotor2;
        }        
    } else {
        motor2Speed = steppers->motor2TargetSpeed;        
    }

    if((motor1Speed < 0) && (motor1OldSpeed >=0)){
        gpio_set_level(MOTOR_1_DIRECTION_PIN, BACKWARD_MOTOR_1);
    } else if((motor1Speed > 0 )&& (motor1OldSpeed <=0)){
        gpio_set_level(MOTOR_1_DIRECTION_PIN, FORWARD_MOTOR_1);
    }

    if((motor2Speed < 0) && (motor2OldSpeed >=0)){
        gpio_set_level(MOTOR_2_DIRECTION_PIN, BACKWARD_MOTOR_2);
    } else if((motor2Speed > 0) && (motor2OldSpeed <=0)){
        gpio_set_level(MOTOR_2_DIRECTION_PIN, FORWARD_MOTOR_2);
    }
    
    setSpeed(abs((int32_t)motor1Speed),abs((int32_t)motor2Speed));

    motor1OldSpeed = motor1Speed;
    motor2OldSpeed = motor2Speed;

}
	void MotorDriver::setMotorDriverEnabled(bool b){
        steppers->motorsEnabled = b;
        
        //enable signal on IO
        if(steppers->motorsEnabled){
            gpio_set_level(MOTOR_ENABLE_PIN, 0);
        }else{
            gpio_set_level(MOTOR_ENABLE_PIN, 1);
        }
        
    }
	bool MotorDriver::isMotorDriverEnabled(){
        return steppers->motorsEnabled;
    }
	int32_t MotorDriver::getMotor1TargetSpeed(){
        return steppers->motor1TargetSpeed;
    }
	int32_t MotorDriver::getMotor2TargetSpeed(){
        return steppers->motor2TargetSpeed;
    }
	int32_t MotorDriver::getMotor1Speed(){
        return motor1Speed;
    }
	int32_t MotorDriver::getMotor2Speed(){
        return motor2Speed;
    }
