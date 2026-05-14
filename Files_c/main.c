/**
 * @file main.c
 * @brief Application example:
 * Potentiometer controls LED brightness using ADC + PWM.
 *
 * Connections:
 *   Potentiometer output -> PA0 (ADC1_IN0)
 *   PWM output           -> PA6 (TIM3_CH1)
 *
 * Behavior:
 *   ADC reads analog voltage from potentiometer.
 *   ADC value (0–4095) is mapped into PWM duty cycle (0–100%).
 *   LED brightness changes in real time.
 *  @author Steven McClellan
 *  @date 05/13/2026
 */

#include "SRS_GPIO_DRIVER.h"
#include "sensor.h"
#include "pwm.h"

int main(void)
{
    uint16_t adc_value;
    uint8_t duty_cycle;

    /* GPIO CONFIGURATION */

    gpio_init();

    /* Enable GPIOA clock */
    gpio_initPort(A);

    /*
     * PA0 -> ADC1_IN0
     * Configure as analog mode
     * MODER = 11
     */
    gpio_setPinMode(A, 0, 3);

    /* ADC CONFIGURATION */

    adc_init();

    /* Enable ADC peripheral */
    adc_enableAdc();

    /*
     * Configure regular ADC channel 0
     * (PA0 = ADC1_IN0)
     */
    sensor_init(0);

    /* PWM CONFIGURATION */

    /* PWM is set at 1 kHz*/
    pwm_init(1000);

    /* Start PWM generation */
    pwm_start();

    /* MAIN LOOP */

    while (1)
    {
        /* Start ADC conversion */
        sensor_startConversion();

         while((ADC1->SR & (1U << 1)) == 0);

        /* Read ADC result (0–4095) */
        sensor_readValue(&adc_value);

        /*
         * Map ADC value into duty cycle percentage
         *
         * 0      -> 0%
         * 4095   -> 100%
         */
        duty_cycle = (adc_value * 100U) / 4095U;

        /* Update PWM signal */
        pwm_setSignal(duty_cycle);

        for(volatile uint32_t i = 0; i < 5000; i++);
    }
}