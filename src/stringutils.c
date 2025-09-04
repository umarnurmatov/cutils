#include "stringutils.h"

#include <memory.h>
#include <limits.h>

#include "assertutils.h"
#include "logutils.h"
#include "utils.h"

/// @brief converts char to digit if possible
/// @param c char to convert
/// @return digit on success, -1 on failure
int _ascii_to_digit(char c);

size_t utils_strlen(const char *str)
{
    utils_assert(str != NULL);

    size_t len = 0ul;

    for(const char* str_char = str; *str_char != '\0'; ++str_char) 
        ++len;

    return len;
        
}

char* utils_strcpy(char *dest, const char *src)
{
    utils_assert(src != NULL);
    utils_assert(dest != NULL);

    char* dest_char = dest;
    const char* src_char = src;
    for( ; *src_char != '\0'; ++src_char)
        *(dest_char++) = *src_char;

    *dest_char = *src_char;

    return dest;
}

char* utils_strncpy(char *dest, const char *src, size_t cnt)
{
    utils_assert(src != NULL);
    utils_assert(dest != NULL);

    size_t n = 0;
    for( ; n < cnt; ++n) {
        dest[n] = src[n];

        if(src[n] == '\0') 
            break;
    }

    dest[n] = '\0';

    return dest;
}

char *utils_strcat(char *dest, const char *src)
{
    utils_assert(src != NULL);
    utils_assert(dest != NULL);

    char* dest_char = dest;
    for( ; *dest_char != '\0'; ++dest_char);

    const char* src_char = src;
    for( ; *src_char != '\0'; ++src_char)
        *(dest_char++) = *src_char;

    *dest_char = *src_char;

    return dest;
}

char *utils_strncat(char *dest, const char *src, size_t cnt)
{
    utils_assert(src != NULL);
    utils_assert(dest != NULL);

    char* dest_end = dest;
    for( ; *dest_end != '\0'; ++dest_end);

    for(size_t n = 0; n < cnt + 1; ++n) {
        dest_end[n] = src[n];

        if(src[n] == '\0') 
            break;
    }

    return dest;
}

char *utils_strchr(const char *str, int ch)
{
    utils_assert(str != NULL);

    const char* str_char = str;
    for( ; *str_char != '\0'; ++str_char)
        if((int)(*str_char) == ch)
            return (char*)str_char;

    if(ch == '\0')
        return (char*)str_char;

    return NULL;
}

char *utils_strdup(const char *src)
{
    utils_assert(src != NULL);

    char* src_copy = (char*)calloc(1, SIZEOF(src));
    if(src_copy == NULL) {
        utils_log(LOG_LEVEL_ERR, "failed to allocate string buffer");
        return NULL;
    }

    mempcpy(src_copy, src, SIZEOF(src));

    return src_copy;
}

int utils_atoi(const char *str)
{
    utils_assert(str != NULL);

    const char* str_end = str; 
    for( ; *str_end != '\0'; ++str_end);

    if(str_end == str) 
        return 0;

    const char* str_char = str_end - 1;
    int str_int = 0;
    int exponent = 1;

    for( ; str_char != str; --str_char) {
        int digit = _ascii_to_digit(*str_char);
        if(digit == -1)
            return 0;

        str_int += digit * exponent;
        exponent *= 10;
    }

    int digit = _ascii_to_digit(*str_char);
    if(digit == -1)
        return 0;
    str_int += digit * exponent;

    return str_int;
}

int _ascii_to_digit(char c)
{
    int digit = (int)c - (int)'0';

    if(digit < 0 || digit > 9)
        return -1;
    else 
        return digit;
}
