""" Credits to Truttle1, creator of the code in advanced.bf
Truttle1's YouTube channel: https://www.youtube.com/@Truttle1\n
Video of the code: https://www.youtube.com/watch?v=Cg98wh2-lOw\n
Game's Source: https://pastebin.com/1E5US36E
"""


from modules.brainduck_interpreter import BrainDuckInterpreter


if __name__ == "__main__":
    interpreter = BrainDuckInterpreter()

    with open("brainduck_codes/advanced.bf", "r") as code:
        code = [cmd for cmd in code.read() if cmd in "><+-[],."]

    interpreter.run(code, debug=False)
    print(f"\nMemory used: {interpreter.memory_used} bytes")
