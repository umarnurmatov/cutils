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

/// @brief validated input of string until correct string entered; allocates buffer with malloc()
/// @param[in] str pointer to pointer to memory where string will be stored
/// @return see \ref io_err_t
/// @return 1 
enum io_err_t input_string_until_correct(char** str, size_t* str_len);

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

/// @brief   read file to buffer
/// @details reads \p file contents to allocated buffer
/// @param   file file to bufferize
/// @return  pointer to buffer 
char* bufferize_file(FILE* file);

/// @brief   write string to stdout stream
/// @details writes \p str contents to stdout stream
///          and puts newline charachter in the end
/// @param   str string to write
/// @return  see \ref io_err_t
enum io_err_t utils_puts(const char* str);

/// @brief   write string to file
/// @details writes \str contents to \p file filestream
///          and puts newline charachter in the end
/// @param   str string to write
/// @return  see \ref io_err_t
enum io_err_t utils_fputs(const char* str, FILE* stream);

/// @brief   get '\\n'-ended string from file
/// @details writes '\\n'-ended string from \p stream to
///          buffer pointed by \p line_ptr; writes '\\n'
///          and '\\0' charachters to the buffer end;\n
///
///          if buffer isn't large enough, reallocates 
///          it using realloc(); buffer size is than 
///          written to \p char_written and \p n
/// @param   line_ptr pointer to a buffer where readed line will
///          be stored
/// @param   n            pointer to a buffer siza
/// @param   stream       filestream to read from
/// @param   char_written pointer to variable, where readed charachters
///                       count will be stored
/// @return  see \ref io_err_t
enum io_err_t utils_getline(char **line_ptr, size_t *n, FILE *stream, ssize_t *char_written);

/// @brief get at most \p count charachters from file
/// @details get at most \p count charachters from \p stream filestream
///          and write it to \p str string;\n
///
///          if '\\n' charachter occured, stops
/// @param   str    string buffer
/// @param   count  charachters to read
/// @param   stream filestream to read from
/// @return  \p str
char* utils_fgets(char* str, size_t count, FILE* stream);
