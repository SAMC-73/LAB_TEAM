/**
 * @file SRS_ADC_DRIVER.c
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
#include "SRS_ADC_DRIVER.h"

/* Declaring static variable for adc_setChannel*/
static uint8_t adc_channel_length = 0;

/* Declaring static variable for adc_setInjectedChannel*/
static uint8_t adc_injected_length = 0;

/* Declaring universal array and size of array for ADC addresses, array is volatile 
to ensure the correct address storage on each element of the array*/
volatile uint32_t* ADC_arr[SIZE];


/* This register will initialize the ADC subsystem in it's default state */
void adc_init(void){
    ADC_arr[0] =   &ADC1->SR;
    ADC_arr[1] =   &ADC1->CR1;
    ADC_arr[2] =   &ADC1->CR2;
    ADC_arr[3] =   &ADC1->DR;
    ADC_arr[4] =   &ADC->CCR;
    ADC_arr[5] =   &ADC1->SQR1;
    ADC_arr[6] =   &ADC1->SQR2;
    ADC_arr[7] =   &ADC1->SQR3;
    ADC_arr[8] =   &ADC1->JSQR;
    ADC_arr[9] =   &ADC1->JDR1;
    ADC_arr[10] =  &ADC1->JDR2;
    ADC_arr[11] =  &ADC1->JDR3;
    ADC_arr[12] =  &ADC1->JDR4;
}


/* This function shall enable clocking for the ADC */
void adc_enableAdc(void){
    // Enables the ADC 
    RCC->APB2ENR |= (1U << 8);

    // Enable ADC (ADON bit)
    *ADC_arr[2] |= (1U << 0);
}

/* This function allows the selection of a valid ADC channel */
uint32_t adc_setChannel(uint8_t channel)
{
    // Confirms that input is a valid channel number
    if (channel > 18) return 1;

    // Validates if there is space for another channel
    if (adc_channel_length >= 16) return 1;

    volatile uint32_t *sqr; // Volatile variable to ensure the correct address is used
    uint8_t position;       // Local variable for position
    uint8_t shift;          // Local variable for shift

    position = adc_channel_length + 1;  // This variable represent the position of the new channel to be created

    if (position <= 6) // If the position is lower or equal to 6 register SQR3 will be used
    {
        sqr = ADC_arr[7];           // SQR3
        shift = (position - 1) * 5; // Adjusting shift to ensure the channel gets overwritten on the correct position
        // Shift gets multiplied by 5 because each channel takes 5 bits
    }
    else if (position <= 12) // If the position is lower or equal to 12 register SQR2 will be used
    {
        sqr = ADC_arr[6];    // SQR2
        shift = (position - 7) * 5;
    }
    else // If none is the case then SQR1 will be used instead
    {
        sqr = ADC_arr[5]; // SQR1
        shift = (position - 13) * 5;
    }

    // Clear previous channel
    *sqr &= ~(0x1FU << shift);

    // Set channel
    *sqr |= (channel << shift);

    adc_channel_length++; // Adjusting the channel length

    // Update L bits in SQR1
    *ADC_arr[5] &= ~(0xFU << 20);
    *ADC_arr[5] |= ((adc_channel_length - 1) << 20);

    return 0;
}

/* This function allows the selection of a valid ADC injected channel */
uint32_t adc_setInjectedChannel(uint8_t channel)
{
    // Confirms that input is a valid channel number
    if (channel > 18) return 1;

    // Maximum injected sequence length = 4
    if (adc_injected_length >= 4) return 1;

    /*
     * JSQR organization:
     *
     * JSQ1 -> bits [4:0]
     * JSQ2 -> bits [9:5]
     * JSQ3 -> bits [14:10]
     * JSQ4 -> bits [19:15]
     *
     * JL -> bits [21:20]
     */

    // Declaring local variable for position manipulation 
    uint8_t position = adc_injected_length + 1;

    // Calculate shift for JSQx field
    uint8_t shift = (position - 1) * 5;

    // Clear previous channel
    *ADC_arr[8] &= ~(0x1FU << shift);

    // Set injected channel
    *ADC_arr[8] |= (channel << shift);

    // Increase injected sequence length
    adc_injected_length++;

    // Update JL bits [21:20]
    *ADC_arr[8] &= ~(0x3U << 20);
    *ADC_arr[8] |= ((adc_injected_length - 1) << 20);

    return 0;
}

/* This function will start a single conversion on the DR register */
    uint32_t adc_startSingleConversion(void){

    // Fail if no regular channels configured
    if(adc_channel_length == 0) return 1;



    // // Clear EOC flag before starting conversion
    // *ADC_arr[0] &= ~(1U << 1);

    // Start regular conversion
    *ADC_arr[2] |= (1U << 30);

    return 0;
}

/* This function will start the continous conversion on the DR register */
uint32_t adc_startContinuousConversion(void){

    // Fail if no regular channels configured
    if(adc_channel_length == 0) return 1;

    // Enable continuous conversion mode (CONT bit)
    *ADC_arr[2] |= (1U << 1);

    // Clear EOC flag
    *ADC_arr[0] &= ~(1U << 1);

    // Start conversion
    *ADC_arr[2] |= (1U << 30);

    return 0;
}

/* This function will start conversion on the injected channels */
uint32_t adc_startInjectedConversion(void){

    // Fail if no injected channels configured
    if(adc_injected_length == 0) return 1;

    // Clear JEOC flag
    *ADC_arr[0] &= ~(1U << 2);

    // Start injected conversion
    *ADC_arr[2] |= (1U << 22);

    return 0;
}

/* This function shall read the bits on the DR register */
uint32_t adc_readData(uint16_t *data){

    // Validate pointer
    if (data == 0) return 1;

    // Verify conversion completed (EOC bit)
    if(((*ADC_arr[0]) & (1U << 1)) == 0) return 1;

    // Read converted value from DR
    *data = (uint16_t)(*ADC_arr[3]);

    return 0;
}

/* This function shall read the bits of the specified JDR register */
uint32_t adc_readInjectedChannelData(uint8_t channel, uint16_t *data){

    // Validate pointer
    if (data == 0) return 1;

    // Validate injected channel range
    if(channel < 1 || channel > 4) return 1;

    // Verify injected conversion completed (JEOC bit)
    if(((*ADC_arr[0]) & (1U << 2)) == 0) return 1;

    // Read corresponding injected data register
    switch(channel){

        case 1:
            *data = (uint16_t)(*ADC_arr[9]);
            break;

        case 2:
            *data = (uint16_t)(*ADC_arr[10]);
            break;

        case 3:
            *data = (uint16_t)(*ADC_arr[11]);
            break;

        case 4:
            *data = (uint16_t)(*ADC_arr[12]);
            break;

        default:
            return 1;
    }

    return 0;
}

