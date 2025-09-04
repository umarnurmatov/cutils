#pragma once

#include <stdio.h>

#include "colorutils.h"

/// @brief input error types
enum io_err_t
{
    IO_ERR_EOF_REACHED,
    IO_ERR_ASSIGMENT_FAIL,
    IO_ERR_ALLOCATION_FAIL,
    IO_ERR_NONE
};

/// @brief clears stdin buffer until reaches \\n or EOF
void clear_stdin_buffer();

/// @brief validated input of floating-point numeric value
/// @param d pointer to variable where inputed value will be stored
/// @return see io_err_t for explanations
enum io_err_t input_double(double *d);

/// @brief validated input of floating-point numeric value until correct value entered
/// @param d pointer to variable where inputed value will be stored
/// @return 1 if EOF occured in stdin, 0 otherwise
enum io_err_t input_double_until_correct(double *d);

/// @brief open file
/// @param filename filename
/// @param modes file open modes
/// @return pointer to filestream if file opened successfully, NULL otherwise
FILE* open_file(const char *filename, const char *modes);

/// @brief creates directory
/// @param path full path
/// @return 0 if dir created successfully, 1 otherwise
int create_dir(const char* path);

/// @brief returns string containing cwd path, buffer is allocated internally
/// @return pointer to string buffer on success, NULL otherwise 
char* get_current_working_dir();

/// @brief get file size in bytes
/// @param file filestream
/// @return file size in bytes 
size_t get_file_size(FILE* file);

/// @brief reads file to buffer and returns pointer to that buffer
/// @param file file to bufferize
/// @return pointer to buffer 
char* bufferize_file(FILE* file);

enum io_err_t utils_puts(const char* str);

enum io_err_t utils_getline(char **line_ptr, size_t *n, FILE *stream, ssize_t *char_written);

char* utils_fgets(char* str, size_t count, FILE* stream);