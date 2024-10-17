# Brainduck Projects
> “Sometimes the questions are complicated, and the answers are simple.” -Dr. Seuss

### **This README is not updated to the latest modifications**

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

The argument is optional, and if it is not included, the interpreter will be executed in "shell" mode.

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

## ASCII Table

| Decimal | Hex   | Octal | Binary       | Character | Description                    |
|---------|-------|-------|--------------|-----------|--------------------------------|
| 0       | 00    | 000   | 00000000     | NUL       | Null character                 |
| 1       | 01    | 001   | 00000001     | SOH       | Start of Heading               |
| 2       | 02    | 002   | 00000010     | STX       | Start of Text                  |
| 3       | 03    | 003   | 00000011     | ETX       | End of Text                    |
| 4       | 04    | 004   | 00000100     | EOT       | End of Transmission            |
| 5       | 05    | 005   | 00000101     | ENQ       | Enquiry                        |
| 6       | 06    | 006   | 00000110     | ACK       | Acknowledge                    |
| 7       | 07    | 007   | 00000111     | BEL       | Bell                           |
| 8       | 08    | 010   | 00001000     | BS        | Backspace                      |
| 9       | 09    | 011   | 00001001     | TAB       | Horizontal Tab                 |
| 10      | 0A    | 012   | 00001010     | LF        | Line Feed                      |
| 11      | 0B    | 013   | 00001011     | VT        | Vertical Tab                   |
| 12      | 0C    | 014   | 00001100     | FF        | Form Feed                      |
| 13      | 0D    | 015   | 00001101     | CR        | Carriage Return                |
| 14      | 0E    | 016   | 00001110     | SO        | Shift Out                      |
| 15      | 0F    | 017   | 00001111     | SI        | Shift In                       |
| 16      | 10    | 020   | 00010000     | DLE       | Data Link Escape               |
| 17      | 11    | 021   | 00010001     | DC1       | Device Control 1 (XON)         |
| 18      | 12    | 022   | 00010010     | DC2       | Device Control 2               |
| 19      | 13    | 023   | 00010011     | DC3       | Device Control 3 (XOFF)        |
| 20      | 14    | 024   | 00010100     | DC4       | Device Control 4               |
| 21      | 15    | 025   | 00010101     | NAK       | Negative Acknowledge           |
| 22      | 16    | 026   | 00010110     | SYN       | Synchronous Idle               |
| 23      | 17    | 027   | 00010111     | ETB       | End of Transmit Block          |
| 24      | 18    | 030   | 00011000     | CAN       | Cancel                         |
| 25      | 19    | 031   | 00011001     | EM        | End of Medium                  |
| 26      | 1A    | 032   | 00011010     | SUB       | Substitute                     |
| 27      | 1B    | 033   | 00011011     | ESC       | Escape                         |
| 28      | 1C    | 034   | 00011100     | FS        | File Separator                 |
| 29      | 1D    | 035   | 00011101     | GS        | Group Separator                |
| 30      | 1E    | 036   | 00011110     | RS        | Record Separator               |
| 31      | 1F    | 037   | 00011111     | US        | Unit Separator                 |
| 32      | 20    | 040   | 00100000     | (space)   | Space                          |
| 33      | 21    | 041   | 00100001     | !         | Exclamation mark               |
| 34      | 22    | 042   | 00100010     | "         | Double quote                   |
| 35      | 23    | 043   | 00100011     | #         | Number sign                    |
| 36      | 24    | 044   | 00100100     | $         | Dollar sign                    |
| 37      | 25    | 045   | 00100101     | %         | Percent sign                   |
| 38      | 26    | 046   | 00100110     | &         | Ampersand                      |
| 39      | 27    | 047   | 00100111     | '         | Single quote                   |
| 40      | 28    | 050   | 00101000     | (         | Left parenthesis               |
| 41      | 29    | 051   | 00101001     | )         | Right parenthesis              |
| 42      | 2A    | 052   | 00101010     | *         | Asterisk                       |
| 43      | 2B    | 053   | 00101011     | +         | Plus                           |
| 44      | 2C    | 054   | 00101100     | ,         | Comma                          |
| 45      | 2D    | 055   | 00101101     | -         | Hyphen-minus                   |
| 46      | 2E    | 056   | 00101110     | .         | Period                         |
| 47      | 2F    | 057   | 00101111     | /         | Slash                          |
| 48      | 30    | 060   | 00110000     | 0         | Digit 0                        |
| 49      | 31    | 061   | 00110001     | 1         | Digit 1                        |
| 50      | 32    | 062   | 00110010     | 2         | Digit 2                        |
| 51      | 33    | 063   | 00110011     | 3         | Digit 3                        |
| 52      | 34    | 064   | 00110100     | 4         | Digit 4                        |
| 53      | 35    | 065   | 00110101     | 5         | Digit 5                        |
| 54      | 36    | 066   | 00110110     | 6         | Digit 6                        |
| 55      | 37    | 067   | 00110111     | 7         | Digit 7                        |
| 56      | 38    | 070   | 00111000     | 8         | Digit 8                        |
| 57      | 39    | 071   | 00111001     | 9         | Digit 9                        |
| 58      | 3A    | 072   | 00111010     | :         | Colon                          |
| 59      | 3B    | 073   | 00111011     | ;         | Semicolon                      |
| 60      | 3C    | 074   | 00111100     | <         | Less-than sign                 |
| 61      | 3D    | 075   | 00111101     | =         | Equals sign                    |
| 62      | 3E    | 076   | 00111110     | >         | Greater-than sign              |
| 63      | 3F    | 077   | 00111111     | ?         | Question mark                  |
| 64      | 40    | 100   | 01000000     | @         | At sign                        |
| 65      | 41    | 101   | 01000001     | A         | Uppercase A                    |
| 66      | 42    | 102   | 01000010     | B         | Uppercase B                    |
| 67      | 43    | 103   | 01000011     | C         | Uppercase C                    |
| 68      | 44    | 104   | 01000100     | D         | Uppercase D                    |
| 69      | 45    | 105   | 01000101     | E         | Uppercase E                    |
| 70      | 46    | 106   | 01000110     | F         | Uppercase F                    |
| 71      | 47    | 107   | 01000111     | G         | Uppercase G                    |
| 72      | 48    | 110   | 01001000     | H         | Uppercase H                    |
| 73      | 49    | 111   | 01001001     | I         | Uppercase I                    |
| 74      | 4A    | 112   | 01001010     | J         | Uppercase J                    |
| 75      | 4B    | 113   | 01001011     | K         | Uppercase K                    |
| 76      | 4C    | 114   | 01001100     | L         | Uppercase L                    |
| 77      | 4D    | 115   | 01001101     | M         | Uppercase M                    |
| 78      | 4E    | 116   | 01001110     | N         | Uppercase N                    |
| 79      | 4F    | 117   | 01001111     | O         | Uppercase O                    |
| 80      | 50    | 120   | 01010000     | P         | Uppercase P                    |
| 81      | 51    | 121   | 01010001     | Q         | Uppercase Q                    |
| 82      | 52    | 122   | 01010010     | R         | Uppercase R                    |
| 83      | 53    | 123   | 01010011     | S         | Uppercase S                    |
| 84      | 54    | 124   | 01010100     | T         | Uppercase T                    |
| 85      | 55    | 125   | 01010101     | U         | Uppercase U                    |
| 86      | 56    | 126   | 01010110     | V         | Uppercase V                    |
| 87      | 57    | 127   | 01010111     | W         | Uppercase W                    |
| 88      | 58    | 130   | 01011000     | X         | Uppercase X                    |
| 89      | 59    | 131   | 01011001     | Y         | Uppercase Y                    |
| 90      | 5A    | 132   | 01011010     | Z         | Uppercase Z                    |
| 91      | 5B    | 133   | 01011011     | [         | Left square bracket            |
| 92      | 5C    | 134   | 01011100     | \         | Backslash                      |
| 93      | 5D    | 135   | 01011101     | ]         | Right square bracket           |
| 94      | 5E    | 136   | 01011110     | ^         | Caret                          |
| 95      | 5F    | 137   | 01011111     | _         | Underscore                     |
| 96      | 60    | 140   | 01100000     | `         | Grave accent                   |
| 97      | 61    | 141   | 01100001     | a         | Lowercase a                    |
| 98      | 62    | 142   | 01100010     | b         | Lowercase b                    |
| 99      | 63    | 143   | 01100011     | c         | Lowercase c                    |
| 100     | 64    | 144   | 01100100     | d         | Lowercase d                    |
| 101     | 65    | 145   | 01100101     | e         | Lowercase e                    |
| 102     | 66    | 146   | 01100110     | f         | Lowercase f                    |
| 103     | 67    | 147   | 01100111     | g         | Lowercase g                    |
| 104     | 68    | 150   | 01101000     | h         | Lowercase h                    |
| 105     | 69    | 151   | 01101001     | i         | Lowercase i                    |
| 106     | 6A    | 152   | 01101010     | j         | Lowercase j                    |
| 107     | 6B    | 153   | 01101011     | k         | Lowercase k                    |
| 108     | 6C    | 154   | 01101100     | l         | Lowercase l                    |
| 109     | 6D    | 155   | 01101101     | m         | Lowercase m                    |
| 110     | 6E    | 156   | 01101110     | n         | Lowercase n                    |
| 111     | 6F    | 157   | 01101111     | o         | Lowercase o                    |
| 112     | 70    | 160   | 01110000     | p         | Lowercase p                    |
| 113     | 71    | 161   | 01110001     | q         | Lowercase q                    |
| 114     | 72    | 162   | 01110010     | r         | Lowercase r                    |
| 115     | 73    | 163   | 01110011     | s         | Lowercase s                    |
| 116     | 74    | 164   | 01110100     | t         | Lowercase t                    |
| 117     | 75    | 165   | 01110101     | u         | Lowercase u                    |
| 118     | 76    | 166   | 01110110     | v         | Lowercase v                    |
| 119     | 77    | 167   | 01110111     | w         | Lowercase w                    |
| 120     | 78    | 170   | 01111000     | x         | Lowercase x                    |
| 121     | 79    | 171   | 01111001     | y         | Lowercase y                    |
| 122     | 7A    | 172   | 01111010     | z         | Lowercase z                    |
| 123     | 7B    | 173   | 01111011     | {         | Left curly bracket             |
| 124     | 7C    | 174   | 01111100     | \|         | Vertical bar                   |
| 125     | 7D    | 175   | 01111101     | }         | Right curly bracket            |
| 126     | 7E    | 176   | 01111110     | ~         | Tilde                          |
| 127     | 7F    | 177   | 01111111     | DEL       | Delete                         |

## License

Licensed under the MIT license. See [LICENSE](LICENSE).
