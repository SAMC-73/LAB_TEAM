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
* @file tim_driver.h
* @brief Timer delay driver header for STM32F411RE.
*
* This module provides a blocking millisecond delay function
* implemented as a software loop calibrated for the 16 MHz HSI
* default clock of the STM32F411RE microcontroller.
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/
#ifndef __TIM_DRIVER_H__
#define __TIM_DRIVER_H__

/*** Includes ***/
#include <stdint.h>

/*** Preprocessor Definitions ***/

/*** Type Prototypes ***/

/*** Global Variables ***/

/*** Function Prototypes ***/

/**
 * @brief Initializes the timer module.
 *
 * Reserved for future hardware timer configuration.
 * No hardware setup is required for the software delay implementation.
 *
 * @return void
 */
void tim_init(void);

/**
 * @brief Blocking delay in milliseconds.
 *
 * Executes a nested NOP loop to produce an approximate delay.
 * The inner loop is calibrated for the STM32F411 at 16 MHz HSI
 * with -O0 compiler optimization.
 *
 * @param ms Number of milliseconds to wait
 *
 * @return void
 */
void tim_delay_ms(uint32_t ms);

#endif /* __TIM_DRIVER_H__ */
