from os import system
from os import path
from os import remove


class BrainduckCompiler:
    def __init__(self):
        self.c_code: list[str] = [
            "#include <stdio.h>",
            "int main() { ",
            "unsigned char d[65535];",
            "unsigned short p = 0;",
            "if (d == NULL) { return 1; }"
        ]

    def run(self, bf_code: list[str], debug_mode=False) -> int:
        for cmd in bf_code:
            match cmd:
                case "+":
                    self.c_code.append("d[p]++;")
                case "-":
                    self.c_code.append("d[p]--;")
                case ">":
                    self.c_code.append("p++;")
                case "<":
                    self.c_code.append("p--;")
                case "[":
                    self.c_code.append("while (d[p] != 0) {")
                case "]":
                    self.c_code.append("}")
                case ".":
                    self.c_code.append("putchar(d[p]);")
                case ",":
                    self.c_code.append("d[p] = getchar();")

        #
        self.c_code.append("return 0;\n}")
        self.c_code = '\n'.join(self.c_code)

        #
        with open("to_compile.c", 'w') as file:
            file.write(self.c_code)

        #
        error = system("gcc -O3 to_compile.c -o compiled -static -static-libgcc")

        #
        if debug_mode is False and path.exists("to_compile.c"):
            remove("to_compile.c")

        return error
