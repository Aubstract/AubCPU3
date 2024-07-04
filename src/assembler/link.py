# Created by Aubrey on 7/2/2024
import dictionaries as dicts
import error_check as err


def get_path_to_parent_dir(path: str) -> str:
    path = path[::-1]  # reverse the path
    path = path[path.index('\\'):]  # remove the filename
    path = path[::-1]  # reverse again back to normal
    return path


def get_link_file_paths(program: list[str]) -> None:
    err.check_link_statements(program)
    parent_dir_path = get_path_to_parent_dir(dicts.src_file_path)
    for str_line in program:
        if "link" in str_line:
            str_line = str_line.replace('"', '')
            str_line = str_line.replace('/', '\\')
            str_line = str_line[str_line.index(' ') + 1:-1]  # chop off "link " and the newline char
            str_line = parent_dir_path + str_line  # append the link path to the parent path
            dicts.link_files.append(str_line)


def link(program: list[str]) -> list[str]:
    get_link_file_paths(program)
    for link_file_path in dicts.link_files:
        with open(link_file_path) as lf:
            lines = lf.readlines()
            program.extend(lines)

    return program
