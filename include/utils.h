#pragma once

#include <stdlib.h>

#define ATTR_UNUSED __attribute__((unused))
#define EXPR_UNUSED(expr) do { (void)expr; } while(0)

#define SIZEOF(arr) sizeof(arr) / sizeof(*arr)

static const int BYTE = __CHAR_BIT__;

#define BEGIN    do
#define GOTO_END break
#define END      while(0)

