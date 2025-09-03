#pragma once

#include <stdlib.h>

size_t utils_strlen(const char* str);

char* utils_strcpy(char* dest, const char* src);

char* utils_strncpy(char* dest, const char* src, size_t cnt);

char *utils_strcat(char* dest, const char* src);

char* utils_strncat(char* dest, const char* src, size_t cnt);

char* utils_strchr(const char* str, int ch);

char* utils_strdup(const char* src);

int utils_atoi(const char* str);