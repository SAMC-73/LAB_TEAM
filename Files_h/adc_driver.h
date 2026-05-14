/******************************************************************************
* Copyright (C) 2026 by Carlos Villarreal - CETYS Universidad
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Carlos Villarreal and CETYS Universidad are not liable for any
* misuse of this material.
*
*****************************************************************************/
/**
* @file adc_driver.h
* @brief ADC Driver header for STM32F411RE.
*
* This module declares the ADC1 driver interface. It configures
* channel 1 on PA1 for reading an analog potentiometer in single
* conversion mode with 12-bit resolution (0 to 4095).
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/
#ifndef __ADC_DRIVER_H__
#define __ADC_DRIVER_H__

/*** Includes ***/
#include <stdint.h>

/*** Preprocessor Definitions ***/

/*** Type Prototypes ***/

/*** Global Variables ***/

/*** Function Prototypes ***/

/**
 * @brief Initializes ADC1 on channel 1 (PA1).
 *
 * Enables clocks for GPIOA and ADC1, configures PA1 as analog
 * input, sets the conversion sequence to channel 1, configures
 * the sample time, and enables the ADC peripheral.
 *
 * @return void
 */
void adc_init(void);

/**
 * @brief Performs a single ADC conversion and returns the result.
 *
 * Triggers a software-started conversion, waits for the End Of
 * Conversion (EOC) flag, and returns the 12-bit result from the
 * data register.
 *
 * @return 12-bit ADC conversion result (0 to 4095)
 */
uint16_t adc_read(void);

#endif /* __ADC_DRIVER_H__ */
