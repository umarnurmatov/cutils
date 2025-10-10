#include "logutils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <threads.h>
#include <string.h>
#include <linux/limits.h>

#include "colorutils.h"
#include "ioutils.h"
#include "assertutils.h"
#include "threadutils.h"

static const int MAX_TIME_STR_LEN = 70;

struct _log_data_t
{
    FILE* stream;
    mtx_t stream_mtx;
    enum log_level_t level_glob;
};

static struct _log_data_t _log_data = {
    .stream = NULL,
    .level_glob = LOG_LEVEL_DEBUG
};

enum log_err_t utils_init_log_file(const char* filename, const char* relpath)
{
    utils_assert(filename != NULL);
    utils_assert(relpath != NULL);

    char* cwd_path = get_current_working_dir();

    size_t cwd_path_len = strlen(cwd_path);
    size_t relpath_len = strlen(relpath);
    size_t filename_len = strlen(filename);

    char* full_path = 
        (char*)calloc(
            1, 
            cwd_path_len + relpath_len + (size_t)3
        );
    sprintf(full_path, "%s/%s", cwd_path, relpath);

    create_dir(full_path);
    
    char* full_filepath = 
        (char*)calloc(
            1, 
            cwd_path_len + relpath_len + filename_len + (size_t)3
        );
    sprintf(full_filepath, "%s/%s", full_path, filename);
    _log_data.stream = open_file(full_filepath, "a");

    free(cwd_path);
    free(full_path);
    free(full_filepath);

    if(_log_data.stream == NULL) 
        _log_data.stream = stderr;

    setvbuf(_log_data.stream, NULL, _IONBF, 0);

    if(utils_mtx_init(&_log_data.stream_mtx, mtx_plain) != thrd_success)
        return LOG_INIT_MTX_INIT_ERR;

    return LOG_INIT_SUCCESS;
}

enum log_err_t utils_init_log_stream(FILE* stream)
{
    _log_data.stream = stream;

    if(utils_mtx_init(&_log_data.stream_mtx, mtx_plain) != thrd_success)
        return LOG_INIT_MTX_INIT_ERR;

    return LOG_INIT_SUCCESS;
}

void utils_end_log(void)
{
    utils_assert(_log_data.stream != NULL);

    int is_console = isatty(fileno(_log_data.stream));
    if(!is_console) fclose(_log_data.stream);

    utils_mtx_destroy(&_log_data.stream_mtx);
}

void utils_set_global_log_level(enum log_level_t _log_level_glob)
{
    _log_data.level_glob = _log_level_glob;
}

const char* utils_get_log_level_str(enum log_level_t log_level)
{
    switch(log_level) {
        case LOG_LEVEL_ERR:
            return "ERROR";
            break;
        case LOG_LEVEL_WARN:
            return "WARN";
            break;
        case LOG_LEVEL_INFO:
            return "INFO";
            break;
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
            break;
        default:
            return "";
            break;
    }
}


void utils_log(enum log_level_t log_level, const char* fmtstring, ...)
{
    if(log_level > _log_data.level_glob)
        return;

    utils_assert(_log_data.stream != NULL);

    utils_mtx_lock(&_log_data.stream_mtx);

    thrd_t cur_thread = thrd_current();

    const char* log_level_str = utils_get_log_level_str(log_level);
    time_t cur_time = time(NULL);
    struct tm* iso_time = localtime(&cur_time);
    char time_buff[MAX_TIME_STR_LEN];
    strftime(time_buff, sizeof(time_buff), "%F %T", iso_time);
    fprintf(
        _log_data.stream, 
        "[%s] [%s] [TID %lu] ", 
        log_level_str, 
        time_buff, 
        cur_thread
    );

    va_list va_arg_list;
    va_start(va_arg_list, fmtstring);
    vfprintf(_log_data.stream, fmtstring, va_arg_list);
    va_end(va_arg_list);

    fputc('\n', _log_data.stream);

    utils_mtx_unlock(&_log_data.stream_mtx);
}

void utils_logc(enum log_level_t log_level, tty_mode_t mode, const char* category, const char* fmtstring, ...)
{
    if(log_level > _log_data.level_glob)
        return;

    utils_assert(_log_data.stream != NULL);

    utils_mtx_lock(&_log_data.stream_mtx);

    thrd_t cur_thread = thrd_current();

    const char* log_level_str = utils_get_log_level_str(log_level);
    time_t cur_time = time(NULL);
    struct tm* iso_time = localtime(&cur_time);
    char time_buff[MAX_TIME_STR_LEN];
    strftime(time_buff, sizeof(time_buff), "%F %T", iso_time);
    utils_colored_fprintf(
        _log_data.stream, 
        mode,
        "[%s] [%s] [%s] [TID %lu] ", 
        log_level_str, 
        time_buff, 
        category,
        cur_thread
    );

    va_list va_arg_list;
    va_start(va_arg_list, fmtstring);
    utils_colored_vfprintf(_log_data.stream, ANSI_COLOR_BOLD_WHITE, fmtstring, va_arg_list);
    va_end(va_arg_list);

    fputc('\n', _log_data.stream);

    utils_mtx_unlock(&_log_data.stream_mtx);
}


void utils_llogc(enum log_level_t log_level, tty_mode_t mode, const char* category, const char* file, int line, const char* func, const char* fmtstring, ...)
{
    if(log_level > _log_data.level_glob)
        return;

    utils_assert(_log_data.stream != NULL);

    utils_mtx_lock(&_log_data.stream_mtx);
    const char* log_level_str = utils_get_log_level_str(log_level);

    utils_colored_fprintf(
        _log_data.stream, 
        mode,
        "[%s] [%s] [from %s:%d %s()] ", 
        log_level_str,
        category,
        file,
        line,
        func
    );

    va_list va_arg_list;
    va_start(va_arg_list, fmtstring);
    utils_colored_vfprintf(_log_data.stream, ANSI_COLOR_BOLD_WHITE, fmtstring, va_arg_list);
    va_end(va_arg_list);

    fputc('\n', _log_data.stream);

    utils_mtx_unlock(&_log_data.stream_mtx);
}
