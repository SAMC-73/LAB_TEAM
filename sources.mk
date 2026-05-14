# sources.mk - Lab 04 UART Driver
# Agrega los nuevos modulos al proyecto base del Lab 01

SRC_DIR     = Files_c
INCLUDE_DIR = Files_h

# Source files
SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/stm32_startup.c \
	$(SRC_DIR)/system_stm32f4xx.c \
	$(SRC_DIR)/SRS_GPIO_DRIVER.c \
	$(SRC_DIR)/uart_driver.c \
	$(SRC_DIR)/serial.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/tim_driver.c \
	$(SRC_DIR)/adc_driver.c

# Include directories
INCLUDES = \
	-I$(INCLUDE_DIR) \
	-I./CMSIS/STM32F4xx/Include \
	-I./CMSIS/Core/Include \
	-I./STM_files
