use std::{fmt::Error, io::Write};


fn find_closed_bracket(_list: &String, _index: usize) -> u32 {0}
fn find_opened_bracket(_list: &String, _index: usize) -> u32 {0}


const DEFAULT_BUFFER_SIZE: usize = 65536;
const INPUT_BUFFER_SIZE: usize = 1024;
const CELL_SIZE: u32 = 8;


pub struct TuringMachine 
{
    input_buffer: [char; INPUT_BUFFER_SIZE],
    instructions: String,
    data: [u8; DEFAULT_BUFFER_SIZE],
    jump_preloader_buffer: Vec<u32>,  // Brackets positions

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
            instructions: "".to_string(),
            data: [0; DEFAULT_BUFFER_SIZE],
            jump_preloader_buffer: Vec::new(),
            data_pointer: 0,
            instruction_pointer: 0
        }
    }

    pub fn from(source_code: Option<String>) -> TuringMachine 
    {
        let jump_preloader_buffer = Vec::<u32>::new();

        match source_code 
        {
            None => {},
            Some(_code) => 
            {
                todo!();
            }
        }

        TuringMachine 
        {
            input_buffer: ['\0'; INPUT_BUFFER_SIZE],
            instructions: "".to_string(),
            data: [0; DEFAULT_BUFFER_SIZE],
            jump_preloader_buffer,
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
            match self.instructions.chars().nth(command).unwrap() 
            {
                '[' => 
                self.jump_preloader_buffer[command] = 
                find_closed_bracket(
                    &self.instructions, 
                    command
                ),
                
                ']' => 
                self.jump_preloader_buffer[command] = 
                find_opened_bracket(
                    &self.instructions, 
                    command
                ),
                
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

        while self.instruction_pointer < (self.instructions.len() - 1) as u32 
        {
            match self.instructions
                    .chars().nth(
                        self.instruction_pointer as usize
                    ).unwrap() 
            {
                /* Shift right */
                '>' => {
                    if self.data_pointer == (DEFAULT_BUFFER_SIZE - 1) as u32 
                    {
                        self.data_pointer = 0;
                    }
                    else 
                    {
                        self.data_pointer += 1;
                    }

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Shift left */
                '<' => {
                    if self.data_pointer == 0 
                    {
                        self.data_pointer = (DEFAULT_BUFFER_SIZE - 1) as u32;
                    }
                    else 
                    {
                        self.data_pointer -= 1;
                    }

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Increase value */
                '+' => {
                    let cell_value = self.data[self.data_pointer as usize];

                    if cell_value == ((2 as u32).pow(CELL_SIZE) - 1) as u8 
                    {
                        self.data[self.data_pointer as usize] = 0;
                    }
                    else 
                    {
                        self.data[self.data_pointer as usize] += 1;
                    }

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Decrease value */
                '-' => {
                    let cell_value = self.data[self.data_pointer as usize];

                    if cell_value == 0 
                    {
                        self.data[self.data_pointer as usize] = 
                        ((2 as u32).pow(CELL_SIZE) - 1) as u8;
                    }
                    else 
                    {
                        self.data[self.data_pointer as usize] += 1;
                    }

                    self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                },
                
                /* Conditional Start */
                '[' => {
                    if *self.data.get(self.data_pointer as usize).unwrap() == 0 
                    {
                        self.instruction_pointer = 
                            *self.jump_preloader_buffer
                                .get(
                                    self.instruction_pointer as usize
                                ).unwrap();
                    } 
                    else 
                    {
                        self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                    }
                },
                
                /* Conditional end */
                ']' => {
                    if *self.data.get(self.data_pointer as usize).unwrap() != 0 
                    {
                        self.instruction_pointer =  
                            *self.jump_preloader_buffer
                                .get(
                                    self.instruction_pointer as usize
                                ).unwrap();
                    } 
                    else 
                    {
                        self.instruction_pointer = self.instruction_pointer.wrapping_add(1);
                    }
                },
                
                /* Input getter */
                ',' => {
                    // Getting input if has none
                    if self.input_buffer[0] == '\0' 
                    {
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
                    print!(
                        "{}", 
                        *self.data.get(
                            self.data_pointer as usize
                        ).unwrap());

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
