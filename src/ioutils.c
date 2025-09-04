#include "ioutils.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <linux/limits.h>

#include "assertutils.h"
#include "logutils.h"

void clear_stdin_buffer()
{
    int buffered_char;
    do {
        buffered_char = getchar();
    } while((buffered_char != '\n') && (buffered_char != EOF));
}

enum io_err_t input_double(double *d)
{
    int assigned = scanf(" %lf", d);
    clear_stdin_buffer();
    switch (assigned)
    {
        case -1:
            return IO_ERR_EOF_REACHED;
            break;
        case 1:
            return IO_ERR_NONE;
            break;
        default:
            return IO_ERR_ASSIGMENT_FAIL;
            break;
    }
}

enum io_err_t input_double_until_correct(double *d)
{
    enum io_err_t errcode = IO_ERR_NONE;
    do {
        errcode = input_double(d);
        if(errcode == IO_ERR_EOF_REACHED) {
            fprintf(stderr, "\n\tEOF reached, exiting.\n");
            break;
        }
        else if(errcode == IO_ERR_ASSIGMENT_FAIL) {
            fprintf(stderr, "\tEnter a valid numeric value.\n\t");
        }
    } while(errcode != IO_ERR_NONE);
    return errcode;
}

FILE *open_file(const char *filename, const char *modes)
{
    utils_assert(filename != NULL);

    FILE* file = fopen(filename, modes);

    if(file == NULL)
        utils_colored_fprintf(
            stderr,
            ANSI_COLOR_BOLD_RED,
            "Could not open file <%s>\n",
            filename 
        );

    return file;
}

int create_dir(const char *path)
{

    utils_assert(path != NULL);

    __mode_t permissions = S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int err = mkdir(path, permissions);

    if(err == -1) 
        return 1;
    return 0;
}

char *get_current_working_dir()
{
    return getcwd(NULL, PATH_MAX);
}

size_t get_file_size(FILE *file)
{
    utils_assert(file != NULL);

    fseek(file, 0L, SEEK_END);
    long size_bytes = ftell(file);

    fseek(file, 0L, SEEK_SET);

    return (size_t)size_bytes;
}

char* bufferize_file(FILE *file)
{
    utils_assert(file != NULL);

    size_t file_size_bytes = get_file_size(file);
    char* file_buffer = (char*)calloc(file_size_bytes, sizeof(char));
    fread(file_buffer, sizeof(char), file_size_bytes, file);
    return file_buffer;
}

io_err_t utils_puts(const char *str)
{
    utils_assert(str != NULL);

    int err = 0;
    for(const char* str_char = str; *str_char != '\0'; ++str_char) {
        err = fputc((int)(*str_char), stdout);
        if(err == EOF)
            return IO_ERR_EOF_REACHED;
    }

    err = fputc((int)'\n', stdout);
    if(err == EOF)
        return IO_ERR_EOF_REACHED;
    
    return IO_ERR_NONE;
}

enum io_err_t utils_getline(char **line_ptr, size_t *n, FILE *stream, ssize_t *char_written)
{
    utils_assert(n != NULL);
    utils_assert(stream != NULL);
    utils_assert(char_written != NULL);

    if(*line_ptr == NULL) {
        *line_ptr = (char*)calloc(3, sizeof(char)); //REVIEW 3 = 'char'+'delim'+'\0'
        if(*line_ptr == NULL) {
            utils_log(LOG_LEVEL_ERR, "string buffer alllocation failed");
            return IO_ERR_ALLOCATION_FAIL;
        }
        *n = 3;
    }

    size_t char_cnt = 0;
    int stream_char = 0;
    while(stream_char != '\n') {
        stream_char = fgetc(stream);
        if(stream_char == EOF)
            return IO_ERR_EOF_REACHED;
        
        (*line_ptr)[char_cnt] = (char)stream_char;
        
        if(char_cnt < (*n - 2)) {
            ++(*n);
            char* reallocated_line_ptr = (char*)realloc(*line_ptr, (*n) * sizeof(char));
            if(reallocated_line_ptr == NULL) {
                utils_log(LOG_LEVEL_ERR, "string buffer reallocation failed");
                free(line_ptr);
                return IO_ERR_ALLOCATION_FAIL;
            }
            *line_ptr = reallocated_line_ptr;
        }

        ++char_cnt;
    }

    (*line_ptr)[char_cnt] = '\0';

    *char_written = (ssize_t)char_cnt + 1l;

    return IO_ERR_NONE;
}

char *utils_fgets(char *str, size_t count, FILE *stream)
{
    utils_assert(str != NULL);
    utils_assert(stream != NULL);

    if(count == 1ul) {
        utils_log(LOG_LEVEL_WARN, "done nothing");
        return NULL;
    }

    size_t char_cnt = 0;
    while(char_cnt <= count) {
        int stream_char = fgetc(stream);
        if(stream_char == EOF && char_cnt == 0)
            return NULL;

        str[char_cnt] = stream_char;
        ++char_cnt;

        if(stream_char == '\n')
            break;
    }

    str[char_cnt] = '\0';

    return str;
}
