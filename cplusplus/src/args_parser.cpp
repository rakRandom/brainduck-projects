#include "args_parser.hpp"
#include <iostream>

int option_pos(int argc, const char ** argv, const char value[], int flag) 
{
    if (flag == 0) {
        char long_arg[1024];
        char short_arg[8];

        sprintf_s(long_arg, "--%s", value);
        sprintf_s(short_arg, "-%c", value[0]);

        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], long_arg) || !strcmp(argv[i], short_arg))
                return i;
        }
    }

    return 0;
}

int show_help(int argc, const char ** argv)
{
    if (option_pos(argc, argv, "help") && argc == 2) {
        std::cout << 
        "[-c/--compile]            - to only compile the code" << std::endl << 
        "[-i/--interpret]          - to only interpret the code" << std::endl << 
        "[-f/--filename file_path] - define where to find the file (required)" << std::endl << 
        std::endl << 
        "`brainduck_cpp.exe [filename]` to execute without any option." << std::endl << 
        "Executing without options will compile the source code and run the compiled code" << 
        std::endl;

        return 0;
    }

    return 1;
}
