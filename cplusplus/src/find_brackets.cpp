#include "find_brackets.hpp"

uMX find_closed_bracket(const std::string &src, uMX pos) 
{
    uMX openbt = 0;

    for (size_t i = pos + 1; i < src.size(); i++) {
        switch (src[i]) {
        case '[':
            openbt++;
            break;
        case ']':
            if (openbt == 0)
                return (uMX) i;
            else
                openbt--;
            break;
        
        default:
            break;
        }
    }
    return -1;
}


uMX find_opened_bracket(const std::string &src, uMX pos) 
{
    uMX closebt = 0;

    for (size_t i = pos - 1; i >= 0; i--) {
        switch (src[i]) {
        case ']':
            closebt++;
            break;
        case '[':
            if (closebt == 0)
                return (uMX) i;
            else
                closebt--;
            break;
        
        default:
            break;
        }
    }
    return -1;
}
