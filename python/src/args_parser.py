from sys import argv

def option_pos(option_name: str):
    long_version = f"--{option_name}"
    short_version = f"-{option_name[0]}"
    
    options_list = []

    for arg in argv:
        if arg.startswith('-'):
            options_list.append(arg)

    try:
        long_pos = options_list.index(long_version)
    except ValueError:
        long_pos = -1
    
    try:
        short_pos = options_list.index(short_version)
    except ValueError:
        short_pos = -1
    
    return long_pos if long_pos != -1 else short_pos


def has_invalid_option(correct_list: list[str]):
    current_list = []

    for arg in argv:
        if arg.startswith('-'):
            current_list.append(arg)

    for current_option in current_list:
        equal_to_at_least_one = False

        for correct_option in correct_list:
            long_version = f"--{correct_option}"
            short_version = f"-{correct_option[0]}"

            if current_option == long_version or current_option == short_version:
                equal_to_at_least_one = True
            
        if not equal_to_at_least_one:
            return current_option
    
    return False
