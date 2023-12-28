import sys
from operator import countOf


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
        self.user_input: str | None
        self.debug_mode: bool
        self.brackets_pos: list[int, int]

    def run(self, code: list[str], debug_mode: bool = False):
        """ Execute a Brainfuck code.
        :param code: A list of instruction in Brainfuck using the original brainfuck sintaxe and rules.
        :param debug_mode: If it's True, at each command will be printed the current command, the current pointer location and the value of the memory that the pointer is pointing. The output will also be changed, outputing the cell value instead of his ASCII correspondent.
        """

        self.memory = [0] * self.memory_size
        self.code = code
        self.pointer = 0
        self.current_cmd = 0
        self.user_input = None
        self.debug_mode = debug_mode
        self.brackets_pos = self.__get_brackets_pos()

        commands = {
            ">": self.__right,
            "<": self.__left,
            "+": self.__increase,
            "-": self.__decrease,
            "[": self.__start_loop,
            "]": self.__end_loop,
            ",": self.__input,
            ".": self.__output
        }

        if debug_mode is True:
            while self.current_cmd < len(self.code):
                print(f"{self.code[self.current_cmd]} - c{self.pointer}: {self.memory[self.pointer]}")
                commands[self.code[self.current_cmd]]()
        else:
            while self.current_cmd < len(self.code):
                commands[self.code[self.current_cmd]]()

    # Simple commmands
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

    # Advanced commands
    def __start_loop(self):
        brackets_index = self.brackets_pos[self.current_cmd]

        # If the current cell isn't zero the looping will start, if it's zero jump to the end of the loop
        if self.memory[self.pointer] != 0:
            self.current_cmd += 1
        else:
            self.current_cmd = brackets_index + 1

    def __end_loop(self):
        brackets_index = self.brackets_pos[self.current_cmd]

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

    def __output(self):
        if self.debug_mode is True:
            print(self.memory[self.pointer], end=" ")
        else:
            # Printing the value of the memory cell
            # self.memory[self.pointer] (cell value) % 255 guarantees that the output will be an ascii character
            print(chr(self.memory[self.pointer] % 255), end="")

        self.current_cmd += 1

    def __get_brackets_pos(self):
        """ Gets the position of the corresponding brackets. """
        brac_dict: dict[int, str | int]
        brac_list: list[int]
        close_brac_list: list[int] = list()
        open_brac_list: list[int]

        # Getting the position and the character for each item in the cmds list, if it's a bracket
        brac_dict = {pos: char for pos, char in enumerate(self.code) if char in "[]"}

        # If some brackets aren't closed
        if countOf(brac_dict.values(), "[") != countOf(brac_dict.values(), "]"):
            print(f"Error: Some pair of brackets is not closed.")
            sys.exit(0)

        # This part is a bit complex
        # First we need to get a copy of the keys (brackets positions)
        # Second we get a list of the open brackets position and invert it
        # Why? Because we will get the pairs from inside out, and then remove the inner pairs from the copy of keys

        brac_list = list(brac_dict.keys())  # Copy of the keys
        open_brac_list = [pos for pos, char in brac_dict.items() if char == "["][::-1]  # Open brackets position (inverted)

        for open_brac_pos in open_brac_list:
            # The position of the close bracket of the inner pair of brackets will always be one index more than the open bracket
            close_brac_pos = brac_list[brac_list.index(open_brac_pos) + 1]
            # Append it to the list of close brackets
            close_brac_list.append(close_brac_pos)

            # And then remote the pair from the list
            brac_list.remove(close_brac_pos)
            brac_list.remove(open_brac_pos)

        # Zipping the open brackets list and the close brackets list
        brac_dict = dict(zip(open_brac_list, close_brac_list))

        # Adding the inverse values, k:v to v:k at the end of the dict
        brac_dict = {**brac_dict, **{v: k for k, v in brac_dict.items()}}

        return brac_dict

    @property
    def memory_used(self):
        """ Returns the memory used by the interpreter.
        :return: The sum of the sys.getsizeof() of each attribute used in the Brainfuck interpreter (memory size, memory list/grid, code, cell size, pointer loc., current cmd, total cmds and user input).
        """

        memory_used = (sys.getsizeof(self.memory_size)
                       + sys.getsizeof(self.memory)
                       + sys.getsizeof(self.code)
                       + sys.getsizeof(self.cell_size)
                       + sys.getsizeof(self.pointer)
                       + sys.getsizeof(self.current_cmd)
                       + sys.getsizeof(self.user_input)
                       + sys.getsizeof(self.brackets_pos))

        return memory_used
