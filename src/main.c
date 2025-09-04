#include <stdio.h>

#include "stringutils.h"
#include "ioutils.h"

int main()
{
    char dest[10] = "";
    utils_strncpy(dest, "ABC", 2);
    utils_strcat(dest, "ASDF");
    printf("1. ABC + ASDF = %s\n", dest);

    utils_puts("2. Hello, i'm puts");
    const char* strint = "13941";
    char ctofind = 'F';
    const char* str = "ASDFGHJK";
    printf("3. %c position in %s: %ld\n", ctofind, str, utils_strchr(str, ctofind) - str);
    printf("4. [str] %s = (int) %d\n", strint, utils_atoi(strint));

    size_t n = 10;
    char* line = NULL;
    ssize_t char_written = 0;
    printf("5. Enter something: ");
    utils_getline(&line, &n, stdin, &char_written);
    printf("... got it (written %ld bytes to buffer): %s", char_written, line);

    char* buf = (char*)calloc(20, sizeof(char));
    printf("6. Enter something: ");
    utils_fgets(buf, 5, stdin);
    printf("...got it (again): %s\n", buf);

    free(line);
    free(buf);

    return 0;
}