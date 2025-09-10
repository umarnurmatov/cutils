#include "arrayutils.h"

#include <stdio.h>
#include <memory.h>

#include "logutils.h"
#include "assertutils.h"

static arr_data_t* _utils_triangle_array_get_ptr(triangle_array_t* arr, size_t iy, size_t ix);

size_t utils_triangle_array_get_size(triangle_array_t* arr)
{
    return arr->height * (arr->height + 1ul) / 2ul;
}

enum array_err_t utils_triangle_array_init(triangle_array_t* arr, size_t height)
{
    arr->height = height;
    size_t arr_size = utils_triangle_array_get_size(arr);

    arr->ptr = (arr_data_t*)calloc(arr_size, sizeof(arr_data_t));
    if(arr->ptr == NULL) {
        utils_log(LOG_LEVEL_ERR, "failed to allocate array");
        return ARRAY_ERR_ALLOCATION_FAILED;
    }

    return ARRAY_ERR_NONE;
}

enum array_err_t utils_trianlge_array_set(triangle_array_t* arr, arr_data_t elem, size_t iy, size_t ix)
{
    utils_assert(arr != NULL);
    utils_assert(arr->ptr != NULL);

    arr_data_t* ptr = _utils_triangle_array_get_ptr(arr, iy, ix);
    if(ptr == NULL)
        return ARRAY_ERR_OUT_OF_RANGE;

    *ptr = elem;

    return ARRAY_ERR_NONE;
}

enum array_err_t utils_trianlge_array_get(triangle_array_t* arr, arr_data_t* elem, size_t iy, size_t ix)
{
    utils_assert(arr != NULL);
    utils_assert(arr->ptr != NULL);

    arr_data_t* ptr = _utils_triangle_array_get_ptr(arr, iy, ix);
    if(ptr == NULL)
        return ARRAY_ERR_OUT_OF_RANGE;

    *elem = *ptr;

    return ARRAY_ERR_NONE;
}

void utils_triangle_array_free(triangle_array_t* arr)
{
    free(arr->ptr);
    arr->ptr = NULL;
}

static arr_data_t* _utils_triangle_array_get_ptr(triangle_array_t* arr, size_t iy, size_t ix)
{
    utils_assert(arr != NULL);
    utils_assert(arr->ptr != NULL);

    if(ix > iy) {
        utils_log(LOG_LEVEL_ERR, "index out of range");
        return NULL;
    }

    size_t size = utils_triangle_array_get_size(arr);
    size_t offset = ix + iy * (iy + 1ul) / 2ul;

    if(offset >= size) {
        utils_log(LOG_LEVEL_ERR, "index out of range");
        return NULL;
    }

    return (arr_data_t*)((size_t)arr->ptr + offset * sizeof(arr_data_t));
}

void utils_triangle_array_print(triangle_array_t* arr)
{
    utils_assert(arr != NULL);
    utils_assert(arr->ptr != NULL);
    
    for(size_t iy = 0; iy < arr->height; ++iy) {
        for(size_t ix = 0; ix <= iy; ++ix) 
            printf("%d\t", *_utils_triangle_array_get_ptr(arr, iy, ix));

        putc('\n', stdout);
    }
}