import sys


class BrainDuckInterpreter:
    def __init__(self, memory_bits=15, cell_bits=8):
        """ A Brainfuck Interpreter.
        Use the 'run()' method to run some Brainfuck code.

        :param memory_bits: Number of bits that the pointer will have, that is, how many cells will be created. If the pointer is 8 bits, then he value will be 255 at maximum, so there will be 256 cells.
        :param cell_bits: Number of bits that each cell will have. If each cell has 8 bits, then the maximum value will be 255 for each cell.
        """

        self.memory_size = 2 ** memory_bits  # Numbers of bits that the pointer has
        self.memory: list[int]
        self.code: list[str]
        self.cell_size: int = 2 ** cell_bits - 1  # Number of bits that each cell has
        self.pointer: int = 0
        self.current_cmd: int = 0
        self.total_cmds: int
        self.user_input: str | None

    def run(self, code: list[str], debug: bool = False):
        """ Execute a Brainfuck code.

        :param code: A list of instruction in Brainfuck using the original brainfuck sintaxe and rules.
        :param debug: If it's True, at each command will be printed the current command, the current pointer location and the value of the memory that the pointer is pointing. The output will also be changed, outputing the cell value instead of his ASCII correspondent.
        """

        self.memory = [0 for _ in range(self.memory_size)]
        self.code = code
        self.pointer = 0
        self.current_cmd = 0
        self.total_cmds = len(self.code)
        self.user_input = None

        while self.current_cmd < self.total_cmds:
            if debug is True:
                print(f"{self.code[self.current_cmd]} - c{self.pointer}: {self.memory[self.pointer]}")
            match self.code[self.current_cmd]:
                case '>': self.__right()
                case '<': self.__left()
                case '+': self.__increase()
                case '-': self.__decrease()
                case '[': self.__start_loop()
                case ']': self.__end_loop()
                case ',': self.__input()
                case '.': self.__output(debug)

    def __right(self):
        # If the pointer is in the last cell, go back to the first one
        # If it isn't, simply add one
        if self.pointer + 1 == self.memory_size:
            self.pointer = 0
        else:
            self.pointer += 1
        self.current_cmd += 1

    def __left(self):
        # If the pointer is in the first cell, go foward to the last one
        # If it isn't, simply subtract one
        if self.pointer == 0:
            self.pointer = self.memory_size - 1
        else:
            self.pointer -= 1
        self.current_cmd += 1

    def __increase(self):
        # If the cell has the max value, then it will be reseted to 0
        # If the cell hasn't the max value, then just add one
        if self.memory[self.pointer] == self.cell_size:
            self.memory[self.pointer] = 0
        else:
            self.memory[self.pointer] += 1
        self.current_cmd += 1

    def __decrease(self):
        # If the cell has value equal to 0, then it will be the max value
        # If the cell hasn't a value equal to 0, then just subtract one
        if self.memory[self.pointer] == 0:
            self.memory[self.pointer] = self.cell_size
        else:
            self.memory[self.pointer] -= 1
        self.current_cmd += 1

    def __start_loop(self):
        barrier_count: int = 0
        brackets_index: int = -1

        # Getting close brackets index, considering looping nests
        # If the brackets aren't closed, the index will be -1
        for i, e in enumerate(self.code[self.current_cmd+1:]):
            if e == '[':
                barrier_count += 1
            elif e == ']':
                if barrier_count == 0:
                    brackets_index = self.current_cmd + i + 1
                    break
                else:
                    barrier_count -= 1

        # If the brackets index is -1, in other words, if the brackets aren't closed, the program will be closed
        if brackets_index == -1:
            print(f"Error: The brackets in the position {self.current_cmd} are not closed.")
            sys.exit(0)

        # If the current cell isn't zero the looping will start, if it's zero jump to the end of the loop
        if self.memory[self.pointer] != 0:
            self.current_cmd += 1
        else:
            self.current_cmd = brackets_index + 1

    def __end_loop(self):
        barrier_count: int = 0
        brackets_index: int = -1

        # Getting open brackets index, considering looping nests
        # If it isn't an open bracket, the index will be -1
        # Because of the inverse array, the index of the brackets is self.current_cmd - i - 1
        for i, e in enumerate(self.code[self.current_cmd-1::-1]):
            if e == ']':
                barrier_count += 1
            elif e == '[':
                if barrier_count == 0:
                    brackets_index = self.current_cmd - i - 1
                    break
                else:
                    barrier_count -= 1

        # If the brackets index is -1, in other words, if there isn't an open bracket, the program will be closed
        if brackets_index == -1:
            print(f"Error: The brackets in the position {self.current_cmd} are not closed.")
            sys.exit(0)

        # If the current cell isn't zero the looping will start again, if it's zero then move to the next command
        if self.memory[self.pointer] == 0:
            self.current_cmd += 1
        else:
            self.current_cmd = brackets_index + 1

    def __input(self):
        # The user input is stored in a sort of 'buffer', that will be removed one by one until only has the null character
        # When this happens, the user will need to input data again
        if self.user_input is None:
            # self.user_input = input() + chr(0)
            # sys.stdin.readline()[:-1] will get all the characters typed, except the line breaker, and chr(0) is to get the null character
            self.user_input = sys.stdin.readline()[:-1] + chr(0)

        # If the user did not enter anything, this will be skiped
        if self.user_input:
            # The memory pointer will recive the value of the first character in the buffer
            self.memory[self.pointer] = ord(self.user_input[0])
            # And the buffer will lose the first character
            self.user_input = self.user_input[1:] if len(self.user_input) > 1 else None

        self.current_cmd += 1

    def __output(self, debug):
        if debug is True:
            print(self.memory[self.pointer], end=" ")
        else:
            # Printing the value of the memory cell
            # self.memory[self.pointer] (cell value) % 255 guarantees that the output will be an ascii character
            print(chr(self.memory[self.pointer] % 255), end="")

        self.current_cmd += 1

    def memory_usage(self):
        """ Returns the memory used by the interpreter.

        :return: The sum of the sys.getsizeof() of each attribute used in the Brainfuck interpreter (memory size, memory list/grid, code, cell size, pointer loc., current cmd, total cmds and user input).
        """

        memory_used = (sys.getsizeof(self.memory_size)
                       + sys.getsizeof(self.memory)
                       + sys.getsizeof(self.code)
                       + sys.getsizeof(self.cell_size)
                       + sys.getsizeof(self.pointer)
                       + sys.getsizeof(self.current_cmd)
                       + sys.getsizeof(self.total_cmds)
                       + sys.getsizeof(self.user_input))

        return memory_used
