#ifndef COMPILER_HPP
#define COMPILER_HPP

// This compiler needs a C compiler (GCC as default)

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>

#include "find_brackets.hpp"
#include "types.h"

// Change this if you are using a compiler other than GCC (at least the GCC C Compiler, you don't need the GCC Compiler Collection in full)
// Make sure that you know what you're doing when changing this commands
#define COMPILE_COMMAND "gcc -O3 -static -static-libgcc"
#define RUN_COMMAND ".exe && echo."


class Compiler {
    public:
        std::string instructions;
        bit debug_mode;

        i32 get_code(std::string source_code);
        i32 compile_code(std::string output_name);

        Compiler() : instructions(""), debug_mode(false) {}
};


/* Main function
 * Compiles the Brainfuck code at a `filename` file.
 * `output_name` is the output file name
 */
i32 compile(std::string filename, std::string output_name, i32 debug_flag);


#endif  // COMPILER_HPP
