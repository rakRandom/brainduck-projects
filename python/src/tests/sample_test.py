from interpreter import BrainduckInterpreter


if __name__ == "__main__":
    # 15 bits pointer and 8 bits cells
    interpreter = BrainduckInterpreter()

    with open("../../brainfuck/sample.bf", "r") as code:
        code = [cmd for cmd in code.read() if cmd in "><+-[],."]

    interpreter.run(code, debug_mode=True)
    print(f"\nMemory used: {interpreter.memory_used} bytes")
