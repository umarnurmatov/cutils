#pragma once

/// @brief optional argument type
typedef enum utils_opt_arg_type_t
{
    OPT_ARG_NONE,
    OPT_ARG_REQUIRED,
    OPT_ARG_OPTIONAL
} utils_opt_arg_type_t;

/// @brief optional argument struct
typedef struct utils_long_opt_t
{
    /// option type
    utils_opt_arg_type_t opt_type;

    /// option name
    const char* name;

    /// argument value, init with NULL
    char* arg;

    /// is argument set, init with 0
    int is_set;

    /// for internal usage, init with 0
    int _val;
} utils_long_opt_t;

/// @brief get long options
/// @param argc provided by main()
/// @param argv provided by main()
/// @param long_opts options array, see \ref utils_long_opt_t
/// @param count \p long_opts size
void utils_long_opt_get(int argc, char* argv[], utils_long_opt_t* long_opts, int count);

