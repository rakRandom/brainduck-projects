from modules.brainduck_interpreter import BrainDuckInterpreter
from modules.execution_functions import execute_shell
from modules.execution_functions import execute_external_code
from sys import argv


def run(path: str = ""):
    interpreter = BrainDuckInterpreter()

    if path:
        execute_external_code(interpreter, path)
    else:
        execute_shell(interpreter)


if __name__ == '__main__':
    code_path: str = ""
    if len(argv) > 1:
        code_path = str(argv[1])
    run(code_path)
