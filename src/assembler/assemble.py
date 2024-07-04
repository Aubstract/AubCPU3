import dictionaries as dicts


def replace_opcodes(program: list[object]):
    for line_object in program:
        tokens = line_object.line.split()
        tokens[0] = dicts.opcodes[tokens[0]]
        line_object.line = ' '.join(tokens)


def construct_binary_list(program: list[object]) -> list[int]:
    bin_program = []

    for line_object in program:
        instr_word = 0
        tokens = line_object.line.split()
        opcode = tokens[0]

        # All instructions write the opcode to the lowest bits
        opcode = dicts.opcodes[opcode]
        instr_word |= int(opcode)

        for index, token in enumerate(tokens):
            if index > 0:
                tokens[index] = int(token)

        # Write the operands to the instruction word
        # "hlt" has no operands
        if tokens[0] == "jin":
            instr_word |= tokens[1] << 8
        elif tokens[0] == "cmp":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "add":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "sub":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "and":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "orr":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "xor":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "lsh":
            instr_word |= tokens[1] << 4
        elif tokens[0] == "rsh":
            instr_word |= tokens[1] << 4
        elif tokens[0] == "inc":
            instr_word |= tokens[1] << 4
        elif tokens[0] == "dec":
            instr_word |= tokens[1] << 4
        elif tokens[0] == "lod":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "ldi":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "sto":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] == "cpr":
            instr_word |= tokens[1] << 4
            instr_word |= tokens[2] << 8
        elif tokens[0] != "hlt":
            print("SOMETHING WENT WRONG IN ASSEMBLE()")
            quit()

        bin_program.append(instr_word)

    return bin_program


def assemble(program: list[object]) -> list[int]:
    binary = construct_binary_list(program)
    return binary
