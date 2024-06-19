import dictionaries as dict


class Line:
    def __init__(self, line_arg: str, line_num_arg: int):
        self.line = line_arg
        self.line_num = line_num_arg


def construct_lines(code: list[str]) -> list[object]:
    """Takes a list of strings and creates a list of objects, each with two attributes:\n
       - The line of code (str)\n
       - The line number (int)\n
       This allows the debugger to specify the line number in an error message"""
    lines = []

    for line_num, line in enumerate(code):
        lines.append(Line(line, line_num + 1))

    return lines


def remove_whitespace(program: list[object]):
    """Eliminates comments, empty lines, tabs, double spaces, etc"""

    for line_num, line_object in reversed(list(enumerate(program))):

        line = line_object.line

        line = line.replace("\t", "")
        while "  " in line:
            line = line.replace("  ", " ")

        if "//" in line:
            line = line[: line.index("//")]
        if line.startswith(" "):
            line = line[1:]
        if line.endswith(" "):
            line = line[:-1]
        if "\n" in line:
            line = line[: line.index("\n")]

        if len(line) == 0:
            program.pop(line_num)
        else:
            program[line_num].line = line


def remove_labels(program: list[object]):
    for index, line_object in reversed(list(enumerate(program))):
        line = line_object.line
        if ':' in line:
            program.pop(index)


def define_labels(program: list[object]):
    line_index = 0
    for line_object in program:
        line: str = line_object.line
        line_num: int = line_object.line_num

        if ':' in line:
            if line.endswith(':'):
                dict.jump_labels[line[:-1]] = str(line_index)
                line_index -= 1
            else:
                line_index -= 1
        line_index += 1
    remove_labels(program)


def preprocess(program: list[str]) -> list[object]:
    new_program = construct_lines(program)
    remove_whitespace(new_program)

    return new_program
