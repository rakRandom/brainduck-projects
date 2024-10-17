#ifndef FIND_BRACKETS_HPP
#define FIND_BRACKETS_HPP

#include <string>
#include "types.h"


/*
 *
 */
uMX find_closed_bracket(const std::string &src, uMX pos);

/*
 *
 */
uMX find_opened_bracket(const std::string &src, uMX pos);


#endif  // FIND_BRACKETS_HPP
