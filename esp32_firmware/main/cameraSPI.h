#pragma once

#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "driver/spi_slave.h"
#include "esp_heap_caps.h"
#include "pins.h"
#include "settings.h"

#define GPIO_MOSI GPIO_NUM_23
#define GPIO_MISO GPIO_NUM_19
#define GPIO_SCLK GPIO_NUM_18
#define GPIO_CS GPIO_NUM_5
#define BUFFER_SIZE 2048
spi_slave_transaction_t* t;
uint32_t *recvbuf;
void spiSetup()
{
	printf("setup spi\n");

	spi_bus_config_t buscfg={
        mosi_io_num : GPIO_MOSI,
        miso_io_num : GPIO_MISO,
        sclk_io_num : GPIO_SCLK,
        quadwp_io_num : -1,
        quadhd_io_num : -1,
        max_transfer_sz : 0,
        flags : SPICOMMON_BUSFLAG_SLAVE
      	};
	spi_slave_interface_config_t slvcfg={
		spics_io_num : GPIO_CS,
		flags : 0,
		queue_size : 8,
        mode : 0,
        post_setup_cb : NULL,
        post_trans_cb : NULL
	};
	gpio_set_pull_mode(GPIO_MOSI, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(GPIO_SCLK, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(GPIO_CS, GPIO_PULLUP_ONLY);

	esp_err_t ret = spi_slave_initialize(VSPI_HOST, &buscfg, &slvcfg, 2);
    assert(ret==ESP_OK);

    recvbuf = (uint32_t*)heap_caps_malloc(BUFFER_SIZE, MALLOC_CAP_DMA);

	t = new spi_slave_transaction_t;
	t->length=BUFFER_SIZE*8;
	t->tx_buffer=NULL;
	t->rx_buffer=recvbuf;
	ESP_ERROR_CHECK(spi_slave_queue_trans(VSPI_HOST, t, portMAX_DELAY));


}
void spiRead()
{
	esp_err_t status = spi_slave_get_trans_result(VSPI_HOST, &t, 0);	
	if(status == ESP_OK)
	{
	printf("read %d\n",t->trans_len);

		for(int i = 0; i < t->trans_len/8; i++)
		{
			printf("%u,",recvbuf[i]);	
			recvbuf[i]=0;
		}
		printf("\n");

		t->trans_len=0;
		t->length=BUFFER_SIZE*8;
		t->tx_buffer=NULL;
		t->rx_buffer=recvbuf;
		ESP_ERROR_CHECK(spi_slave_queue_trans(VSPI_HOST, t, portMAX_DELAY));
	}
}