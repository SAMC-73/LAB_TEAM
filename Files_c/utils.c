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
 * @file utils.c
 * @brief Utility library with helper functions.
 *
 * Utils module has helper functions to treat strings, ASCII conversions, and
 * printing utilities.
 *
 * @author Daniel Lopez, Mauricio Vela, Carlos Cayetano.
 * @date 05/06/2026
 *
 */

/*** Includes ***/
#include "utils.h"

/*** Preprocessor Definitions ***/

/*** Type Prototypes ***/

/*** Local Variables ***/

/*** External Variables ***/

/*** Function Prototypes ***/

static uint32_t utils_printString(char *dst, char *src);
static uint32_t utils_printInt(char *dst, int32_t num, uint8_t sign, uint32_t base);

/*** Function Definitions ***/

void utils_snprintf(char *dst, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
                case 's':
                    dst += utils_printString(dst, va_arg(args, char *));
                    break;
                case 'd':
                    dst += utils_printInt(dst, va_arg(args, int32_t), 1, 10);
                    break;
                case 'u':
                    dst += utils_printInt(dst, (int32_t)va_arg(args, uint32_t), 0, 10);
                    break;
                case 'x':
                    dst += utils_printInt(dst, (int32_t)va_arg(args, uint32_t), 0, 16);
                    break;
                case 'c':
                    *dst++ = (char)va_arg(args, int);
                    break;
                case '%':
                    *dst++ = '%';
                    break;
                default:
                    *dst++ = '%';
                    *dst++ = *format;
                    break;
            }
        }
        else
        {
            *dst++ = *format;
        }

        format++;
    }

    *dst = '\0';
    va_end(args);
}


/**
 * @brief Copy a string into a destination buffer.
 */
static uint32_t utils_printString(char *dst, char *src)
{
    uint32_t len = 0;

    while (*src)
    {
        *dst++ = *src++;
        len++;
    }

    return len;
}

/**
 * @brief Convert an integer to ASCII and copy it into a destination buffer.
 */
static uint32_t utils_printInt(char *dst, int32_t num, uint8_t sign, uint32_t base)
{
    uint8_t tmp[32];
    uint32_t len = utils_itoa(num, tmp, sign, (uint8_t)base);

    for (uint32_t i = 0; i < len; i++)
    {
        dst[i] = (char)tmp[i];
    }

    return len;
}

/**
 * @brief Convert data from integer type into an ASCII string
 */
uint32_t utils_itoa(int32_t data, uint8_t *ptr, uint8_t sign, uint8_t base)
{
    uint32_t len = 0;
    uint32_t udata;
    uint8_t negative = 0;
    const char digits[] = "0123456789abcdef";

    if (sign && (data < 0))
    {
        negative = 1;
        udata = (uint32_t)(-data);
    }
    else
    {
        udata = (uint32_t)data;
    }

    if (udata == 0)
    {
        ptr[len++] = '0';
        ptr[len] = '\0';
        return len;
    }

    while (udata > 0)
    {
        ptr[len++] = (uint8_t)digits[udata % base];
        udata /= base;
    }

    if (negative)
    {
        ptr[len++] = '-';
    }

    ptr[len] = '\0';
    utils_memReverse(ptr, len);

    return len;
}

/**
 * @brief Convert data from an ASCII string into an integer type
 */
int32_t utils_atoi(uint8_t *ptr, uint32_t digits, uint8_t sign, uint8_t base)
{
    int32_t result = 0;
    uint8_t negative = 0;
    uint32_t i = 0;

    if (sign && (ptr[0] == '-'))
    {
        negative = 1;
        i = 1;
    }

    for (; i < digits; i++)
    {
        uint8_t c = ptr[i];
        uint8_t digit;

        if (c >= '0' && c <= '9')
            digit = c - '0';
        else if (c >= 'a' && c <= 'f')
            digit = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            digit = c - 'A' + 10;
        else
            break;

        result = result * (int32_t)base + (int32_t)digit;
    }

    if (negative)
        result = -result;

    return result;
}

/**
 * @brief Copy a block of memory from source to destination.
 */
void * utils_memCpy(void *dst, void *src, size_t length)
{
    uint8_t *d = (uint8_t *)dst;
    uint8_t *s = (uint8_t *)src;

    for (size_t i = 0; i < length; i++)
        d[i] = s[i];

    return dst;
}

/**
 * @brief Reverse the order of elements of a data set
 */
void * utils_memReverse(void *src, size_t length)
{
    uint8_t *data = (uint8_t *)src;
    size_t left = 0;
    size_t right = length - 1;
    uint8_t tmp;

    while (left < right)
    {
        tmp         = data[left];
        data[left]  = data[right];
        data[right] = tmp;
        left++;
        right--;
    }

    return src;
}
