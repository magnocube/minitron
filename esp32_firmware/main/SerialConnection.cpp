

    #include "SerialConnection.h"
    void SerialConnection::setup(){
        const uart_port_t uart_num = UART_NUM_2;
        uart_config_t uart_config = {
            .baud_rate = 9600,
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
    }
    bool SerialConnection::dataAnvailable(){
        int length = 0;
        uart_get_buffered_data_len(UART_NUM_2, (size_t*)&length);

        if(length > 0){
            return true;
        }
        return false;
    }
    char * SerialConnection::ReadData(){

        const uart_port_t uart_num = UART_NUM_2;
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