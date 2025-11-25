#pragma once

#ifdef _DEBUG
#define utils_assert(expression) !!(expression) \
                                    ? (void)(0) \
                                    : utils_assert_fail(#expression, __FILE__, __LINE__)

#define asserted || utils_assert_fail(#expr, __FILE__, __LINE__)
#else
#define utils_assert(expression) (void)(0)
#define asserted 
#endif

#define verified(expr) || ({ expr; false; })

/// @brief prints failed assertion info  and stack trace to stderr (see utils_assert macro)
/// @param expression string containing asserted expression
/// @param filename filename where assertion occured
/// @param linenumber number of line containing assertion in file
void __attribute__((noreturn)) utils_assert_fail(const char* expression, const char* filename, int linenumber);
