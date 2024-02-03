#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream> // deals with input and output
// #include <string>   // string library
#include <cstdint>  // C standart int library, contains uint8_t, uint16_t and et cetera.
#include <cstring>  // C standart string library, contains strlen(), strcpy() and et cetera.
// using namespace std;  // let us use std functions without explicity telling that is from std (std::)

// telling the brainfuck.cpp file that this functions will exist in some point (in link phase)
uint16_t find_closed_bracket(const char * cmds, uint16_t pos);
uint16_t find_opened_bracket(const char * cmds, uint16_t pos);

#endif // FUNCTIONS_H
