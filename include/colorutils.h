#pragma once

#include <stdio.h>

#include "assertutils.h"
#include "utils.h"

typedef const char* tty_mode_t;

ATTR_UNUSED static tty_mode_t ANSI_COLOR_RED         = "\x1b[1;31m";
ATTR_UNUSED static tty_mode_t ANSI_COLOR_GREEN       = "\x1b[1;32m";
ATTR_UNUSED static tty_mode_t ANSI_COLOR_YELLOW      = "\x1b[1;33m";
ATTR_UNUSED static tty_mode_t ANSI_COLOR_BLUE        = "\x1b[1;34m";

ATTR_UNUSED static tty_mode_t ANSI_COLOR_BOLD_WHITE  = "\x1b[1;38;5;15m";
ATTR_UNUSED static tty_mode_t ANSI_COLOR_BOLD_RED    = "\x1b[1;38;5;160m";
ATTR_UNUSED static tty_mode_t ANSI_COLOR_BOLD_GREEN  = "\x1b[1;38;5;82m";
ATTR_UNUSED static tty_mode_t ANSI_COLOR_BOLD_YELLOW = "\x1b[1;38;5;226m";
ATTR_UNUSED static tty_mode_t ANSI_COLOR_BOLD_BLUE   = "\x1b[1;38;5;27m";

ATTR_UNUSED static tty_mode_t ANSI_COLOR_RESET       = "\x1b[0m";

/// @brief function to print text with ANSI mode; checks if stream is console
/// @param stream output stream
/// @param mode ANSI color mode 
/// @param fmtstring formatted string 
void utils_colored_fprintf(FILE* stream, tty_mode_t mode, const char* fmtstring, ...)
    __attribute__ ((format (printf, 3, 4)));

/// @brief function to print text with ANSI mode; checks if stream is console
/// @param stream output stream
/// @param mode ANSI color mode 
/// @param fmtstring formatted string 
void utils_colored_vfprintf(FILE* stream, tty_mode_t mode, const char* fmtstring, va_list vlist);
