#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream> // deals with input and output
#include <cstring>
#include <fstream>  // create, read and write to files

#include "vector.hpp"
#include "find_brackets.hpp"
#include "types.h"

#define DEFAULT_BUFFER_SIZE 65536
#define MEMORY_SIZE 65536


/* Main function
 * Todo: change from "argc" and "argv" to the proper arguments
 * for now, it is just an extension of the main.cpp at the `src/` folder
 * that is executed based on a conditional
 */
int interpret(const char * filename);


#endif // INTERPRETER_HPP
