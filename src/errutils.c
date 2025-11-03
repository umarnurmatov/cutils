#include "errutils.h"
#include "assertutils.h"

void utils_set_err(int* err, int to_set)
{
    utils_assert(err);

    *err |= to_set;
}

int utils_get_err(int err, int is_set)
{
    return err & is_set;
}
