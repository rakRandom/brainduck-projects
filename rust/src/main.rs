mod interpreter;


fn main() {
    interpreter::run(vec!['+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '.']).unwrap();
}
