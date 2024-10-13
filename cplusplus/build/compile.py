"""
Compiles automatically the project

Use if you don't have Make installed
"""

import os


def run():
    executable_name: str = "brainduck_cpp"
    files_to_compile: list[str] = []

    for dirpath, _, filenames in os.walk("."):
        for filename in filenames:
            if filename.endswith(".cpp") and dirpath.startswith("..\\src"):
                files_to_compile.append(f"{dirpath.replace('\\', '/')}/{filename}")
    
    os.system(f"g++ -O3 {' '.join(files_to_compile)} -o {executable_name} -I ../include/ -static -static-libgcc -static-libstdc++")


if __name__ == "__main__":
    run()
