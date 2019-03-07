

    #include "SerialConnection.h"
    void SerialConnection::setup(){
       
        uart_config_t uart_config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .rx_flow_ctrl_thresh = 122,
            .use_ref_tick = false};

            
        // Configure UART parameters
        ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
        // uart_set_baudrate(uart_num,9600);
        // uart_set_word_length(uart_num,UART_DATA_8_BITS);
        // uart_set_parity(uart_num,UART_PARITY_DISABLE);
        // uart_set_stop_bits(uart_num,UART_STOP_BITS_1);
        // uart_set_hw_flow_ctrl(uart_num,UART_HW_FLOWCTRL_CTS_RTS);
        // uart_set_mode(uart_num,UART_MODE_UART);



        // Set UART pins(TX: IO16 (UART2 default), RX: IO17 (UART2 default), RTS: IO18, CTS: IO19)
        ESP_ERROR_CHECK(uart_set_pin(uart_num, 17, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

        // Setup UART buffered IO with event queue
        const int uart_buffer_size = 256;
        QueueHandle_t uart_queue;
        // Install UART driver using an event queue here
        ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));



        //setup servo
        mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 5);  //gpio 5
  
        printf("Configuring Initial Parameters of mcpwm......\n");
        mcpwm_config_t pwm_config;
        pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
        pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
        pwm_config.cmpr_b = 0;    //duty cycle of PWMxb = 0
        pwm_config.counter_mode = MCPWM_UP_COUNTER;
        pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
        mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
        mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, degreesToPos(180));
        // while (1) {
        //     vTaskDelay(500/portTICK_PERIOD_MS);
        //     for (count = 0; count < SERVO_MAX_DEGREE; count++) {
        //         printf("Angle of rotation: %d\n", count);
        //         angle = degreesToPos(count);
        //         //printf("pulse width: %dus\n", angle);
        //         mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
        //         vTaskDelay(10/portTICK_PERIOD_MS);     //Add delay, since it takes time for servo to rotate, generally 100ms/60degree rotation at 5V
        //     }
        // }

    }
    bool SerialConnection::dataAnvailable(){
        int length = 0;
        uart_get_buffered_data_len(UART_NUM_2, (size_t*)&length);

        if(length > 0){
            return true;
        }
        return false;
    }
    /*
    This function will read all the data anvailable in the serial perhepiral. 
    After it has read the buffers it will send a confirmation back.
    */
    char * SerialConnection::ReadData(){

        
        uint8_t data[256];
        int length = 0;
        ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length));
        length = uart_read_bytes(uart_num, data, length, 100);

        printf("received uart data\n");
        printf((char*)data);
        
        char* test_str = "confirmed.\n";
        uart_write_bytes(uart_num, (const char*)test_str, strlen(test_str));
        return NULL;
    }

    void SerialConnection::sendData(char * data){

        uart_write_bytes(uart_num, (const char*)data, strlen(data));
    }

    void SerialConnection::setCameraAngle(int degrees){
                pos = degrees;
                int angle = degreesToPos(degrees);
                //printf("pulse width: %dus\n", angle);
                mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle);
    }
	int SerialConnection::getCameraAngle(){
        return pos;
    }
    int SerialConnection::degreesToPos(int degree_of_rotation){
        int cal_pulsewidth = 0;
        cal_pulsewidth = (SERVO_MIN_PULSEWIDTH + (((SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
        return cal_pulsewidth;
    }