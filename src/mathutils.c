#include "mathutils.h"

int utils_imax(int a, int b)
{
    return a > b ? a : b;
}

int utils_imin(int a, int b)
{
    return a < b ? a : b;
}

uint64_t utils_i64_factorial(uint64_t x)
{
    uint64_t ans = 1;
    for(uint64_t i = 2; i <= x; ++i)
        ans *= i; 

    return ans;
    }
