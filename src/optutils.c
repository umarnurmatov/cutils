#include "optutils.h"

#include <stdlib.h>
#include <getopt.h>
#include <memory.h>
#include <stdio.h>

#include "assertutils.h"
#include "logutils.h"

#define LOG_CATEGORY_OPT "OPTIONS"

/// @internal
static int _utils_opt_arg_type_to_std(utils_opt_arg_type_t arg);

void utils_long_opt_get(int argc, char* argv[], utils_long_opt_t* long_opts, int count)
{
    utils_assert(long_opts != NULL);
    utils_assert(count > 0);

    option* long_opts_ = (option*)calloc((size_t)count + 1ul, sizeof(option));
    for(int opt_i = 0ul; opt_i < count; ++opt_i) {
        long_opts[opt_i]._val = opt_i;

        utils_assert(long_opts[opt_i].name != NULL);
        long_opts_[opt_i].name 
            = long_opts[opt_i].name;
        long_opts_[opt_i].has_arg 
            = _utils_opt_arg_type_to_std(long_opts[opt_i].opt_type);
        long_opts_[opt_i].flag = NULL;
        long_opts_[opt_i].val = long_opts[opt_i]._val;
    }

    int ret_val = 0;
    int opt_i   = 0;
    for( ;; ) {
        ret_val = getopt_long(
            argc, 
            argv, 
            "", 
            (const option*)long_opts_, 
            &opt_i
        );

        if(ret_val == -1)
            break;

        long_opts[opt_i].arg = optarg;

        if(long_opts[opt_i].opt_type == OPT_ARG_REQUIRED && ret_val == '?') {
            long_opts[opt_i].is_set = 0;
            continue;
        }

        long_opts[opt_i].is_set = 1;
    }

    for(int ind = 0; ind < count; ++ind)
        if(!long_opts[ind].is_set)
            UTILS_LOGE(LOG_CATEGORY_OPT, "log option --%s must be set", long_opts[ind].name);
    
    free(long_opts_);
}

int _utils_opt_arg_type_to_std(utils_opt_arg_type_t arg)
{
    switch(arg) {
        case OPT_ARG_NONE:
            return no_argument;
            break;
        case OPT_ARG_REQUIRED:
            return required_argument;
            break;
        case OPT_ARG_OPTIONAL:
            return optional_argument;
            break;
        default:
            return no_argument;
            break;
    }
}
