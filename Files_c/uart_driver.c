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
* @file uart_driver.c
* @brief UART Driver implementation for STM32F411RE.
*
* Configures USART2 on PA2 (TX) and PA3 (RX) using the existing
* GPIO driver. The system clock source is HSI at 16 MHz. Implements
* all five functional requirements from the UART SRS (FR-1 to FR-5).
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/

/*** Includes ***/
#include "uart_driver.h"
#include "SRS_GPIO_DRIVER.h"
#include "stm32f4xx.h"

/*** Preprocessor Definitions ***/
#define SYSCLK_HZ   16000000UL  /* Default HSI clock frequency: 16 MHz */

/*** Type Prototypes ***/

/*** Local Variables ***/

/*** External Variables ***/

/*** Function Prototypes ***/

/*** Function Definitions ***/

void uart_init(uint32_t baud_rate)
{
    /* Enable USART2 clock on APB1 bus */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /* Configure PA2 (TX) and PA3 (RX) as Alternate Function using GPIO driver */
    gpio_initPort(A);
    gpio_setAlternateFunction(A, 2);    /* PA2 = USART2 TX */
    gpio_setAlternateFunction(A, 3);    /* PA3 = USART2 RX */

    /* Set AF7 (USART2) for PA2 and PA3 in AFR[0] register */
    GPIOA->AFR[0] &= ~((0xFU << 8U) | (0xFU << 12U));
    GPIOA->AFR[0] |=  ((0x7U << 8U) | (0x7U << 12U));

    /* Disable USART2 before applying configuration */
    USART2->CR1 &= ~USART_CR1_UE;

    /* Configure baud rate: BRR = fclk / baud_rate */
    USART2->BRR = SYSCLK_HZ / baud_rate;

    /* Enable transmitter, receiver, and USART peripheral */
    USART2->CR1 = USART_CR1_TE     /* Transmitter Enable */
                | USART_CR1_RE     /* Receiver Enable    */
                | USART_CR1_UE;    /* USART Enable       */
}

void uart_send_byte(uint8_t data)
{
    /* Wait until Transmit Data Register is empty (TXE = 1) */
    while (!uart_tx_ready());

    /* Write byte to the data register */
    USART2->DR = data;
}

void uart_send_string(const char *str)
{
    /* Transmit each character until null terminator */
    while (*str)
    {
        uart_send_byte((uint8_t)*str);
        str++;
    }
}

uint8_t uart_tx_ready(void)
{
    /* Return 1 if TXE flag is set in the Status Register */
    return (USART2->SR & USART_SR_TXE) ? 1U : 0U;
}

void uart_disable(void)
{
    /* Clear UE bit to disable USART2 */
    USART2->CR1 &= ~USART_CR1_UE;
}
