#include "compiler.hpp"
#include "interpreter.hpp"
#include "args_parser.hpp"


i32 main(i32 argc, const i8 ** argv)
{
    // Only show the help options, if it was required
    if (show_help(argc, argv))
        return 0;

    // Getting the file name
    const i8 * filename = NULL;

    if (argc == 2)
    {   filename = argv[1];   }
    else 
    {   filename = get_value(argc, argv, option_pos(argc, argv, "filename"));   }

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
    if (option_pos(argc, argv, "interpret"))  // If its to just interpret
    {
        if(interpret(filename, option_pos(argc, argv, "debug"))) 
        {
            std::cerr << "Error: Unsuccessful attempt to interpret the code." << std::endl;
            return 4;
        }
    }
    else 
    {
        std::string output_name = "output";

        if (get_value(argc, argv, option_pos(argc, argv, "output")) != NULL)
            output_name = get_value(argc, argv, option_pos(argc, argv, "output"));

        if(compile(filename, output_name, option_pos(argc, argv, "debug")))
        {
            std::cerr << "Error: Error at compile time." << std::endl;
            return 3;
        }

        if (!option_pos(argc, argv, "compile"))  // If its not to just compile
            system(output_name.append(RUN_COMMAND).c_str());
    }


    return 0;
}
