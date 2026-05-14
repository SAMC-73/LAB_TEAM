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
* @file uart_driver.h
* @brief UART Driver header for STM32F411RE.
*
* This module declares the low-level UART driver interface for USART2.
* It configures the peripheral on PA2 (TX) and PA3 (RX) and provides
* functions for byte and string transmission over serial communication.
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/
#ifndef __UART_DRIVER_H__
#define __UART_DRIVER_H__

/*** Includes ***/
#include <stdint.h>

/*** Preprocessor Definitions ***/

/*** Type Prototypes ***/

/*** Global Variables ***/

/*** Function Prototypes ***/

/**
 * @brief Initializes USART2 with the specified baud rate.
 *
 * Enables the USART2 and GPIOA clocks, configures PA2 as TX and PA3
 * as RX in alternate function mode (AF7), and sets the baud rate
 * register. Enables the transmitter, receiver, and USART peripheral.
 *
 * @param baud_rate Desired baud rate in bits per second (e.g. 115200)
 *
 * @return void
 */
void uart_init(uint32_t baud_rate);

/**
 * @brief Transmits a single byte over USART2.
 *
 * Waits until the transmit data register is empty (TXE flag),
 * then writes the byte to the data register.
 *
 * @param data Byte value to transmit
 *
 * @return void
 */
void uart_send_byte(uint8_t data);

/**
 * @brief Transmits a null-terminated string over USART2.
 *
 * Iterates over each character of the string and calls
 * uart_send_byte() until the null terminator is reached.
 *
 * @param str Pointer to the null-terminated string to transmit
 *
 * @return void
 */
void uart_send_string(const char *str);

/**
 * @brief Checks whether the USART2 transmit register is ready.
 *
 * Reads the TXE bit from the USART2 status register (SR).
 *
 * @return 1 if the transmit data register is empty and ready, 0 otherwise
 */
uint8_t uart_tx_ready(void);

/**
 * @brief Disables the USART2 peripheral.
 *
 * Clears the UE bit in the CR1 register, disabling USART2.
 *
 * @return void
 */
void uart_disable(void);

#endif /* __UART_DRIVER_H__ */
