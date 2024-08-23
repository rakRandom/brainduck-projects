#ifndef ARGS_PARSER_HPP
#define ARGS_PARSER_HPP

#include <cstdio>
#include <string.h>

/* Do not pass any string with a space dividing words
 * Flag 0 = long and short arguments are valid
 * Returns the index of the arg
 */
int option_pos(int argc, const char ** argv, const char * value, int flag = 0);

#endif  // ARGS_PARSER_HPP
