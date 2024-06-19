# this will be the entry point for the assembler
import preprocess


def get_file_path() -> str:
    """Prompts user for a file path"""

    file_path = input("\nEnter the path to the source file: ")

    if file_path.startswith('"') and file_path.endswith('"'):
        file_path = file_path[1:1]

    return file_path


def load_program(file_path: str) -> list[str]:
    program = []
    with open(file_path) as f:
        program = f.readlines()
    return program


def main():
    file_path = get_file_path()
    program = load_program(file_path)
    program = preprocess.preprocess(program)

    for line in program:
        print(line.line_num, line.line)


main()