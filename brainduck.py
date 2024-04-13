from modules.interpreter import BrainduckInterpreter
from modules.compiler import BrainduckCompiler
from modules.execution_functions import compile_external_code
from modules.execution_functions import interpret_external_code
from modules.execution_functions import execute_shell
from sys import argv, exit

#
VALID_OPTIONS: tuple[str, ...] = "--debug", "--d", "--compile", "--c"


def run(code_path: str, debug_mode: bool, compile_mode: bool):
    if compile_mode:
        compiler = BrainduckCompiler()
        compile_external_code(compiler, code_path, debug_mode)

    else:
        interpreter = BrainduckInterpreter()

        if code_path:
            interpret_external_code(interpreter, code_path, debug_mode)
        else:
            execute_shell(interpreter, debug_mode)


if __name__ == '__main__':
    #
    path: str = ""
    debug: bool = False
    compile_: bool = False

    #
    options_selected = [
        option for option in argv[1:]
        if option.startswith("--")
    ]

    args = [
        arg for arg in argv[1:]
        if not arg.startswith("-")
    ]

    # Options
    # Testing if some option isn't valid
    for option in options_selected:
        if option not in VALID_OPTIONS:
            print(f"Error: Invalid option '{option}'")
            exit(0)

    # Setting the configs based on the selected options
    debug = ("--debug" in options_selected or
             "--d" in options_selected)

    compile_ = ("--compile" in options_selected or
                "--c" in options_selected)

    # Arguments
    # Getting the path, if it has one
    if len(args) > 0:
        path = args[0]
    # If it doesn't, but is defined to compile the code, it will not run
    elif compile_ is True:
        print("Error: The code can only be compiled if it has an origin file.")
        exit(0)

    #
    run(path, debug, compile_)
