/**
 * @file SRS_ADC_DRIVER.h
 * @brief Module that manipulates the ADC peripherals that the 
 * development board may use.
 * 
 * The user may use multiple functions to indicate the development board
 * which ADC resgister it will use.
 *
 * @author Steven McClellan
 * @date 05/13/2026
 *
 */

/* INCLUDES */
#include <stdint.h>
#include "stm32f4xx.h"

/* Declaring enum for ease of access from other files*/
typedef enum adc{
    status,
    control1,
    control2,
    reg_data,
    c_control,
    r_sequence1,
    r_sequence2,
    r_sequence3,
    i_sequence,
    i_chan1,
    i_chan2,
    i_chan3,
    i_chan4,
    SIZE
}adc_g;

/* Declaring universal array and size of array for ADC addresses, array is volatile 
to ensure the correct address storage on each element of the array*/
extern volatile uint32_t *ADC_arr[SIZE];

// Declaring all functions

/* This register will initialize all ADC peripherals in it's default state */
void adc_init(void);

/* This function shall enable clocking for the ADC */
void adc_enableAdc(void);

/* This function allows the selection of a valid ADC channel */
uint32_t adc_setChannel(uint8_t channel);

/* This function allows the selection of a valid ADC channel */
uint32_t adc_setInjectedChannel(uint8_t channel);

/* This function will start a single conversion on the DR register */
uint32_t adc_startSingleConversion(void);

/* This function will start the continous conversion on the DR register */
uint32_t adc_startContinousConversion(void);

/* This function will start conversion on the injected channels */
uint32_t adc_startInjectedConversion(void);

/* This function shall read the bits on the DR register  */
uint32_t adc_readData(uint16_t *data);

/* This function shall read the bits of the specified JDR register */
uint32_t adc_readInjectedChannelData(uint8_t channel, uint16_t *data);

