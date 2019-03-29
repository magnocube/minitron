deps_config := \
	D:\synced_folder\Tinlab\minitron\esp32_firmware\components\I2Cbus\Kconfig \
	D:\synced_folder\Tinlab\minitron\esp32_firmware\components\MPUdriver\Kconfig \
	C:\esp\esp-idf\components\app_trace\Kconfig \
	C:\esp\esp-idf\components\aws_iot\Kconfig \
	C:\esp\esp-idf\components\bt\Kconfig \
	C:\esp\esp-idf\components\driver\Kconfig \
	C:\esp\esp-idf\components\esp32\Kconfig \
	C:\esp\esp-idf\components\esp_adc_cal\Kconfig \
	C:\esp\esp-idf\components\esp_event\Kconfig \
	C:\esp\esp-idf\components\esp_http_client\Kconfig \
	C:\esp\esp-idf\components\esp_http_server\Kconfig \
	C:\esp\esp-idf\components\ethernet\Kconfig \
	C:\esp\esp-idf\components\fatfs\Kconfig \
	C:\esp\esp-idf\components\freemodbus\Kconfig \
	C:\esp\esp-idf\components\freertos\Kconfig \
	C:\esp\esp-idf\components\heap\Kconfig \
	C:\esp\esp-idf\components\libsodium\Kconfig \
	C:\esp\esp-idf\components\log\Kconfig \
	C:\esp\esp-idf\components\lwip\Kconfig \
	C:\esp\esp-idf\components\mbedtls\Kconfig \
	C:\esp\esp-idf\components\mdns\Kconfig \
	C:\esp\esp-idf\components\mqtt\Kconfig \
	C:\esp\esp-idf\components\nvs_flash\Kconfig \
	C:\esp\esp-idf\components\openssl\Kconfig \
	C:\esp\esp-idf\components\pthread\Kconfig \
	C:\esp\esp-idf\components\spi_flash\Kconfig \
	C:\esp\esp-idf\components\spiffs\Kconfig \
	C:\esp\esp-idf\components\tcpip_adapter\Kconfig \
	C:\esp\esp-idf\components\unity\Kconfig \
	C:\esp\esp-idf\components\vfs\Kconfig \
	C:\esp\esp-idf\components\wear_levelling\Kconfig \
	D:\synced_folder\Tinlab\minitron\esp32_firmware\components\I2Cbus\Kconfig.projbuild \
	D:\synced_folder\Tinlab\minitron\esp32_firmware\components\MPUdriver\Kconfig.projbuild \
	C:\esp\esp-idf\components\app_update\Kconfig.projbuild \
	C:\esp\esp-idf\components\bootloader\Kconfig.projbuild \
	C:\esp\esp-idf\components\esptool_py\Kconfig.projbuild \
	C:\esp\esp-idf\components\partition_table\Kconfig.projbuild \
	/c/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
