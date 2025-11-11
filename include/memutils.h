#pragma once

#include <stdlib.h>

#define NFREE(ptr) free(ptr); \
                   ptr = NULL;

#define TYPED_CALLOC(size, type) \
    (type*) calloc (size, sizeof(type))

