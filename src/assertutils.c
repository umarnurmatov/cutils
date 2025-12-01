#include "assertutils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <execinfo.h>
#include <dlfcn.h>
#include <cxxabi.h>

#include "colorutils.h"

static const int MAX_STACKTRACE_SIZE = 256;

static char* utils_demangle_backtrace_string_cxx_(char* str);
static const char* utils_demangle_backtrace_string_c_(char* str);
static void utils_print_stacktrace_(void);

static char* utils_demangle_backtrace_string_cxx_(char* str)
{
    char* symbol_begin = strchr(str, '(') + 1;
    char* symbol_end = strchr(str, '+');

    int status = 0;

    *symbol_end = '\0';
    char* realname = __cxxabiv1::__cxa_demangle(symbol_begin, NULL, NULL, &status);
    *symbol_end = '+';
    
    fprintf(stderr, "%d\n", status);

    if(status != 0)
        return NULL;

    return realname;
}

#define BUF_SIZE 100
static const char* utils_demangle_backtrace_string_c_(void* buffer, char* str)
{
    Dl_info info;

    return str;
}

static void utils_print_stacktrace_(void)
{
    // void** backtrace_buffer = (void**)calloc(MAX_STACKTRACE_SIZE, sizeof(void*));
    void* backtrace_buffer[MAX_STACKTRACE_SIZE] = {};

    int backtrace_size = backtrace(backtrace_buffer, MAX_STACKTRACE_SIZE);
    char** backtrace_strings = backtrace_symbols(backtrace_buffer, backtrace_size);
    if (backtrace_strings != NULL)
    {
        for(int i = 0; i < backtrace_size; ++i) {
            Dl_info info;
            dladdr(backtrace_buffer[i], &info);
            utils_colored_fprintf(stderr, ANSI_COLOR_YELLOW, "%s\n", info.dli_sname ? info.dli_sname : backtrace_strings[i]);
        }
    }

    free(backtrace_strings);
    // free(backtrace_buffer);
}

void utils_assert_fail(const char *expression, const char *filename, int linenumber)
{
    utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_WHITE, "%s:%d: assertion failed\n", filename, linenumber);
    utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_RED, "   assert(%s)\n", expression);
    utils_print_stacktrace_();
    abort();
}
