#pragma once

#include <stdlib.h>

/// @brief   free and null
/// @details free memory pointed by \p ptr and assigng NULL
/// @param   ptr pointer to free
inline void nfree(void* ptr)
{
    free(ptr);
    ptr = nullptr;
}
