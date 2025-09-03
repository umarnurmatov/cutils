#include "assertutils.h"

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#include "colorutils.h"

static const int MAX_STACKTRACE_SIZE = 256;

void utils_print_stacktrace(void)
{
    void** backtrace_buffer = (void**)calloc(MAX_STACKTRACE_SIZE, sizeof(void*));

    int backtrace_size = backtrace(backtrace_buffer, MAX_STACKTRACE_SIZE);
    char** backtracce_strings = backtrace_symbols(backtrace_buffer, backtrace_size);
    if (backtracce_strings != NULL)
    {
        utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_WHITE, "Stack trace (%d stack frames):\n", backtrace_size);
        for(int i = 0; i < backtrace_size; ++i)
            utils_colored_fprintf(stderr, ANSI_COLOR_YELLOW, "%s\n", backtracce_strings[i]);
    }

    free(backtracce_strings);
    free(backtrace_buffer);
}

void utils_assert_fail(const char *expression, const char *filename, int linenumber)
{
    utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_WHITE, "%s:%d: assertion failed\n", filename, linenumber);
    utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_RED, "   assert(%s)\n", expression);
    utils_print_stacktrace();
    abort();
}
