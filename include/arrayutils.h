#pragma once

#include <stdlib.h>

enum array_err_t
{
    ARRAY_ERR_NONE,
    ARRAY_ERR_ALLOCATION_FAILED,
    ARRAY_ERR_OUT_OF_RANGE
};

typedef int arr_data_t;

struct triangle_array_t
{
    arr_data_t* ptr;
    size_t height;
};

typedef struct triangle_array_t triangle_array_t;

size_t utils_triangle_array_get_size(triangle_array_t* arr);

enum array_err_t utils_triangle_array_init(triangle_array_t* arr, size_t height);

enum array_err_t utils_trianlge_array_set(triangle_array_t* arr, arr_data_t elem, size_t iy, size_t ix);

enum array_err_t utils_trianlge_array_get(triangle_array_t* arr, arr_data_t* elem, size_t iy, size_t ix);

void utils_triangle_array_free(triangle_array_t* arr);

void utils_triangle_array_print(triangle_array_t* arr);
