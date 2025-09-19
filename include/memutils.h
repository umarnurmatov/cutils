#pragma once

#include <stdlib.h>

#define NFREE(ptr) free(ptr); \
                   ptr = NULL;
