from modules.brainduck_interpreter import BrainDuckInterpreter


if __name__ == '__main__':
    bf_interpreter = BrainDuckInterpreter()

    code: list[str] | str = list()
    user_input: str = ""

    print("Brainfuck interpreter")

    while True:
        user_input = input("> ")
        if user_input != "":
            code.append(user_input)
        else:
            break

    code = [cmd for cmd in "".join(code) if cmd in "><+-[],."]
    bf_interpreter.run(code)
