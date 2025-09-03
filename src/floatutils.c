#include "floatutils.h"

#include <math.h>

static const uint16_t NAN_INF_EXPONENT_DOUBLE_PRECISION = 0x07ff;

int utils_isnan(double x)
{
    uint16_t exponent = utils_get_double_exponent(x);
    uint64_t fraction = utils_get_double_fraction(x);
    if((exponent == NAN_INF_EXPONENT_DOUBLE_PRECISION) && (fraction != (uint64_t)(0)))
        return 1;
    return 0;
}

int utils_isinf(double x)
{
    uint16_t exponent = utils_get_double_exponent(x);
    uint64_t fraction = utils_get_double_fraction(x);
    if((exponent == NAN_INF_EXPONENT_DOUBLE_PRECISION) && (fraction == (uint64_t)(0)))
        return 1;
    return 0;
}

int utils_isfinite(double x)
{
    return !utils_isinf(x) && !utils_isnan(x);
}

int utils_equal_with_precision(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

int utils_equal_zero(double a)
{
    return utils_equal_with_precision(a, ZERO);
}

int utils_gt_zero(double a)
{
    return (!utils_equal_zero(a)) && (a > ZERO);
}

int utils_lt_zero(double a)
{
    return (!utils_equal_zero(a)) && (a < ZERO);
}