#include "args_parser.hpp"

int option_pos(int argc, const char ** argv, const char value[], int flag = 0) 
{
    if (flag == 0) {
        char long_arg[1024];
        char short_arg[8];

        sprintf_s(long_arg, "--%s", value);
        sprintf_s(short_arg, "-%c", value[0]);

        for (int i = 1; i < argc; i++)
            if (strcmp(argv[i], long_arg) || strcmp(argv[i], short_arg))
                return i;
    }

    return 0;
}

const char * arg_value(int argc, const char ** argv, int pos)
{
    return NULL;
}
