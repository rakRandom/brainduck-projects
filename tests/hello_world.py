from modules.brainduck_interpreter import BrainDuckInterpreter


if __name__ == "__main__":
    # 4 bits pointer uses way less memory than 15 bits
    # cells uses memory dinamicaly, so will only use more memory if the value is higher
    # (e.g: 16 bits cell with value 0 is the same as a 4 bits one)
    interpreter = BrainDuckInterpreter(memory_bits=4, cell_bits=7)

    with open("../brainfuck_codes/hello_world.bf", "r") as code:
        code = [cmd for cmd in code.read() if cmd in "><+-[],."]

    # Expected result: "Hello World!"
    interpreter.run(code, debug=False)
    print(f"Memory used: {interpreter.memory_used} bytes")
