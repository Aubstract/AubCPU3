# this will be the entry point for the assembler
from datetime import datetime
import argparse
import mcschematic as mcschem

import dictionaries as dicts
import link
import preprocess as pre
import assemble
import postprocess as post


def get_file_path() -> str:
    """Prompts user for a file path"""
    file_path = input("\nEnter the path to the source file: ")

    if file_path.startswith('"') and file_path.endswith('"'):
        file_path = file_path[1:1]

    return file_path


def load_program(file_path: str) -> list[str]:
    """Reads the source file into a string"""
    program = []
    with open(file_path) as f:
        program = f.readlines()
    return program


def write_bin_file(path: str, program: list[int]) -> None:
    """Writes the binary instruction list to a file"""
    with open(f"{path}.bin", "wb") as f:
        for value in program:
            # Convert integer to 2-byte bytearray with little-endian byte order
            bytes_data = value.to_bytes(2, byteorder="little")
            f.write(bytes_data)


def generate_signal_strengths(lower_byte1, upper_byte1, lower_byte2, upper_byte2) -> list[int]:
    """Takes 4 bytes and converts them to the corresponding set of 8 signal strength values for the barrels"""
    bitmask = 0x80
    return_list = []
    for index in range(7, -1, -1):
        ss = 0
        if lower_byte1 & bitmask:
            ss |= 1
        if lower_byte2 & bitmask:
            ss |= 2
        if upper_byte1 & bitmask:
            ss |= 4
        if upper_byte2 & bitmask:
            ss |= 8
        return_list.append(ss)
        bitmask >>= 1

    return return_list


def write_schem_file(path: str, file_name: str, program: list[int]) -> None:
    """Constructs a .schem file out of the binary instruction list.\n
    - program is a list of 16-bit integers"""

    schem = mcschem.MCSchematic()

    # Offset of schem origin from player's feet
    origin_x = 1
    origin_y = -2
    origin_z = 1

    # Make sure that the program is always 256 instructions long (fills empty space with "halt" instructions)
    if len(program) != 256:
        program.extend([0] * (256 - len(program)))

    for index, (instr1, instr2) in enumerate(zip(program[::2], program[1::2])):
        # index starts at 0 and counts up by 1
        coord_x = origin_x + ((index // 8) * 2) + (index // 16)
        coord_y = origin_y + (index // 16) % 2
        coord_z = origin_z + (index % 8) * 2

        lower_byte1 = instr1 & 0xFF
        upper_byte1 = instr1 >> 8
        lower_byte2 = instr2 & 0xFF
        upper_byte2 = instr2 >> 8

        signal_strengths = generate_signal_strengths(lower_byte1, upper_byte1, lower_byte2, upper_byte2)

        for height, ss in enumerate(signal_strengths):
            schem.setBlock((coord_x, coord_y - (2 * height), coord_z), mcschem.BlockDataDB.BARREL.fromSS(ss))

    # Construct the sign's NBT data
    now = datetime.now()
    line1 = file_name
    line2 = "Assembled:"
    line3 = now.strftime("%Y-%m-%d")
    line4 = f"""{now.strftime("%H:%M:%S")}"""
    block_data = ("""minecraft:birch_sign[rotation=8,waterlogged=false]"""
                  + """{GlowingText: 0b, Color: "black", Text4: '{"text":" """
                  + line4 + """ "}', Text3: '{"text":" """
                  + line3 + """ "}', Text2: '{"text":" """
                  + line2 + """ "}', Text1: '{"text":" """
                  + line1 + """ "}'}""")
    schem.setBlock((0, 0, 0), block_data)

    schem.save(path, file_name, mcschem.Version.JE_1_18_2)


def main():
    msg = "Assemble a file"
    parser = argparse.ArgumentParser(description=msg)
    # parser.add_argument("-src", "--source", help="path to source file")
    parser.add_argument("-bin", "--binary", action="store_true", help="output a binary file")
    parser.add_argument("-schem", "--schematic", action="store_true", help="output a schematic file")
    parser.add_argument("-odir", "--outputDirPath", help="Path to the output directory")
    args = parser.parse_args()
    args.outputDirPath = args.outputDirPath.replace('"', '')

    # Get source file
    dicts.src_file_path = get_file_path()
    program = load_program(dicts.src_file_path)

    # Pre-process
    program = link.link(program)
    program = pre.preprocess(program)

    # Assemble
    program = assemble.assemble(program)

    # Post process
    post.postprocess(program)
    
    # Build output file path
    file_name = dicts.src_file_path.split("\\")[-1]
    file_name = file_name[:file_name.index('.')]

    # Write to output file (bin or schem depending on cmdline args)
    if args.binary:
        write_bin_file(args.outputDirPath + "\\" + file_name, program)
    elif args.schematic:
        write_schem_file(args.outputDirPath, file_name, program)


if __name__ == "__main__":
    main()
