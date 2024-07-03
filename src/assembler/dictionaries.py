src_file_path = ""
link_files = []
jump_labels = {}
var_labels = {}

opcodes = {
    "hlt": "0",
    "jin": "1",
    "cmp": "2",
    "add": "3",
    "sub": "4",
    "and": "5",
    "orr": "6",
    "xor": "7",
    "lsh": "8",
    "rsh": "9",
    "inc": "10",
    "dec": "11",
    "lod": "12",
    "ldi": "13",
    "sto": "14",
    "cpr": "15"
}

register_names = {
    "x0":  "0",
    "x1":  "1",
    "x2":  "2",
    "x3":  "3",
    "x4":  "4",
    "x5":  "5",
    "x6":  "6",
    "x7":  "7",
    "x8":  "8",
    "x9":  "9",
    "x10":  "10",
    "x11":  "11",
    "x12":  "12",
    "x13":  "13",
    "x14":  "14",
    "x15":  "15"
}

alt_register_names = {
    "hard_zero_reg": "0",
    "return_reg": "1",
    "arg_a_reg": "2",
    "arg_b_reg": "3",
    "arg_c_reg": "4",
    "flag_reg": "13",
    "stack_ptr_reg": "14",
    "pc_reg": "15"
}
