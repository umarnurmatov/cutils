#pragma once

#ifndef NDEBUG
#define utils_assert(expression) !!(expression) \
                                    ? (void)(0) \
                                    : utils_assert_fail(#expression, __FILE__, __LINE__)
#else
#define utils_assert(expression) (void)(0)
#endif

/// @brief prints stack trace to stderr 
void utils_print_stacktrace(void);

/// @brief prints failed assertion info  and stack trace to stderr (see utils_assert macro)
/// @param expression string containing asserted expression
/// @param filename filename where assertion occured
/// @param linenumber number of line containing assertion in file
void __attribute__((noreturn)) utils_assert_fail(const char* expression, const char* filename, int linenumber);
