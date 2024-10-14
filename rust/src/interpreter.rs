use std::{fmt::Error, io::Write};

use crate::find_brackets::*;


const DEFAULT_BUFFER_SIZE: usize = 65536;
const INPUT_BUFFER_SIZE: usize = 1024;
const CELL_SIZE: u32 = 8;


pub struct TuringMachine 
{
    input_buffer: [char; INPUT_BUFFER_SIZE],
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
            input_buffer: ['\0'; INPUT_BUFFER_SIZE],
            instructions: Vec::new(),
            data: [0; DEFAULT_BUFFER_SIZE],
            jump_preloader_buffer: [0; DEFAULT_BUFFER_SIZE],
            data_pointer: 0,
            instruction_pointer: 0
        }
    }

    pub fn get_code(&mut self, source_code: Vec<char>) 
    {
        // Removing every character that isn't a brainfuck command (optimization)
        for cmd in source_code 
        {
            match cmd 
            {
                '>' | '<' | '+' | '-' | 
                '[' | ']' | ',' | '.' => 
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

        while self.instruction_pointer < self.instructions.len() as u32 
        {
            match self.instructions[self.instruction_pointer as usize]
            {
                /* Shift right */
                '>' => {
                    self.data_pointer = (self.data_pointer.wrapping_add(1)) % DEFAULT_BUFFER_SIZE as u32;

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Shift left */
                '<' => {
                    self.data_pointer = (self.data_pointer.wrapping_sub(1)) % DEFAULT_BUFFER_SIZE as u32;

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Increase value */
                '+' => {
                    let cell_value = self.data[self.data_pointer as usize];

                    if cell_value == ((2 as u32).pow(CELL_SIZE) - 1) as u8 {
                        self.data[self.data_pointer as usize] = 0;
                    }
                    else {
                        self.data[self.data_pointer as usize] += 1;
                    }

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Decrease value */
                '-' => {
                    let cell_value = self.data[self.data_pointer as usize];

                    if cell_value == 0 {
                        self.data[self.data_pointer as usize] = 
                        ((2 as u32).pow(CELL_SIZE) - 1) as u8;
                    }
                    else {
                        self.data[self.data_pointer as usize] -= 1;
                    }

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Conditional Start */
                '[' => {
                    if self.data[self.data_pointer as usize] == 0 {
                        self.instruction_pointer = self.jump_preloader_buffer[self.instruction_pointer as usize];
                    } 
                    else {
                        self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                    }
                },
                
                /* Conditional end */
                ']' => {
                    if self.data[self.data_pointer as usize] != 0 {
                        self.instruction_pointer = self.jump_preloader_buffer[self.instruction_pointer as usize];
                    } 
                    else {
                        self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                    }
                },
                
                /* Input getter */
                ',' => {
                    // Getting input if has none
                    if self.input_buffer[0] == '\0' {
                        todo!();
                    }
    
                    // Defining the data pointer value as the first character of the input
                    self.data[self.data_pointer as usize] = self.input_buffer[0] as u8;
                
                    // Shifting the array to the left by 1
                    self.input_buffer[0] = '\0';
                    self.input_buffer.rotate_left(1);
    
                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Output data pointer value (ASCII) */
                '.' => {
                    print!("{}", self.data[self.data_pointer as usize] as char);

                    std::io::stdout()
                        .flush()
                        .unwrap();

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                _ => self.instruction_pointer = self.instruction_pointer.wrapping_add(1)
            }
        }
    }
}


pub fn run(code: Vec<char>) -> Result<(), Error> 
{
    let mut machine: TuringMachine = TuringMachine::new();

    machine.get_code(code);
    machine.execute_code();

    Ok(())
}
