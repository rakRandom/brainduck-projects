#include "core/compiler.hpp"
#include "core/interpreter.hpp"


int main(int argc, char * argv[])
{
    int op = 0;

    if (op == 1)
        compile(argc, argv);
    
    else if (op == 2)
        interpret(argc, argv);

    return 0;
}
