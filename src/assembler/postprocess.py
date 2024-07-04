# Created by Aubrey on 7/3/2024
import dictionaries as dicts


def print_dict(dict_name: str, dictionary: dict) -> None:
    print(dict_name + ':')
    for key, value in dicts.jump_labels.items():
        print('\t' + key + ": " + value)
    print()


def postprocess(program: list[int]) -> None:
    print(f"\nSUCCESSFULLY ASSEMBLED!\n"
          f"\nNumber of instructions: {len(program)}\n")

    print_dict("Var Labels", dicts.var_labels)
    print_dict("Jump Labels", dicts.jump_labels)

    print(f"Linked Files:")
    for label in dicts.link_files:
        print('\t' + label)
