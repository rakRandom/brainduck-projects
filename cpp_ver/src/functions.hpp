#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdint>  // C standart int library, contains uint8_t, uint16_t and et cetera.
#include <cstring>  // C standart string library, contains strlen(), strcpy() and et cetera.

#endif // FUNCTIONS_H

typedef uint16_t  u16;

u16 find_closed_bracket(const char * cmds, u16 pos) {
    u16 openbt = 0;

    for (size_t i = pos + 1; i < strlen(cmds); i++) {
        switch (cmds[i]) {
        case '[':
            openbt++;
            break;
        case ']':
            if (openbt == 0)
                return (u16) i;
            else
                openbt--;
            break;
        
        default:
            break;
        }
    }
    return -1;
}


u16 find_opened_bracket(const char * cmds, u16 pos) {
    u16 closebt = 0;

    for (size_t i = pos - 1; i >= 0; i--) {
        switch (cmds[i]) {
        case ']':
            closebt++;
            break;
        case '[':
            if (closebt == 0)
                return (u16) i;
            else
                closebt--;
            break;
        
        default:
            break;
        }
    }
    return -1;
}
