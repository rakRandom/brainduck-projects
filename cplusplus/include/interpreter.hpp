#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream> // deals with input and output
#include <cstring>
#include <fstream>  // create, read and write to files
#include <vector>

#include "find_brackets.hpp"
#include "types.h"

#define DEFAULT_BUFFER_SIZE 65536
#define MEMORY_SIZE 65536


/* Simulates a Turing machine, executes Brainfuck code
 */
class TuringMachine 
{
    private:
        i8 input_buffer[DEFAULT_BUFFER_SIZE];
        std::string instructions;
        std::vector<u8> data;
        std::vector<u32> jump_preloader_buffer;  // Brackets positions
        u32 data_pointer;
        u32 instruction_pointer;

    public:
        TuringMachine() : instructions(""), data(MEMORY_SIZE, 0), jump_preloader_buffer(DEFAULT_BUFFER_SIZE, 0) {
            std::memset(input_buffer, 0, DEFAULT_BUFFER_SIZE);

            instructions.reserve(DEFAULT_BUFFER_SIZE);
            data_pointer = 0;
            instruction_pointer = 0;
        }

        /* Gets the final code, faster and lighter, based on a source code
         * Also, preloads the jumps on the code
         */
        i32 get_code(std::string source_code);

        i32 execute_code();
};


/* Main function
 * Todo: change from "argc" and "argv" to the proper arguments
 * for now, it is just an extension of the main.cpp at the `src/` folder
 * that is executed based on a conditional
 */
i32 interpret(const i8 * filename);


#endif  // INTERPRETER_HPP
