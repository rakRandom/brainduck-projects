# Brainduck, a Brainfuck interpreter
> “Sometimes the questions are complicated, and the answers are simple.” -Dr. Seuss

This project is based on the esoteric Brainfuck language, known for being one of the most difficult to understand and 
use, and that's why I made this interpreter in a dynamic and high-level language, Python.

## How to use
In the directories of this project there is the test folder, which contains 4 tests, and the run. The files in the test 
folder work with an external .bf file, while the run file can also work by creating a "shell", like in Python. 
To disable the shell and run an external file, you need to change the value of the "code_path" variable to the path of 
your file.

After executing the run file in shell mode, the user can type the code and separate it into lines, and as long as the 
user does not type an empty line, the program will continue to recive the user input.

## How the interpreter works
The interpreter is a class that works using the original Brainfuck syntax and rules. The remaining Python files take the 
.bf file, read it, separate the text into a list of characters, and filter out those that are not Brainfuck commands. 
After that, the command list is sent to an object of the BrainDuckInterpreter class as a parameter of the run function, 
and this creates the memory spaces, defined when creating the object, and other necessary variables.

> Brainfuck commands: > < [ ] , .

The BrainDuckInterpreter class is independent of the rest of the project, and can be used in other projects just by 
copying and pasting the file, its only dependencies being the command prompt, if a new project wants to use a custom 
interface it will have to change the interpreter code a little.
