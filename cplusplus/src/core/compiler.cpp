#include "compiler.hpp"


sz_t find_closed_bracket(const std::string &src, sz_t pos) {
    sz_t openbt = 0;

    for (size_t i = pos + 1; i < src.size(); i++) {
        switch (src[i]) {
        case '[':
            openbt++;
            break;
        case ']':
            if (openbt == 0)
                return (sz_t) i;
            else
                openbt--;
            break;
        
        default:
            break;
        }
    }
    return -1;
}


sz_t find_opened_bracket(const std::string &src, sz_t pos) {
    sz_t closebt = 0;

    for (size_t i = pos - 1; i >= 0; i--) {
        switch (src[i]) {
        case ']':
            closebt++;
            break;
        case '[':
            if (closebt == 0)
                return (sz_t) i;
            else
                closebt--;
            break;
        
        default:
            break;
        }
    }
    return -1;
}


int get_code(const char file_path[], std::string &dest)
{
    std::string file_line;
    std::string raw_code;
    std::ifstream file(file_path);

    // Error condition - File path is wrong or simply the file cannot be opened
    if (errno)
        return 1;
    
    // Getting file content
    while(std::getline(file, file_line))
        raw_code.append(file_line);

    file.close();

    // Filtering non-command characters
    dest.reserve(raw_code.size());
    for (char &ch : raw_code)
        if (ch == '>' || ch == '<' || ch == '+' || ch == '-' || 
            ch == '[' || ch == ']' || ch == ',' || ch == '.')
            dest.append(1, ch); // Fastest way, '+=' is simpler but slightly slower

    return 0;
}


int is_sintax_wrong(const std::string &src)
{
    for (sz_t i = 0; i < src.size() - 1; i++) 
    {
        if (src[i] == '[')
            if (find_closed_bracket(src, i) == -1)
                return 1;
        else if (src[i] == ']')
            if (find_opened_bracket(src, i) == -1)
                return 1;
    }
    return 0;
}


int compile_code(const std::string &src)
{
    std::ofstream output_c("output.c");  // TODO: if is '-o' between the args, the arg next to him will be the .exe name

    // Error condition - output.c cannot be created
    if (errno)
        return 1;

    // Adding the essential commands at the beggining of the file
    output_c << "#include <stdio.h>\n";
    output_c << "#include <stdlib.h>\n";
    output_c << "#include <stdint.h>\n";
    output_c << "int main() {\n";
    output_c << "uint8_t *p = (uint8_t *) calloc(30000, 1);\n";
    output_c << "if (p == NULL) { return 1; }\n";

    // Adding the commands (c equivalents)
    for (const char &command : src)
    {
        switch (command)
        {
        case '+':
            output_c << "++*p;\n";
            break;
        case '-':
            output_c << "--*p;\n";
            break;
        case '>':
            output_c << "++p;\n";
            break;
        case '<':
            output_c << "--p;\n";
            break;
        case '[':
            output_c << "while (*p != 0) {\n";
            break;
        case ']':
            output_c << "}\n";
            break;
        case '.':
            output_c << "putchar(*p);\n";
            break;
        case ',':
            output_c << "*p = getchar();\n";
            break;
        
        default:
            output_c.clear();
            output_c.close();
            return 1;
        }
    }

    // Finalizing file operations
    output_c << "return(0);\n}";
    output_c.close();

    // Compiling
    if (system(COMPILE_COMMAND))
        return 1;

    return 0;
}


int compile(int argc, const char ** argv) 
{
    std::string code = "";

    // Error condition 1 - Not enough parameters, 2 is (currently) the only one accepted, .exe name and file path
    if (argc != 2)
    { 
        std::cout << "Error: The only parameter accepted is the file path." << std::endl;
        return 1;
    }

    // Error condition 2 - Cannot get the code (commands), mainly because the file path is wrong.
    if (get_code(argv[1], code))
    {
        std::cout << "Error: Cannot get the file content, check if the path is right." << std::endl;
        return 1;
    }
    
    // Error condition 3 - Code sintax is wrong (brackets not in pair)
    if (is_sintax_wrong(code))
    {
        std::cout << "Error: Code sintax is wrong." << std::endl;
        return 1;
    }

    // Error condition 4 - Cannot compile the code, mainly because the user doesn't have a C compiler
    if (compile_code(code))
    {
        std::cout << "Error: The code cannot be compiled, check if the C compiler is properly installed." << std::endl;
        return 1;
    }

    // Happy message to the user, if the code was compiled successfully, of course
    std::cout << "Code compiled successfully: " << argv[1] << std::endl;
    
    return 0;
}
