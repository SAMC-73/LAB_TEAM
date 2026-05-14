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
* @file main.c
* @brief Lab 04 - UART Driver and Serial Communication application.
*
* Initializes the Serial, ADC, and Timer modules. Every 500 ms reads
* the potentiometer connected to PA1 via ADC1 channel 1, computes the
* equivalent voltage in millivolts, and transmits the telemetry over
* USART2 at 115200 baud using serial_printf().
*
* Pin connections:
*   PA1  ->  Potentiometer wiper (ADC1 CH1)
*   PA2  ->  USART2 TX (ST-Link virtual COM port)
*   PA3  ->  USART2 RX
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/

/*** Includes ***/
#include "serial.h"
#include "adc_driver.h"
#include "tim_driver.h"

/*** Preprocessor Definitions ***/
#define BAUD_RATE           115200U     /* USART2 baud rate             */
#define VREF_MV             3300U       /* Reference voltage in mV      */
#define ADC_RESOLUTION      4095U       /* 12-bit ADC maximum value     */
#define SAMPLE_PERIOD_MS    500U        /* Telemetry period in ms       */

/*** Type Prototypes ***/

/*** Local Variables ***/

/*** External Variables ***/

/*** Function Prototypes ***/

/*** Function Definitions ***/

int main(void)
{
    /* Initialize Serial, ADC, and Timer modules */
    serial_init(BAUD_RATE);
    adc_init();
    tim_init();

    /* Print startup header */
    serial_printf("=== Lab 04 - UART Serial Monitor ===\n");
    serial_printf("Baud rate: %u bps | Vref: %u mV\n\n", BAUD_RATE, VREF_MV);

    while (1)
    {
        /* Read potentiometer raw value (0 to 4095) */
        uint16_t adc_value = adc_read();

        /* Convert ADC count to millivolts: V = (adc / 4095) * 3300 */
        uint32_t voltage_mv = ((uint32_t)adc_value * VREF_MV) / ADC_RESOLUTION;

        /* Transmit telemetry over UART */
        serial_printf("ADC Value: %d | Voltage: %d mV\n",
                      (int32_t)adc_value,
                      (int32_t)voltage_mv);

        /* Wait 500 ms before next sample */
        tim_delay_ms(SAMPLE_PERIOD_MS);
    }

    return 0;
}
