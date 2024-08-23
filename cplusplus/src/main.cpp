#include "core/args_parser.hpp"
#include "core/compiler.hpp"
#include "core/interpreter.hpp"


int main(int argc, const char ** argv)
{
    // Only show the help option
    if (option_pos(argc, argv, "help") && argc == 2) {
        std::cout << 
        "[-c/--compile]            to compile the code" << std::endl << 
        "[-i/--interpret]          to interpret the code" << std::endl << 
        "[-f/--filename file_path] define where to find the file (required)" << std::endl << 
        std::endl << 
        "`brainduck.exe [filename]` to execute without any option." << std::endl << 
        "Executing without options will only compile, without interpreting it, but if the compilation was successful, it will run automatically the compiled code" << 
        std::endl;
        return 0;
    }

    // Getting args and options
    int is_to_compile, is_to_interpret, filename_index;

    if (argc == 2) {
        is_to_compile = 1;
        is_to_interpret = 0;
        filename_index = 1;
    }
    else {
        is_to_compile = option_pos(argc, argv, "compile");
        is_to_interpret = option_pos(argc, argv, "interpret");
        filename_index = option_pos(argc, argv, "filename") + 1;
    }

    // Error tests
    if (filename_index >= argc) {
        std::cout << "Error: Filename not found in args." << std::endl;
        return 1;
    }
    if (argv[filename_index][0] == '-') {
        std::cout << "Error: Filename cannot be an option." << std::endl;
        return 2;
    }

    // Execution
    if (is_to_compile)
        if(compile(argc, argv)) {
            std::cout << "Error: Error at compile time." << std::endl;
            return 3;
        }
    
    if (is_to_interpret)
        if(interpret(argc, argv)) {
            std::cout << "Error: Unsuccessful attempt to interpret the code." << std::endl;
            return 4;
        }

    return 0;
}
