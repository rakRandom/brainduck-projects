#include "interpreter.hpp"

i32 TuringMachine::get_code(std::string source_code) 
{
    // Removing every character that isn't a brainfuck command (optimization)
    for(u32 i = 0; i < source_code.size(); ++i)
        switch (source_code[i]) 
        {
            case '>':
            case '<':
            case '+':
            case '-':
            case '[':
            case ']':
            case ',':
            case '.':
                instructions += source_code[i];
            
            default:
                break;
        }

    // Getting all the brackets pairs
    for (u32 command = 0; command < instructions.size() - 1; command++) 
    {
        switch (instructions.at(command)) 
        {
            case '[':
                jump_preloader_buffer.at(command) = find_closed_bracket(instructions, command);
                break;
            
            case ']':
                jump_preloader_buffer.at(command) = find_opened_bracket(instructions, command);
                break;
            
            default:
                break;
        }
    }

    return 0;
}

i32 TuringMachine::execute_code() 
{
    while (instruction_pointer < instructions.length()) 
    {
        switch (instructions.at(instruction_pointer)) 
        {
            /* Shift right */
            case '>':
                data_pointer++;
                instruction_pointer++;
                break;
            
            /* Shift left */
            case '<':
                data_pointer--;
                instruction_pointer++;
                break;
            
            /* Increase value */
            case '+':
                ++data.at(data_pointer);
                instruction_pointer++;
                break;
            
            /* Decrease value */
            case '-':
                --data.at(data_pointer);
                instruction_pointer++;
                break;
            
            /* Conditional Start */
            case '[':
                if (data.at(data_pointer) == 0)
                    instruction_pointer = jump_preloader_buffer.at(instruction_pointer);
                else
                    instruction_pointer++;
                break;
            
            /* Conditional end */
            case ']':
                if (data.at(data_pointer) != 0)
                    instruction_pointer = jump_preloader_buffer.at(instruction_pointer);
                else
                    instruction_pointer++;
                break;
            
            /* Input getter */
            case ',':
                // Getting machine input buffer if has none
                if (input_buffer[0] == '\0')
                    std::cin.getline(input_buffer, sizeof(input_buffer) / sizeof(i8) - 1);

                // Defining the machine data pointer value as the first character of the machine input buffer
                data.at(data_pointer) = input_buffer[0];
            
                // Shifting the array to the left by 1
                for (i32 i = 1; i < sizeof(input_buffer) / sizeof(i8); i++)
                    input_buffer[i - 1] = input_buffer[i];
                
                instruction_pointer++;
                break;
            
            /* Output machine data pointer value (ASCII) */
            case '.':
                std::cout << (i8) data.at(data_pointer);
                instruction_pointer++;
                break;
            
            default:
                instruction_pointer++;
                break;
        }
    }

    return 0;
}


i32 interpret(const i8 * filename) 
{
    // Checking if the filename is NULL
    if (filename[0] == '\0') 
    {
        std::cerr << "Error: The file name cannot be NULL" << std::endl;
        return 4;
    }

    // Creating the machine
    TuringMachine machine;

    // Getting the file content
    std::ifstream in(filename);

    if (!in.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 3;
    }

    in.seekg(0, std::ios::end);
    size_t size = in.tellg();
    std::string raw_code(size, ' ');
    in.seekg(0);
    in.read(&raw_code[0], size); 
    in.close();
    
    // Getting the code
    if (machine.get_code(raw_code)) 
    {
        std::cerr << "Error: Failed to polish the code.\nCheck if there is any error in the source code." << std::endl;
        return 2;
    }

    // Executing the code
    if (machine.execute_code()) 
    {
        std::cerr << "Error: Failed to execute the code.\nCheck if there is any error in the source code." << std::endl;
        return 1;
    }
    
    return 0;
}
