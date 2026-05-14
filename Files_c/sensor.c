/**
 * @file sensor.c
 * @brief Sensor module.
 *
 * This C file is used to define functions to help read data 
 * of sensors using the ADC driver
 *
 *
 * @author Steven McClellan
 * @date 05/13/2026
 */

/* INCLUDES */

#include "sensor.h"

// This function shall initialize a single ADC channel
 uint32_t sensor_init(uint8_t channel){

    // Initialize ADC register mapping
    adc_init();

    // Enable ADC clock
    adc_enableAdc();

    // Configure sensor ADC channel
    if(adc_setChannel(channel) !=0){
        return 1;
    } 

    return 0;
 }

 // This function shall start a single conversion on the ADC register
 uint32_t sensor_startConversion(void){
    return adc_startSingleConversion(); // Returns the start single conversion function
 }

 // This function shall return the data read on the ADC channel
 uint32_t sensor_readValue(uint16_t *value){

    return adc_readData(value); // Returns the function of read data
 }