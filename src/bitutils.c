#include "bitutils.h"

#include <stdlib.h>
#include <string.h>

static const int LEN_DOUBLE_PRECISION          = 64;
static const int LEN_FRACTION_DOUBLE_PRECISION = 52;
static const int LEN_EXPONENT_DOUBLE_PRECISION = 11;

uint64_t utils_double_to_integer(double x)
{
    uint64_t x_buffer = 0;
    memcpy(&x_buffer, &x, sizeof(uint64_t));
    return x_buffer;
}

uint16_t utils_get_double_exponent(double x)
{
    uint64_t x_integer = utils_double_to_integer(x);
    uint64_t x_mask = ~((uint64_t)(1) << (LEN_DOUBLE_PRECISION - 1));
    x_integer &= x_mask;                         // unset sign bit
    x_integer >>= LEN_FRACTION_DOUBLE_PRECISION; // aligning exponent to LSB
    uint16_t exponent_buffer = 0;
    memcpy(&exponent_buffer, &x_integer, sizeof(uint16_t));
    return exponent_buffer;
}

uint64_t utils_get_double_fraction(double x)
{
    uint64_t x_integer = utils_double_to_integer(x);
    uint64_t fraction_mask = 0;
    for(int i = 0; i < LEN_FRACTION_DOUBLE_PRECISION; ++i) 
        fraction_mask |= ((uint64_t)(1) << i);
    return x_integer & fraction_mask;
}

