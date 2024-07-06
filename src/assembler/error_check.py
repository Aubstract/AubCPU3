import Line
import dictionaries as dicts


def throw_error(err_msg: str) -> None:
    print("\n####################################################")
    print("ERROR:")
    print(err_msg)
    print("####################################################\n")
    quit()


def check_expression(line_object: object) -> None:
    expression = line_object.line[line_object.line.index(':') + 1:]
    tokens = expression.split()

    for token in tokens:
        token_valid = False

        if token.isnumeric():
            token_valid = True
        elif token in dicts.jump_labels:
            token_valid = True
        elif token in dicts.var_labels:
            token_valid = True
        elif token == '.':
            token_valid = True
        elif token in ['+', '-', '*', '/']:
            token_valid = True

        if not token_valid:
            throw_error(f"Invalid expression '{expression}' on line {line_object.line_num}:\n"
                        f"{line_object.line}")


def check_if_all_labels_are_defined(program: list[object]) -> None:
    for line_object in program:
        tokens = line_object.line.split()
        for token in tokens[1:]:
            token_valid = False

            if token.isnumeric():
                token_valid = True
            elif token in dicts.var_labels:
                token_valid = True
            elif token in dicts.jump_labels:
                token_valid = True
            elif token in dicts.register_names:
                token_valid = True
            elif token in dicts.alt_register_names:
                token_valid = True

            if not token_valid:
                throw_error(f"Undefined label '{token}' on line {line_object.line_num}:\n"
                            f"{line_object.line}")


def check_opcodes_and_operands(program: list[object]) -> None:
    for line_object in program:
        tokens = line_object.line.split()

        # Check for valid opcode
        opcode = tokens[0]
        if opcode not in dicts.opcodes:
            throw_error(f"Unknown opcode '{opcode}' in line {line_object.line_num}:\n"
                        f"{line_object.line}")

        # Check number of operands
        invalid_num_operands = (f"Invalid number of operands in line {line_object.line_num}:\n"
                                f"{line_object.line}")
        if opcode in ["hlt"]:
            if len(tokens) != 1:
                throw_error(invalid_num_operands)
        elif opcode in ["jin", "lsh", "rsh", "inc", "dec"]:
            if len(tokens) != 2:
                throw_error(invalid_num_operands)
        elif opcode in ["cmp", "add", "sub", "and", "orr", "xor", "lod", "ldi", "sto", "cpr"]:
            if len(tokens) != 3:
                throw_error(invalid_num_operands)

        # Check that operands are valid register addresses
        min_reg_addr = 0
        max_reg_addr = 15
        if opcode in dicts.opcodes and opcode not in ["hlt", "jin"]:
            valid_addr = True
            if tokens[1].isnumeric():
                addr = int(tokens[1])
                if addr < min_reg_addr or addr > max_reg_addr:
                    valid_addr = False

            if not valid_addr:
                throw_error(f"Invalid register address '{tokens[1]}' in line {line_object.line_num}:\n"
                            f"{line_object.line}")
        # TODO: handle the other operands and their valid ranges

        # Check if values are in range
        min_val = -128
        max_val = 255
        for token in tokens[1:]:

            if token.isnumeric():
                value = int(token)
                if value < min_val or value > max_val:
                    throw_error(f"Value '{value}' in  line {line_object.line_num} is out of range [{min_val},{max_val}]:\n"
                                f"{line_object.line}")
            elif token in dicts.var_labels:
                value = int(dicts.var_labels[token])
                if value < min_val or value > max_val:
                    throw_error(f"Value '{value}' in  line {line_object.line_num} is out of range [{min_val},{max_val}]:\n"
                                f"{line_object.line}")
            elif token in dicts.jump_labels:
                value = int(dicts.jump_labels[token])
                if value < min_val or value > max_val:
                    throw_error(f"Value '{value}' in  line {line_object.line_num} is out of range [{min_val},{max_val}]:\n"
                                f"{line_object.line}")


def check_link_statements(program: list[str]) -> None:
    for line in program:
        if line.startswith("link"):
            tokens = line.split()
            if len(tokens) != 2:
                throw_error(f"Invalid number of tokens in link statement:\n"
                            f"{line[:-1]}")  # minus the newline char
