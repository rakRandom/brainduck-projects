from modules.brainduck_interpreter import BrainDuckInterpreter


if __name__ == "__main__":
    interpreter = BrainDuckInterpreter(memory_bits=4)

    with open("brainduck_codes/user_interaction.bf", "r") as code:
        code = [cmd for cmd in code.read() if cmd in "><+-[],."]

    # Try typing the alphabet when you run the code
    interpreter.run(code, debug=False)
    print(f"\nMemory used: {interpreter.memory_usage()} bytes")
