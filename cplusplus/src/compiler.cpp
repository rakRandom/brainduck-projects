#include "compiler.hpp"


i32 get_code(const i8 file_path[], std::string &dest)
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
    for (i8 &ch : raw_code)
        if (ch == '>' || ch == '<' || ch == '+' || ch == '-' || 
            ch == '[' || ch == ']' || ch == ',' || ch == '.')
            dest.append(1, ch); // Fastest way, '+=' is simpler but slightly slower

    return 0;
}


i32 is_sintax_wrong(const std::string &src)
{
    for (uMX i = 0; i < src.size() - 1; i++) 
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


i32 compile_code(const std::string &src)
{
    std::ofstream output_c("output.c");  // TODO: if is '-o' between the args, the arg next to him will be the .exe name

    // Error condition - output.c cannot be created
    if (errno)
        return 1;

    // Adding the essential commands at the beggining of the file
    output_c << "#include <stdio.h>\n";
    output_c << "int main() {\n";
    output_c << "unsigned char d[65535];\n";
    output_c << "unsigned short p = 0;\n";
    output_c << "if (d == NULL) { return 1; }\n";

    // Adding the commands (c equivalents)
    for (const i8 &command : src)
    {
        switch (command)
        {
        case '+':
            output_c << "d[p]++;\n";
            break;
        case '-':
            output_c << "d[p]--;\n";
            break;
        case '>':
            output_c << "p++;\n";
            break;
        case '<':
            output_c << "p--;\n";
            break;
        case '[':
            output_c << "while (d[p] != 0) {\n";
            break;
        case ']':
            output_c << "}\n";
            break;
        case '.':
            output_c << "putchar(d[p]);\n";
            break;
        case ',':
            output_c << "d[p] = getchar();\n";
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


i32 compile(const i8 * filename) 
{
    std::string code = "";

    // Error condition 1 - Cannot get the code (commands), mainly because the file path is wrong.
    if (get_code(filename, code))
    {
        std::cerr << "Error: Cannot get the file content, check if the path is right." << std::endl;
        return 1;
    }
    
    // Error condition 2 - Code sintax is wrong (brackets not in pair)
    if (is_sintax_wrong(code))
    {
        std::cerr << "Error: Code sintax is wrong." << std::endl;
        return 1;
    }

    // Error condition 3 - Cannot compile the code, mainly because the user doesn't have a C compiler
    if (compile_code(code))
    {
        std::cerr << "Error: The code cannot be compiled, check if the C compiler is properly installed." << std::endl;
        return 1;
    }

    // Happy message to the user, if the code was compiled successfully, of course
    std::cout << "Code compiled successfully: " << filename << std::endl;
    
    return 0;
}
