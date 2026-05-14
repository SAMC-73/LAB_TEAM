/**
 * @file sensor.h
 * @brief Sensor module.
 *
 * This header file is used to declare functions to help read data 
 * of sensors using the ADC driver
 *
 *
 * @author Steven McClellan
 * @date 05/13/2026
 */

/* INCLUDES */

#include "SRS_ADC_DRIVER.h"

// This function shall initialize a single ADC channel
 uint32_t sensor_init(uint8_t channel);

  // This function shall start a single conversion on the ADC register
 uint32_t sensor_startConversion(void);

 // This function shall return the data read on the ADC channel
 uint32_t sensor_readValue(uint16_t *value);