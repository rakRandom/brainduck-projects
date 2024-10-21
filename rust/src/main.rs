use std::env;

mod interpreter;
mod find_brackets;
mod extractor;


fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Error: No file path");
        return;
    }

    let result_code = extractor::get_code_from_file(&args[1]);

    match result_code {
        Err(_) => println!("Error: Invalid file path"),
        Ok(code) => interpreter::run(code).unwrap()
    }
}
