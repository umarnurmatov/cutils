#pragma once
#include <stdlib.h>
#include <stdint.h>

typedef uint64_t utils_hash_t;

utils_hash_t utils_djb2_hash(const void* data, size_t size_bytes);
