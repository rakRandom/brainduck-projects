use std::{fmt::Error, io::Write};

const DEFAULT_BUFFER_SIZE: usize = 65536;

fn get_brackets_pos(code: &Vec<char>) -> Result<Vec<char>, Error> {
    todo!();
}

pub fn run(code: &Vec<char>) -> Result<(), Error> {
    let brackets_pos = get_brackets_pos(code).unwrap();

    let mut memory: [u8; DEFAULT_BUFFER_SIZE] = [0; DEFAULT_BUFFER_SIZE];
    let mut input: [char; 1024] = ['\0'; 1024];

    let mut cell: u32 = 0;
    let mut cmd: u32 = 0;

    while cmd < code.len().into() - 1 {
        match code.get(cmd.into()).unwrap() {
            /* Shift right */
            '>' => {
                cell = cell.wrapping_add(1);
                cmd = cmd.wrapping_add(1);
            },
            
            /* Shift left */
            '<' => {
                cell = cell.wrapping_sub(1);
                cmd = cmd.wrapping_add(1);
            },
            
            /* Increase value */
            '+' => {
                todo!();
                memory[cell.into()] = memory[cell.into()].wrapping_add(1);
                cmd = cmd.wrapping_add(1);
            },
            
            /* Decrease value */
            '-' => {
                todo!();
                memory[cell.into()] = memory[cell.into()].wrapping_sub(1);
                cmd = cmd.wrapping_add(1);
            },
            
            /* Conditional Start */
            '[' => {
                if *memory.get(cell.into()).unwrap() == 0 {
                    cmd = *brackets_pos.get(cmd.into()).unwrap();
                } else {
                    cmd = cmd.wrapping_add(1);
                }
            },
            
            /* Conditional end */
            ']' => {
                if *memory.get(cell.into()).unwrap() != 0 {
                    cmd = *brackets_pos.get(cmd.into()).unwrap();
                } else {
                    cmd = cmd.wrapping_add(1);
                }
            },
            
            /* Input getter */
            ',' => {
                // Getting input if has none
                if input[0] == '\0' {
                    todo!();
                    std::cin.getline(input, sizeof(input) / sizeof(char) - 1);
                }

                // Defining the cell value as the first character of the input
                memory[cell.into()] = input[0];
            
                // Shifting the array to the left by 1
                input[0] = '\0';
                input.rotate_left(1);

                cmd = cmd.wrapping_add(1);
            },
            
            /* Output cell value (ASCII) */
            '.' => {
                print!("{}", *memory.get(cell.into()).unwrap());
                std::io::stdout().flush();
                cmd = cmd.wrapping_add(1);
            },
            
            _ => cmd = cmd.wrapping_add(1)
        }
    }

    Ok(())
}
