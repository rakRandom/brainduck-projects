from interpreter import BrainduckInterpreter
from compiler import BrainduckCompiler
from sys import exit

BRAINFUCK_COMMANDS = "><+-[],."


def execute_shell(interpreter: BrainduckInterpreter, debug_mode: bool = False):
    code: list[str] | str
    user_input: str

    print("Brainfuck Interpreter Shell (BIS) - type \"exit\" to exit")
    while True:
        code = list()

        while True:
            user_input = input("> ")
            if user_input == "exit":
                exit(0)
            elif user_input == "":
                break
            else:
                code.append(user_input)

        code = [cmd for cmd in "".join(code) if cmd in BRAINFUCK_COMMANDS]
        interpreter.run(code, debug_mode)
        print()


def interpret_external_code(interpreter: BrainduckInterpreter, code_path: str, debug_mode: bool = False):
    with open(code_path, "r") as code:
        code = [cmd for cmd in code.read() if cmd in BRAINFUCK_COMMANDS]

    interpreter.run(code, debug_mode)
    print(f"\nMemory used: {interpreter.memory_used} bytes")


def compile_external_code(compiler: BrainduckCompiler, code_path: str, debug_mode: bool = False):
    with open(code_path, "r") as code:
        code = [cmd for cmd in code.read() if cmd in BRAINFUCK_COMMANDS]

    error = compiler.run(code, debug_mode)

    if error:
        print(f"An error occurred during compilation: Error n.º {error}.")
    else:
        print(f"Compilation done successfully.")
