#include "threadutils.h"

#include "utils.h"

int utils_mtx_init(mtx_t *mtx, int type)
{
    #if defined (SINGLE_THREAD)
        EXPR_UNUSED(mtx);
        EXPR_UNUSED(type);
        return 0;
    #else
        return mtx_init(mtx, type);
    #endif
}

void utils_mtx_destroy(mtx_t *mtx)
{
    #if defined SINGLE_THREAD
        EXPR_UNUSED(mtx);
    #else
        mtx_destroy(mtx);
    #endif
}

int utils_mtx_lock(mtx_t *mtx)
{
    #if defined SINGLE_THREAD
        EXPR_UNUSED(mtx);
        return 0;
    #else
        return mtx_lock(mtx);
    #endif
}

int utils_mtx_unlock(mtx_t *mtx)
{
    #if defined SINGLE_THREAD
        EXPR_UNUSED(mtx);
        return 0;
    #else
        return mtx_unlock(mtx);
    #endif
}
