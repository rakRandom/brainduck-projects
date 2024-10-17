#ifndef ARGS_PARSER_HPP
#define ARGS_PARSER_HPP

#include <cstdio>
#include <string.h>

#include "types.h"


/* Do not pass any string with a space dividing words
 * Flag 0 = long and short arguments are valid
 * Returns the index of the arg
 */
i32 option_pos(i32 argc, const i8 ** argv, const i8 value[], i32 flag = 0);


/* Shows the help text if it was called
 */
i32 show_help(i32 argc, const i8 ** argv);


/* Gets the value at a certain position with bound check
 * Returns NULL if `pos` is greater than `argc` or below 0
 * Returns a char pointer if not
 */
inline const i8 * get_value(i32 argc, const i8 ** argv, i32 pos)
{
    if (pos + 1 > argc || pos <= 0)
        return NULL;
    return argv[pos + 1];
}


#endif  // ARGS_PARSER_HPP
