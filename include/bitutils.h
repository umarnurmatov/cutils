#pragma once

#include <stdint.h>

/// @brief converts double to integer bit-by-bit
/// @param x variable to convert
/// @return bit-by-bit converted x
uint64_t utils_double_to_integer(double x);

/// @brief extracts exponent from double-precision floating-point variable
/// @param x double-precision floating-point variable
/// @return exponent of x 
uint16_t utils_get_double_exponent(double x);

/// @brief extracts fraction from double-precision floating-point variable
/// @param x double-precision floating-point variable
/// @return fraction of x 
uint64_t utils_get_double_fraction(double x);