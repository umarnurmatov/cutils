#include "colorutils.h"

#include <stdarg.h>
#include <unistd.h>

void utils_colored_fprintf(FILE *stream, tty_mode_t mode, const char *fmtstring, ...)
{
    utils_assert(stream != NULL);
    utils_assert(mode != NULL);
    utils_assert(fmtstring != NULL);

    int is_console = isatty(fileno(stream));

    if(is_console)
        fputs(mode, stream);

    va_list va_arg_list;
    va_start(va_arg_list, fmtstring);
    vfprintf(stream, fmtstring, va_arg_list);
    va_end(va_arg_list);

    if(is_console)
        fputs(ANSI_COLOR_RESET, stream);
}
