#include "interpreter.hpp"


// Only array to not be a vector, it's better that way
char input[DEFAULT_BUFFER_SIZE];
vector<char> commands(DEFAULT_BUFFER_SIZE);
vector<u8> memory(MEMORY_SIZE);
vector<u32> brackets_pos(DEFAULT_BUFFER_SIZE);
u32 cell, cmd = 0;

int interpret_code() 
{
    while (cmd < commands.length() - 1) 
    {
        switch (commands.get(cmd)) 
        {
            /* Shift right */
            case '>':
                cell++;
                cmd++;
                break;
            
            /* Shift left */
            case '<':
                cell--;
                cmd++;
                break;
            
            /* Increase value */
            case '+':
                memory.add_by_1(cell);
                cmd++;
                break;
            
            /* Decrease value */
            case '-':
                memory.sub_by_1(cell);
                cmd++;
                break;
            
            /* Conditional Start */
            case '[':
                if (memory.get(cell) == 0)
                    cmd = brackets_pos.get(cmd);
                else
                    cmd++;
                break;
            
            /* Conditional end */
            case ']':
                if (memory.get(cell) != 0)
                    cmd = brackets_pos.get(cmd);
                else
                    cmd++;
                break;
            
            /* Input getter */
            case ',':
                // Getting input if has none
                if (input[0] == '\0')
                    std::cin.getline(input, sizeof(input) / sizeof(char) - 1);

                // Defining the cell value as the first character of the input
                memory.set(cell, input[0]);
            
                // Shifting the array to the left by 1
                for (int i = 1; i < sizeof(input) / sizeof(char); i++)
                    input[i - 1] = input[i];
                
                cmd++;
                break;
            
            /* Output cell value (ASCII) */
            case '.':
                std::cout << (char) memory.get(cell);
                cmd++;
                break;
            
            default:
                cmd++;
                break;
        }
    }

    return 0;
}


int interpret(const char * filename) 
{
    if (filename[0] == '\0')
        return 1;

    std::fill(input, std::end(input), '\0');
    memory.fill(0);

    // Getting the file content
    std::ifstream in(filename);
    std::string raw_code((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    
    // Removing every character that isn't a brainfuck command (optimization)
    std::string code;
    code.reserve(raw_code.size());
    for(u32 i = 0; i < raw_code.size(); ++i)
        if (raw_code[i] == '>' || 
            raw_code[i] == '<' || 
            raw_code[i] == '+' || 
            raw_code[i] == '-' || 
            raw_code[i] == '[' || 
            raw_code[i] == ']' || 
            raw_code[i] == ',' || 
            raw_code[i] == '.')
            code += raw_code[i];

    // Copying from the code string to the commands
    commands.copy(code.c_str(), sizeof(*code.c_str())*strlen(code.c_str()));

    // Getting all the brackets pairs
    for (u32 cmd = 0; cmd < commands.length() - 1; cmd++) 
    {
        if (commands.get(cmd) == '[')
            brackets_pos.set(cmd, find_closed_bracket(commands.items(), cmd));
        else if (commands.get(cmd) == ']')
            brackets_pos.set(cmd, find_opened_bracket(commands.items(), cmd));
    }

    if (interpret_code())
        return 1;
    
    return 0;
}
