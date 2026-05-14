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
* @file serial.h
* @brief High-level Serial communication module header.
*
* This module provides a printf-like API for terminal communication.
* It uses the UART driver for transmission and the Utils module for
* number-to-string formatting, abstracting low-level UART operations.
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/
#ifndef __SERIAL_H__
#define __SERIAL_H__

/*** Includes ***/
#include <stdint.h>

/*** Preprocessor Definitions ***/

/*** Type Prototypes ***/

/*** Global Variables ***/

/*** Function Prototypes ***/

/**
 * @brief Initializes the Serial module.
 *
 * Calls uart_init() with the specified baud rate to configure
 * USART2 for serial communication.
 *
 * @param baud_rate Desired baud rate in bits per second (e.g. 115200)
 *
 * @return void
 */
void serial_init(uint32_t baud_rate);

/**
 * @brief Sends a formatted string over UART.
 *
 * Parses the format string and replaces format specifiers with their
 * corresponding values using utils_itoa() for numeric conversion.
 * Supported specifiers: %d (signed), %u (unsigned), %x (hex),
 * %s (string), %c (character).
 *
 * @param fmt Pointer to the null-terminated format string
 * @param ... Variable arguments corresponding to format specifiers
 *
 * @return void
 */
void serial_printf(const char *fmt, ...);

#endif /* __SERIAL_H__ */
