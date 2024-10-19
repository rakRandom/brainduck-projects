mod interpreter;
mod find_brackets;
mod extractor;


fn main() {
    interpreter::run(extractor::get_code_from_file("../brainfuck/simple_input.bf".to_string())).unwrap();
}
