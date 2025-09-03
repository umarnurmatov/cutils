#include <stdio.h>

#include "stringutils.h"
#include "ioutils.h"

int main()
{
    char dest[10] = "ASD";
    utils_strncat(dest, "ASDF", 10);
    printf("%s\n", dest);

    utils_puts("asdf");
    printf("%c\n", *utils_strchr("ASDF", 'F'));
    printf("%d\n", utils_atoi("1234"));
    return 0;
}