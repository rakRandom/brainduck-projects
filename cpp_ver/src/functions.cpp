#include "functions.h"


uint16_t find_closed_bracket(const char * cmds, uint16_t pos) {
    uint16_t openbt = 0;

    for (size_t i = pos + 1; i < strlen(cmds); i++) {
        switch (cmds[i]) {
        case '[':
            openbt++;
            break;
        case ']':
            if (openbt == 0)
                return (uint16_t) i;
            else
                openbt--;
            
            break;
        
        default: break;
        }
    }
    
    return -1;
}


uint16_t find_opened_bracket(const char * cmds, uint16_t pos) {
    uint16_t closebt = 0;

    for (size_t i = pos - 1; i >= 0; i--) {
        switch (cmds[i]) {
        case ']':
            closebt++;
            break;
        case '[':
            if (closebt == 0)
                return (uint16_t) i;
            else
                closebt--;
            
            break;
        
        default: break;
        }
    }
    
    return -1;
}
