#include "assertutils.h"

#include <stdlib.h>
#include <execinfo.h>
#include <dlfcn.h>

#include "colorutils.h"

static const int MAX_STACKTRACE_SIZE = 256;

static void utils_print_stacktrace_(void);

void utils_print_stacktrace_(void)
{
    void** backtrace_buffer = (void**)calloc(MAX_STACKTRACE_SIZE, sizeof(void*));

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
    free(backtrace_buffer);
}

void utils_assert_fail(const char *expression, const char *filename, int linenumber)
{
    utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_WHITE, "%s:%d: assertion failed\n", filename, linenumber);
    utils_colored_fprintf(stderr, ANSI_COLOR_BOLD_RED, "   assert(%s)\n", expression);
    utils_print_stacktrace_();
    abort();
}
