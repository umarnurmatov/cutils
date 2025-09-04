#include <stdio.h>

#include "stringutils.h"
#include "ioutils.h"

int main()
{
    char dest[10] = "";
    utils_strncpy(dest, "ABC", 2);
    utils_strcat(dest, "ASDF");
    printf("%s\n", dest);

    utils_puts("asdf");
    printf("%c\n", *utils_strchr("ASDF", 'F'));
    printf("%d\n", utils_atoi("1234"));

    utils_puts("ASDFGH");
    size_t n = 10;
    char* line = NULL;
    ssize_t char_written = 0;
    utils_getline(&line, &n, stdin, &char_written);
    printf("%s %ld", line, char_written);

    free(line);

    return 0;
}