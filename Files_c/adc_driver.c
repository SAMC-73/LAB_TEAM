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
* @file adc_driver.c
* @brief ADC Driver implementation for STM32F411RE.
*
* Configures ADC1 on PA1 (channel 1) in single conversion mode
* with 12-bit resolution and software trigger. Uses CMSIS register
* definitions for RCC, GPIOA, and ADC1 peripherals.
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/

/*** Includes ***/
#include "adc_driver.h"
#include "stm32f4xx.h"

/*** Preprocessor Definitions ***/

/*** Type Prototypes ***/

/*** Local Variables ***/

/*** External Variables ***/

/*** Function Prototypes ***/

/*** Function Definitions ***/

void adc_init(void)
{
    /* Enable GPIOA clock on AHB1 bus */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* Enable ADC1 clock on APB2 bus */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* Configure PA1 as analog input (MODER bits [3:2] = 11) */
    GPIOA->MODER |= (3U << (1U * 2U));

    /* Reset ADC control registers */
    ADC1->CR1 = 0U;
    ADC1->CR2 = 0U;

    /* Set channel 1 as the single conversion in the sequence */
    ADC1->SQR3 = 1U;    /* First (and only) conversion: channel 1 */
    ADC1->SQR1 = 0U;    /* Total sequence length = 1 conversion    */

    /* Sample time for channel 1: 84 cycles (bits [5:3] in SMPR2) */
    ADC1->SMPR2 |= (4U << 3U);

    /* Enable ADC1 peripheral */
    ADC1->CR2 |= ADC_CR2_ADON;
}

uint16_t adc_read(void)
{
    /* Trigger software conversion */
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* Wait for End Of Conversion flag (EOC) */
    while (!(ADC1->SR & ADC_SR_EOC));

    /* Return lower 12 bits of the data register */
    return (uint16_t)(ADC1->DR & 0x0FFFU);
}
