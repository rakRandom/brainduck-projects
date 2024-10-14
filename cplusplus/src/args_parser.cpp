#include "args_parser.hpp"
#include <iostream>

i32 option_pos(i32 argc, const i8 ** argv, const i8 value[], i32 flag) 
{
    if (flag == 0) 
    {
        i8 long_arg[1024];
        i8 short_arg[8];

        sprintf_s(long_arg, "--%s", value);
        sprintf_s(short_arg, "-%c", value[0]);

        for (i32 i = 1; i < argc; i++) 
        {
            if (!strcmp(argv[i], long_arg) || !strcmp(argv[i], short_arg))
                return i;
        }
    }

    return 0;
}

i32 show_help(i32 argc, const i8 ** argv)
{
    if (option_pos(argc, argv, "help") && argc == 2) 
    {
        std::cout << 
        "[-c/--compile]            - to only compile the code" << std::endl << 
        "[-i/--interpret]          - to only interpret the code" << std::endl << 
        "[-f/--filename file_path] - define where to find the file (required)" << std::endl << 
        std::endl << 
        "`brainduck_cpp.exe [filename]` to execute without any option." << std::endl << 
        "Executing without options will compile the source code and run the compiled code" << 
        std::endl;

        return 1;
    }

    return 0;
}
