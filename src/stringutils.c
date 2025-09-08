#include "stringutils.h"

#include <memory.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>

#include "assertutils.h"
#include "logutils.h"
#include "utils.h"

/// @brief converts char to digit if possible
/// @param c char to convert
/// @return digit on success, -1 on failure
int _ascii_to_digit(char c);

/// @brief converts char to sign if possible
/// @param c char to convert
/// @return 1 if c = '+', -1 if '-', 0 otherwise
int _ascii_to_sign(char c);

void* _ptr_const_cast(const void* ptr);

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

    *dest_char = '\0';

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

    for( ; n < cnt; ++n)
        dest[n] = '\0';

    return dest;
}

char *utils_strcat(char *dest, const char *src)
{
    utils_assert(src != NULL);
    utils_assert(dest != NULL);

    char* dest_char = dest + utils_strlen(dest);

    const char* src_char = src;
    for( ; *src_char != '\0'; ++src_char)
        *(dest_char++) = *src_char;

    *dest_char = '\0';

    return dest;
}

char *utils_strncat(char *dest, const char *src, size_t cnt)
{
    utils_assert(src != NULL);
    utils_assert(dest != NULL);

    char* dest_end = dest + utils_strlen(dest);

    size_t n = 0;
    for( ; n < cnt; ++n) {
        dest_end[n] = src[n];

        if(src[n] == '\0') 
            break;
    }

    dest_end[n] = '\0';

    return dest;
}

char *utils_strchr(const char *str, int ch)
{
    utils_assert(str != NULL);

    const char* str_char = str;
    for( ; *str_char != '\0'; ++str_char)
        if((int)(*str_char) == ch)
            return (char*)_ptr_const_cast(str_char);

    if(ch == '\0')
        return (char*)_ptr_const_cast(str_char);

    return NULL;
}

char *utils_strdup(const char *src)
{
    utils_assert(src != NULL);

    size_t src_len = utils_strlen(src);

    char* src_copy = (char*)calloc(1, src_len + sizeof('\0'));
    if(src_copy == NULL) {
        utils_log(LOG_LEVEL_ERR, "failed to allocate string buffer");
        return NULL;
    }

    memcpy(src_copy, src, src_len + sizeof('\0'));

    return src_copy;
}

char *utils_strstr(const char *str, const char *substr)
{
    utils_assert(str != NULL);
    utils_assert(substr != NULL);

    size_t substr_len = utils_strlen(substr);
    size_t str_len = utils_strlen(str);

    if(substr_len == 0)
        return (char*)_ptr_const_cast(str);

    for(size_t i = 0; i < str_len; ++i) {
        if(str_len - i < substr_len)
            break;

        if(strncmp((str + i), substr, substr_len) == 0)
            return (char*)_ptr_const_cast(str + i);
    }
    
    return NULL;
}

int utils_atoi(const char *str)
{
    utils_assert(str != NULL);

    // Skipping whitespaces
    const char* str_char = str; 
    for( ; isspace(*str_char); ++str_char);

    int sign = _ascii_to_sign(*str_char);
    if(sign != 0) ++str_char;

    int str_int = 0;
    while(*str_char != '\0') {
        int digit = _ascii_to_digit(*str_char);
        if(digit == -1)
            return 0;

        str_int = 10 * str_int + (sign != 0 ? sign : 1) * digit; 

        ++str_char;
    }

    return str_int;
}

void utils_print_ascii_str(char *str)
{
    char* str_char = str;
    while(*str_char != '\0') {
        printf("%d ", (int)*str_char);
        ++str_char;
    } 
    printf("%d\n", (int)'\0');
}


int _ascii_to_digit(char c)
{
    int digit = (int)c - (int)'0';

    if(digit < 0 || digit > 9)
        return -1;
    else 
        return digit;
}

int _ascii_to_sign(char c)
{
    if(c == '+')
        return 1;
    else if(c == '-')
        return -1;
    else
        return 0;
}

void* _ptr_const_cast(const void* ptr)
{
    // ptr can be NULL
    void* dest_ptr = NULL;
    memcpy(&dest_ptr, &ptr, sizeof(void*));
    return dest_ptr;
}