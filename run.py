from modules.brainduck_interpreter import BrainDuckInterpreter
from modules.execution_functions import execute_shell
from modules.execution_functions import execute_external_code


if __name__ == '__main__':
    interpreter = BrainDuckInterpreter()

    # Put the path to the .bf file here
    code_path: str = ""

    if code_path:
        execute_external_code(interpreter, code_path)
    else:
        execute_shell(interpreter)
