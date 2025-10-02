#include "sortutils.h"

#include <cstdio>
#include <memory.h>

#include "assertutils.h"

static const int _SCRATCH_BUF_SIZE_B = 32;

static void _utils_swap_on_buf(void* x, void* y, size_t tsize, char* buf);

static void _utils_swap_chunks(void* x, void* y, size_t tsize);

static void _utils_swap_bytes(void* x, void* y, size_t tsize);

static size_t _utils_quicksort_partition(void* arr, size_t lo, size_t hi, size_t tsize, utils_cmp cmp);

void utils_swap(void* x, void* y, size_t tsize)
{
    static char scratch_buf[_SCRATCH_BUF_SIZE_B];

    char* buf = tsize > _SCRATCH_BUF_SIZE_B 
                    ? (char*)malloc(tsize)
                    : scratch_buf;

    _utils_swap_on_buf(x, y, tsize, buf);

    if(buf != scratch_buf)
        free(buf);
}

void utils_bubblesort(void* arr, size_t asize, size_t tsize, utils_cmp cmp)
{
    utils_assert(arr != NULL);
    utils_assert(cmp != NULL);
    
    char* arr_c = (char*)arr;
    char* el_a = NULL;
    char* el_b = NULL;
    bool swapped = 0;

    for(size_t ia = 0; ia < asize; ++ia) {
        swapped = 0;
        for(size_t ib = 0; ib < asize - ia - 1ul; ++ib) {
            el_a = arr_c + tsize * ib;
            el_b = arr_c + tsize * (ib + 1ul);
            if(cmp(el_a, el_b) > 0) {
                _utils_swap_chunks(el_a, el_b, tsize);
                swapped = 1;
            }
        }
        if(!swapped)
            break;
    }
}

void utils_quicksort(void* arr, size_t lo, size_t hi, size_t tsize, utils_cmp cmp)
{
    utils_assert(arr != NULL);
    utils_assert(cmp != NULL);

    if(lo >= hi) return;

    // TODO for case 2 and 3

    size_t pt = _utils_quicksort_partition(arr, lo, hi, tsize, cmp);

    utils_quicksort(arr, lo      , pt - 1ul, tsize, cmp);
    utils_quicksort(arr, pt + 1ul, hi      , tsize, cmp);
}

void _utils_swap_on_buf(void* x, void* y, size_t tsize, char* buf)
{
    utils_assert(x   != NULL);
    utils_assert(y   != NULL);
    utils_assert(buf != NULL);

    memcpy(buf, x  , tsize);
    memcpy(x  , y  , tsize);
    memcpy(y  , buf, tsize);
}

static void _utils_swap_chunks(void* x, void* y, size_t tsize)
{
    utils_assert(x != NULL);
    utils_assert(y != NULL);

    int64_t chunk = 0ul;
    size_t chunk_cnt = tsize / sizeof(chunk);

    int64_t* x_ptr = (int64_t*)x;
    int64_t* y_ptr = (int64_t*)y;
    for(size_t i = 0; i < chunk_cnt; ++i) {
        chunk  = *x_ptr;
        *x_ptr = *y_ptr;
        *y_ptr = chunk;

        ++x_ptr;
        ++y_ptr;
    }

    size_t remain_byte_cnt = tsize % sizeof(chunk);
    _utils_swap_bytes((char*)x_ptr, (char*)y_ptr, remain_byte_cnt);
}

static void _utils_swap_bytes(void* x, void* y, size_t tsize)
{
    // TODO asserts
    char* x_byte_ptr = (char*)x;
    char* y_byte_ptr = (char*)y;
    char byte = 0;

    for(size_t i = 0; i < tsize; ++i)
    {
        byte        = *x_byte_ptr;
        *x_byte_ptr = *y_byte_ptr;
        *y_byte_ptr = byte;

        ++x_byte_ptr;
        ++y_byte_ptr;
    }
}

static size_t _utils_quicksort_partition(void* arr, size_t lo, size_t hi, size_t tsize, utils_cmp cmp)
{
    // TODO asserts
    char* arr_c = (char*)arr;
    
    size_t pivot_ind      = hi;
    size_t pivot_temp_ind = lo;

    for(size_t arr_ind = lo; arr_ind < hi; ++arr_ind) {
        if(cmp(arr_c + arr_ind * tsize, arr_c + pivot_ind * tsize) <= 0) {
            _utils_swap_chunks(arr_c + arr_ind * tsize, arr_c + pivot_temp_ind * tsize, tsize);
            ++pivot_temp_ind;
        }
    }

    _utils_swap_chunks(arr_c + pivot_temp_ind * tsize, arr_c + pivot_ind * tsize, tsize);
    return pivot_temp_ind;
}
