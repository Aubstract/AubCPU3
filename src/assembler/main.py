# this will be the entry point for the assembler
import dictionaries as dict
import preprocess
import link
import assemble


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
    dict.src_file_path = get_file_path()
    program = load_program(dict.src_file_path)
    program = link.link(program)

    program = preprocess.preprocess(program)
    program = assemble.assemble(program)

    file_name = dict.src_file_path.split("\\")[-1]
    file_name = file_name[:file_name.index('.')]

    print(dict.jump_labels)
    print(dict.var_labels)

    with open(f"bin_files/{file_name}.bin", "wb") as f:
        for value in program:
            # Convert integer to 2-byte bytearray with little-endian byte order
            bytes_data = value.to_bytes(2, byteorder="little")
            f.write(bytes_data)


if __name__ == "__main__":
    main()