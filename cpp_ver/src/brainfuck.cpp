#include "brainfuck.hpp"

#define DEFAULT_BUFFER_SIZE 65536
#define MEMORY_SIZE 65536

char input[DEFAULT_BUFFER_SIZE];
char commands[DEFAULT_BUFFER_SIZE];
vector<uint8_t> memory(MEMORY_SIZE);
uint16_t brackets_pos[DEFAULT_BUFFER_SIZE];
uint16_t cell, cmd = 0;


void setup(const char * file_path);

int main(int argc, char * argv[]) 
{
    if (*argv[1] == '\0')
        return 1;

    setup(argv[1]);

    while (cmd < sizeof(commands) / sizeof(char) - 1) 
    {
        switch (commands[cmd])
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
                    cmd = brackets_pos[cmd];
                else
                    cmd++;
                break;
            
            /* Conditional end */
            case ']':
                if (memory.get(cell) != 0)
                    cmd = brackets_pos[cmd];
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


void setup(const char * file_path) 
{
    std::fill(input, std::end(input), '\0');
    memory.fill(0);

    // Getting the file content
    std::ifstream in(file_path);
    std::string raw_code((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    
    // Removing every character that isn't a brainfuck command (optimization)
    std::string code;
    code.reserve(raw_code.size());
    for(uint32_t i = 0; i < raw_code.size(); ++i)
        if (raw_code[i] == '>' || 
            raw_code[i] == '<' || 
            raw_code[i] == '+' || 
            raw_code[i] == '-' || 
            raw_code[i] == '[' || 
            raw_code[i] == ']' || 
            raw_code[i] == ',' || 
            raw_code[i] == '.')
            code += raw_code[i];
    
    // Code string size
    // std::cout << sizeof(*code.c_str())*strlen(code.c_str()) << std::endl;

    // As the content may be null, it should be properly copied to the commands as a array of characters

    // memcpy version - faster:
    memcpy_s(commands, 
            sizeof(commands), 
            code.c_str(), 
            sizeof(*code.c_str())*strlen(code.c_str()));

    // strcpy version - cleaner:
    // strcpy_s(commands, sizeof(commands), code.c_str());

    for (uint16_t cmd = 0; cmd < strlen(commands); cmd++) 
    {
        if (commands[cmd] == '[')
            brackets_pos[cmd] = find_closed_bracket(commands, cmd);
        else if (commands[cmd] == ']')
            brackets_pos[cmd] = find_opened_bracket(commands, cmd);
    }
}
