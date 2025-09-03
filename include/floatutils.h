#pragma once

#include "bitutils.h"

static const double EPSILON = 1e-10;
static const double ZERO = 0.0;

/// @brief checks if double-precision floating-point variable is NaN
/// @param x variable to check
/// @return 1 if x is None, 0 otherwise
int utils_isnan(double x);

/// @brief checks if double-precision floating-point variable is +/- infinity
/// @param x variable to check
/// @return 1 if x is +/- infinity, 0 otherwise
int utils_isinf(double x);

/// @brief checks if double-precision floating-point variable is finite
/// @param x variable to check
/// @return 1 if x is finite, 0 otherwise
int utils_isfinite(double x);

/// @brief compares two floating-point variables on equality with precision
/// @param a pointer to first variable
/// @param b pointer to second variable
/// @return 1 if variables are equal, 0 otherwise
int utils_equal_with_precision(double a, double b);

/// @brief compares value with zero
/// @param a pointer to variable
/// @return 1 if value equals zero, 0 otherwise
int utils_equal_zero(double a);

/// @brief compares value with zero
/// @param a pointer to variable
/// @return 1 if value greater than zero, 0 otherwise
int utils_gt_zero(double a);

/// @brief compares value with zero
/// @param a pointer to variable
/// @return 1 if value less than zero, 0 otherwise
int utils_lt_zero(double a);
