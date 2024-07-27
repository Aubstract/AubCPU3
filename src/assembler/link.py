# Created by Aubrey on 7/2/2024
import dictionaries as dicts
import error_check as err


def read_file(file_path: str) -> list[str]:
    with open(file_path) as fp:
        return fp.readlines()


def get_path_to_parent_dir(path: str) -> str:
    path = path[::-1]  # reverse the path
    path = path[path.index('\\'):]  # remove the filename
    path = path[::-1]  # reverse again back to normal
    return path


def append_linked_files(program: list[str], src_path: str) -> list[str]:
    err.check_link_statements(program)
    linked_progs = []
    parent_dir_path = get_path_to_parent_dir(src_path)
    for prog_line in program:
        if prog_line.startswith("link "):
            link_path = prog_line.removeprefix("link ")
            link_path = link_path.replace('"', '')
            link_path = link_path.replace('\n', '')
            link_path = link_path.replace('/', '\\')
            link_path = parent_dir_path + link_path
            if link_path not in dicts.link_files:
                dicts.link_files.append(link_path)
                linked_progs.extend(read_file(link_path))
                linked_progs.extend(append_linked_files(linked_progs, link_path))
    return linked_progs


def link(program: list[str]) -> list[str]:
    program.extend(append_linked_files(program, dicts.src_file_path))
    return program
