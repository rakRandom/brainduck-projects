pub fn find_closed_bracket(list: &String, pos: usize) -> u32 {
    let mut openbt = 0;

    for i in (pos + 1)..list.chars().count()
    {
        match list.chars().nth(i).unwrap() 
        {
            '[' =>  openbt += 1,

            ']' => {
                if openbt == 0 {
                    return i as u32;
                } else {
                    openbt -= 1;
                }
            }
            
            _ => {}
        }
    }

    u32::MAX
}

pub fn find_opened_bracket(list: &String, pos: usize) -> u32 {
    let mut closebt = 0;

    for i in (0..(pos - 1)).rev()
    {
        match list.chars().nth(i).unwrap()
        {
            ']' =>  closebt += 1,

            '[' => {
                if closebt == 0 {
                    return i as u32;
                } else {
                    closebt -= 1;
                }
            },
            
            _ => {}
        }
    }

    u32::MAX
}
