#include "optutils.h"

#include <stdlib.h>

int main(int argc, char* argv[])
{
    utils_long_opt_t long_opts[] = {
        { OPT_ARG_REQUIRED, "filename", NULL, 0, 0 },
        { OPT_ARG_NONE,     "some",     NULL, 0, 0 }
    };

    utils_long_opt_get(argc, argv, long_opts, sizeof(long_opts) / sizeof(long_opts[0]));

    return 0;
}
