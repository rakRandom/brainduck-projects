use std::{fmt::Error, io::Write};

use crate::find_brackets::*;


const DEFAULT_BUFFER_SIZE: usize = 65536;
const CELL_SIZE: u32 = 8;
const MAX_FLUSH_HOLDER: u32 = 16;


pub struct TuringMachine 
{
    input_buffer: String,
    instructions: Vec<char>,
    data: [u8; DEFAULT_BUFFER_SIZE],
    jump_preloader_buffer: [u32; DEFAULT_BUFFER_SIZE],  // Brackets positions

    data_pointer: u32,
    instruction_pointer: u32,
}


impl TuringMachine 
{
    pub fn new() -> TuringMachine 
    {
        TuringMachine 
        {
            input_buffer: String::new(),
            instructions: Vec::new(),
            data: [0; DEFAULT_BUFFER_SIZE],
            jump_preloader_buffer: [0; DEFAULT_BUFFER_SIZE],
            data_pointer: 0,
            instruction_pointer: 0
        }
    }

    pub fn get_code(&mut self, source_code: Vec<char>) 
    {
        let mut polish_source_code: String = source_code.iter().collect();

        polish_source_code = polish_source_code.replace("[-]", "0");
        polish_source_code = polish_source_code.replace("[->+<]", "1");

        // Removing every character that isn't a brainfuck command (optimization)
        for cmd in polish_source_code.chars() 
        {
            match cmd 
            {
                '>' | '<' | '+' | '-' | '1' |
                '[' | ']' | ',' | '.' | '0' => 
                self.instructions.push(cmd),
                
                _ => {}
            }
        }

        // Getting all the brackets pairs
        for command in 0..self.instructions.len() 
        {
            match self.instructions[command]
            {
                '[' => self.jump_preloader_buffer[command] = find_closed_bracket(&self.instructions, command),
                
                ']' => self.jump_preloader_buffer[command] = find_opened_bracket(&self.instructions, command),
                
                _ => {}
            }
        }
    }

    pub fn execute_code(&mut self) 
    {
        if self.instructions.is_empty() 
        {
            return;
        }

        let mut flush_counter = 0;
        let mut input_buffer_vector: Vec<u8>;

        while self.instruction_pointer < self.instructions.len() as u32 
        {
            match self.instructions[self.instruction_pointer as usize]
            {
                /* Shift right */
                '>' => {
                    let mut counter = 1;

                    while self.instructions[(self.instruction_pointer + counter) as usize] == '>' {
                        counter += 1;
                    }
                    self.data_pointer = (self.data_pointer.wrapping_add(counter)) % DEFAULT_BUFFER_SIZE as u32;

                    self.instruction_pointer += counter;
                },
                
                /* Shift left */
                '<' => {
                    let mut counter = 1;

                    while self.instructions[(self.instruction_pointer + counter) as usize] == '<' {
                        counter += 1;
                    }

                    self.data_pointer = (self.data_pointer.wrapping_sub(counter)) % DEFAULT_BUFFER_SIZE as u32;

                    self.instruction_pointer += counter;
                },
                
                /* Increase value */
                '+' => {
                    let mut counter = 1;

                    while self.instructions[(self.instruction_pointer + counter) as usize] == '+' {
                        counter += 1;
                    }

                    self.data[self.data_pointer as usize] = 
                    (self.data[self.data_pointer as usize].wrapping_add(counter as u8)) % ((2 as u32).pow(CELL_SIZE) - 1) as u8;

                    self.instruction_pointer += counter;
                },
                
                /* Decrease value */
                '-' => {
                    let mut counter = 1;

                    while self.instructions[(self.instruction_pointer + counter) as usize] == '-' {
                        counter += 1;
                    }

                    self.data[self.data_pointer as usize] = 
                    (self.data[self.data_pointer as usize].wrapping_sub(counter as u8)) % ((2 as u32).pow(CELL_SIZE) - 1) as u8;

                    self.instruction_pointer += counter;
                },
                
                /* Conditional Start */
                '[' => {
                    if self.data[self.data_pointer as usize] == 0 {
                        self.instruction_pointer = self.jump_preloader_buffer[self.instruction_pointer as usize];
                    } 
                    else {
                        self.instruction_pointer += 1;
                    }
                },
                
                /* Conditional end */
                ']' => {
                    if self.data[self.data_pointer as usize] != 0 {
                        self.instruction_pointer = self.jump_preloader_buffer[self.instruction_pointer as usize];
                    } 
                    else {
                        self.instruction_pointer += 1;
                    }
                },
                
                /* Input getter - TODO: Add a counter to improve performance */
                ',' => {
                    std::io::stdout().flush().unwrap();
                    
                    // Getting input if has none
                    while self.input_buffer.is_empty() {
                        std::io::stdin().read_line(&mut self.input_buffer).unwrap();
                    }
    
                    input_buffer_vector = self.input_buffer.bytes().collect::<Vec<u8>>();

                    // Defining the data pointer value as the first character of the input
                    self.data[self.data_pointer as usize] = input_buffer_vector[0];
                
                    // Shifting the array to the left by 1
                    input_buffer_vector[0] = 0;
                    input_buffer_vector.rotate_left(1);

                    self.input_buffer = String::from_utf8(input_buffer_vector.to_vec()).unwrap();

                    self.instruction_pointer += 1;
                },
                
                /* Output data pointer value (ASCII) */
                '.' => {
                    print!("{}", self.data[self.data_pointer as usize] as char);

                    if flush_counter >= MAX_FLUSH_HOLDER {
                        std::io::stdout().flush().unwrap();
                        flush_counter = 0;
                    } else {
                        flush_counter += 1;
                    }
                    

                    self.instruction_pointer += 1;
                },

                /* Custom Command: Reset cell value */
                '0' => {
                    self.data[self.data_pointer as usize] = 0;
                    self.instruction_pointer += 1;
                },

                /* Custom Command: Pass value to the next */
                '1' => {
                    let next_pointer = ((self.data_pointer.wrapping_add(1)) % DEFAULT_BUFFER_SIZE as u32) as usize;

                    self.data[next_pointer] = self.data[next_pointer].wrapping_add(self.data[self.data_pointer as usize]);
                    self.data[self.data_pointer as usize] = 0;
                    
                    self.instruction_pointer += 1;
                },
                
                _ => self.instruction_pointer += 1
            }
        }

        print!("\n");
        std::io::stdout().flush().unwrap();
    }
}


pub fn run(code: Vec<char>) -> Result<(), Error> 
{
    let mut machine: TuringMachine = TuringMachine::new();

    machine.get_code(code);
    machine.execute_code();

    Ok(())
}
