from modules.brainduck_interpreter import BrainDuckInterpreter


if __name__ == "__main__":
    # 15 bits pointer and 8 bits cells
    interpreter = BrainDuckInterpreter()

    with open("brainduck_codes/sample.bf", "r") as code:
        code = [cmd for cmd in code.read() if cmd in "><+-[],."]

    interpreter.run(code, debug=True)
    print(f"\nMemory used: {interpreter.memory_usage()} bytes")
