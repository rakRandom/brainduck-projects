# Brainduck, a Brainfuck interpreter (and compiler)
> “Sometimes the questions are complicated, and the answers are simple.” -Dr. Seuss

<br>

## Description
This project is based on the esoteric Brainfuck language, known for being one of the most difficult to understand and 
use, and that's why I made this interpreter in a dynamic and high-level language, Python.

<br>

## How to use

### Running in the IDE
In the directories of this project there is the test folder, which contains 4 tests, and the ```run.py``` file. The files in the 
test folder work with an external Brainfuck file, while the run file can also work by creating a "shell", like in Python.

After executing the run file in shell mode, the user can type the code and separate it into lines, and as long as the 
user does not type an empty line, the program will continue to recive the user input.

To disable the shell and run an external file, you need to change the value of the ```code_path``` variable to the path of 
your file, and then your external Brainfuck code will run perfectly.

### Running in the command line interface (CLI)
Alternatively, you can use it through the CLI, which is very simple. The interpreter has 2 call parameters, one being an 
option and the other an argument.
```
python brainduck.py --debug [file path]
```
> [file path] is optional

The option causes the code in Brainfuck to run in debug mode (which will be explained later), and the argument, as the 
name suggests, is the path to the Brainfuck file.

The argument is optional, and if it is not included, the interpreter will be executed in 'shell' mode.

<br>

## How the interpreter works

### The BrainDuckInterpreter class
The interpreter is a class that works using the original Brainfuck syntax and rules. The remaining Python files take the 
Brainfuck file, read it, separate the text into a list of characters, and filter out those that are not Brainfuck commands. 
After that, the command list is sent to an object of the ```BrainDuckInterpreter``` class as a parameter of the run function, 
and this creates the memory spaces, defined when creating the object, and other necessary variables.

```
The list of Brainfuck commands:
 + - Increase the value in the cell by 1
 - - Decrease the value in the cell by 1
 > - Move the memory pointer to the right
 < - Move the memory pointer to the left
 [ - Start a conditional loop (oversimplified)
 ] - End a conditional loop (oversimplified)
 , - Get the user input and store in the curent memory cell
 . - Print the current memory cell value in ASCII table
```

### How the debug mode works

With debug mode activated, each instruction is shown in the CLI the command used, the current cell and the value of the 
current cell. Furthermore, when the show cell value command is used, the value is shown as a number, instead of the ASCII (American Standart Code for Information Interchange) character.


### How the compile mode works

Command
```
python brainduck.py --compile [file path]
```
> [file path] is required

### Creating an object from BrainDuckInterpreter

The ```BrainDuckInterpreter``` ```__init__()``` method takes 2 arguments, one is ```memory_bits``` and the other is ```cell_bits```.

As the name suggest, the first defines how many bits the memory will have, consequently defining how many cells there 
will be (e.g.: If ```memory_bits``` has the value of 15, there will be 32.768 cells).

The ```cell_bits``` defines how many bits will have each cell (e.g.: If ```cell_bits``` has the value of 8, the maximum 
value of the cells will be 255).

### Dependencies

The ```BrainDuckInterpreter``` class is independent of the rest of the project, and can be used in other projects just by 
reusing the file, its only dependencies being the command prompt, if a new project wants to use a custom interface it 
will have to change the interpreter code a little.

<br>

## C++ Version

 To compile the C++ version, simply run the make.bat file at the command prompt.
```
C:\brainduck-interpreter\cpp_ver>make
```
 And then you can run the code with the parameter being the .bf file you want to run.
```
C:\brainduck-interpreter\cpp_ver>brainfuck test_codes/mandelbrot.bf
```
 The code uses stack/compile allocated memory to read the brainfuck and execute it, so there is a limit of 65,536 (or 2 to the power of 16) characters. This version **does not** contain the debug option, other than that it executes the code in a similar way.

<br>

## License

Licensed under the MIT license. See [LICENSE](LICENSE).
