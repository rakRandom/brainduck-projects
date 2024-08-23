#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream> // deals with input and output
#include <cstdint>  // C standart int library, contains uint8_t, uint16_t and et cetera.
#include <cstring>  // C standart string library, contains strlen(), strcpy() and et cetera.
#include <fstream>  // create, read and write to files

#include "vector.hpp"

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define DEFAULT_BUFFER_SIZE 65536
#define MEMORY_SIZE 65536


/* Main function
 * Todo: change from "argc" and "argv" to the proper arguments
 * for now, it is just an extension of the main.cpp at the `src/` folder
 * that is executed based on a conditional
 */
int interpret(int argc, char * argv[]);


#endif // INTERPRETER_HPP
