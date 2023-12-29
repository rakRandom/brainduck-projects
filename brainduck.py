from modules.brainduck_interpreter import BrainDuckInterpreter
from modules.execution_functions import execute_shell
from modules.execution_functions import execute_external_code
from sys import argv, exit


def run(code_path: str, debug_mode: bool):
    interpreter = BrainDuckInterpreter()

    if code_path:
        execute_external_code(interpreter, code_path, debug_mode)
    else:
        execute_shell(interpreter, debug_mode)


if __name__ == '__main__':
    path: str = ""
    debug: bool = False

    options = [option for option in argv[1:] if option.startswith("--")]
    args = [arg for arg in argv[1:] if not arg.startswith("-")]

    # Options
    if len(options) > 0:
        if options[0] == "--debug":
            debug = True
        else:
            print("Invalid option, do you mean \"--debug\"?")
            exit(0)
    # Arguments
    if len(args) > 0:
        path = args[0]

    run(path, debug)
