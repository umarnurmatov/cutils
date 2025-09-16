#pragma once

#include <stdlib.h>

/// @brief string legth
/// @param str null-terminated string
size_t utils_strlen(const char* str);

/// @brief copy \p src string to \p dest
/// @param dest destination buffer, must be large enougth,
///        that is \ref utils_strlen(\p src) + 1
/// @param src string to copy from
/// @return dest
char* utils_strcpy(char* dest, const char* src);

/// @brief copy at most cnt charachters from \p src 
///        string to \p dest; fill remaning space
///        with null-terminator charachters
/// @param dest destination buffer, must be at least
///        size \p cnt
/// @param src string to copy from
/// @return dest
char* utils_strncpy(char* dest, const char* src, size_t cnt);

/// @brief concatenate strings \p dest and \p src and write
///        result to \p dest
/// @param dest destination string; must be large enougth,
///        that is \ref utils_strlen(\p dest)
///        + \ref utils_strlen(\p src) + 1
/// @param src string to concatenate with
/// @return \p dest
char *utils_strcat(char* dest, const char* src);

/// @brief concatenate \p dest and no more than
///        \p cnt characters from \p src; write
///        result to dest; fill remaning space with
///        null-terminator charachter
/// @param dest destination string; must be at least
///        size \ref utils_strlen(\p dest) + \p cnt
/// @param src string to concatenate with
/// @return \p dest
char* utils_strncat(char* dest, const char* src, size_t cnt);

/// @brief    locate charachter
/// @details  locates for charachter \p ch in string \p str with O(n)
///           time complexity
/// @param    str string to observe
/// @param    ch charachter to find
/// @return   pointer to character in \p str if \p ch is found,
///           NULL otherwise
char* utils_strchr(const char* str, int ch);

/// @brief    duplicate a string
/// @details  allocates buffer using \ref calloc() to that
///           \p src string will be copied
/// @param    src string to copy
/// @return   pointer to allocated buffer on success,
///           NULL otherwise
char* utils_strdup(const char* src);

/// @brief    locate subtring
/// @details  locate substring \p str in string \p str
///           with O(n) time complextity
/// @param    str string to observe
/// @param    substr substring to locate
/// @return   pointer to first substring charachter in \p str 
///           if \p substr is found, NULL otherwise
char* utils_strstr(const char* str, const char* substr);

/// @bried   convert a string to integer
/// @details converts string \p str to signed integer,
///          skipping all whitespaces in the beginning
///          of \p str
/// @param   str string to convert
/// @return  converted integer on success, 0 on failure
int utils_atoi(const char* str);

/// @internal
void utils_print_ascii_str(char* str);
