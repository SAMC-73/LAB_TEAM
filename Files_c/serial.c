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
* @file serial.c
* @brief High-level Serial communication module implementation.
*
* Implements serial_init() and serial_printf() using the UART driver
* and the Utils module. Formats numeric and string arguments into a
* local buffer before transmitting via uart_send_string().
*
* @author Carlos Villarreal
* @date May 14, 2026
*
*/

/*** Includes ***/
#include "serial.h"
#include "uart_driver.h"
#include "utils.h"
#include <stdarg.h>

/*** Preprocessor Definitions ***/
#define SERIAL_BUFFER_SIZE  128U    /* Maximum formatted string length */

/*** Type Prototypes ***/

/*** Local Variables ***/

/*** External Variables ***/

/*** Function Prototypes ***/

/*** Function Definitions ***/

void serial_init(uint32_t baud_rate)
{
    uart_init(baud_rate);
}

void serial_printf(const char *fmt, ...)
{
    char    buffer[SERIAL_BUFFER_SIZE];
    buffer[0] = '\0';   /* No memset: compatible con -nostdlib */
    char   *dst = buffer;
    uint8_t tmp[32];
    va_list args;

    va_start(args, fmt);

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            switch (*fmt)
            {
                case 'd':
                {
                    /* Signed decimal integer */
                    int32_t val  = va_arg(args, int32_t);
                    uint32_t len = utils_itoa(val, tmp, 1U, 10U);
                    for (uint32_t i = 0U; i < len; i++) { *dst++ = (char)tmp[i]; }
                    break;
                }
                case 'u':
                {
                    /* Unsigned decimal integer */
                    uint32_t val = va_arg(args, uint32_t);
                    uint32_t len = utils_itoa((int32_t)val, tmp, 0U, 10U);
                    for (uint32_t i = 0U; i < len; i++) { *dst++ = (char)tmp[i]; }
                    break;
                }
                case 'x':
                {
                    /* Unsigned hexadecimal integer */
                    uint32_t val = va_arg(args, uint32_t);
                    uint32_t len = utils_itoa((int32_t)val, tmp, 0U, 16U);
                    for (uint32_t i = 0U; i < len; i++) { *dst++ = (char)tmp[i]; }
                    break;
                }
                case 's':
                {
                    /* Null-terminated string */
                    char *s = va_arg(args, char *);
                    while (*s) { *dst++ = *s++; }
                    break;
                }
                case 'c':
                {
                    /* Single character */
                    *dst++ = (char)va_arg(args, int);
                    break;
                }
                case '%':
                {
                    /* Literal percent sign */
                    *dst++ = '%';
                    break;
                }
                default:
                {
                    *dst++ = '%';
                    *dst++ = *fmt;
                    break;
                }
            }
        }
        else
        {
            *dst++ = *fmt;
        }

        fmt++;
    }

    *dst = '\0';
    va_end(args);

    uart_send_string(buffer);
}
