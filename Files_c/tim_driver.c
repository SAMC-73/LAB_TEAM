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
* @file tim_driver.c
* @brief Timer delay driver implementation for STM32F411RE.
*
* Implements a software-based millisecond delay using nested NOP loops.
* The inner iteration count (CYCLES_PER_MS) is calibrated for the HSI
* clock at 16 MHz with -O0 compiler optimization level.
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/

/*** Includes ***/
#include "tim_driver.h"

/*** Preprocessor Definitions ***/
#define CYCLES_PER_MS   3200U   /* NOP iterations per ms at 16 MHz, -O0 */

/*** Type Prototypes ***/

/*** Local Variables ***/

/*** External Variables ***/

/*** Function Prototypes ***/

/*** Function Definitions ***/

void tim_init(void)
{
    /* No hardware configuration required for software delay */
}

void tim_delay_ms(uint32_t ms)
{
    for (uint32_t i = 0U; i < ms; i++)
    {
        for (volatile uint32_t j = 0U; j < CYCLES_PER_MS; j++)
        {
            __asm__("nop");
        }
    }
}
