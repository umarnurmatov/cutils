#pragma once

#include <threads.h>

/// @brief mtx_init wrapper
/// @param mtx pointer to mutex
/// @param type type of mutex
int utils_mtx_init(mtx_t* mtx, int type);

/// @brief mtx_destroy wrapper
/// @param mtx pointer to mutex
void utils_mtx_destroy(mtx_t* mtx);

/// @brief mtx_lock wrapper
/// @param mtx pointer to mutex
int utils_mtx_lock(mtx_t* mtx);

/// @brief mtx_unlock wrapper
/// @param mtx pointer to mutex
int utils_mtx_unlock(mtx_t* mtx);

