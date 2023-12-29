from sys import exit


class BrainDuckInterpreter:
    def __init__(self): ...
    def run(self, code, debug_mode=False): ...

    @property
    def memory_used(self):
        return None


def execute_shell(interpreter: BrainDuckInterpreter, debug_mode: bool = False):
    code: list[str] | str = list()
    user_input: str

    print("Brainfuck interpreter shell - type \"exit\" to exit")
    while True:
        while True:
            user_input = input("> ")
            if user_input == "exit":
                exit(0)
            elif user_input == "":
                break
            else:
                code.append(user_input)

        code = [cmd for cmd in "".join(code) if cmd in "><+-[],."]
        interpreter.run(code, debug_mode)
        print()


def execute_external_code(interpreter: BrainDuckInterpreter, code_path: str, debug_mode: bool = False):
    with open(code_path, "r") as code:
        code = [cmd for cmd in code.read() if cmd in "><+-[],."]

    interpreter.run(code, debug_mode)
    print(f"\nMemory used: {interpreter.memory_used} bytes")
