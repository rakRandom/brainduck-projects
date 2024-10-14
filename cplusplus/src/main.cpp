#include "compiler.hpp"
#include "interpreter.hpp"
#include "args_parser.hpp"


i32 main(i32 argc, const i8 ** argv)
{
    // Only show the help options
    if (show_help(argc, argv))
        return 0;

    // Getting args and options
    i32 mode = 2;
    const i8 * filename = NULL;

    if (argc == 2) 
    {
        filename = argv[1];
    } else 
    {
        if(option_pos(argc, argv, "compile"))
            mode = 1;
        if(option_pos(argc, argv, "interpret"))
            mode = 0;
        
        filename = get_value(argc, argv, option_pos(argc, argv, "filename") + 1);
    }

    // Error tests
    if (filename == NULL) 
    {
        std::cerr << "Error: Filename not found in args." << std::endl;
        return 1;
    }
    if (filename[0] == '-') 
    {
        std::cerr << "Error: Filename cannot be an option." << std::endl << 
        "If you are using a mode flag (interpret/compile)," << std::endl << 
        "use the `filename` flag to define the file name" << std::endl;
        return 2;
    }

    // Execution
    switch (mode) {
        case 0:
            if(interpret(filename)) 
            {
                std::cerr << "Error: Unsuccessful attempt to interpret the code." << std::endl;
                return 4;
            }
            break;

        case 1:
            if(compile(filename)) 
            {
                std::cerr << "Error: Error at compile time." << std::endl;
                return 3;
            }
            break;
        
        case 2:
            if(compile(filename)) 
            {
                std::cerr << "Error: Error at compile time." << std::endl;
                return 3;
            }
            else
                system(RUN_COMMAND);
            break;
        
        default:
            break;
    }

    return 0;
}
