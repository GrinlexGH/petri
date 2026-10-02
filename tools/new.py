#!/usr/bin/env python3
"""Create a new project in petri/src.

Usage:
    python tools/new.py <name>

Creates petri/src/<name>/ with a default CMakeLists.txt and main.cpp,
then registers it in petri/src/CMakeLists.txt via add_subdirectory().
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC_DIR = ROOT / "src"
SRC_CMAKE = SRC_DIR / "CMakeLists.txt"

# Folder name doubles as the CMake target name.
NAME_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_-]*$")

CMAKE_TEMPLATE = """\
add_executable(@NAME@)

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.h" "*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.c" "*.cc" "*.cpp")

if(headers)
    target_sources(@NAME@
        PRIVATE
            FILE_SET HEADERS
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
            FILES ${headers}
    )
endif()

if(sources)
    target_sources(@NAME@
        PRIVATE
            FILE_SET SOURCES
            BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
            FILES ${sources}
    )
endif()

target_link_libraries(@NAME@ PRIVATE fmt::fmt)

petri_configure_target(@NAME@ VS_STARTUP)
"""

MAIN_TEMPLATE = """\
#include <fmt/format.h>

int main() {
    fmt::println("Hello from @NAME@!");
    return 0;
}
"""


def render(template: str, name: str) -> str:
    return template.replace("@NAME@", name)


def write_file(path: Path, content: str) -> None:
    with open(path, "w", encoding="utf-8", newline="\n") as f:
        f.write(content)


def main() -> int:
    parser = argparse.ArgumentParser(description="Create a new project in petri/src")
    parser.add_argument("name", help="project name (used as folder and target name)")
    name = parser.parse_args().name

    if not NAME_RE.match(name):
        print(
            f"error: invalid name '{name}' "
            "(use letters, digits, '_' or '-', and don't start with a digit)",
            file=sys.stderr,
        )
        return 1

    project_dir = SRC_DIR / name
    if project_dir.exists():
        print(f"error: {project_dir} already exists", file=sys.stderr)
        return 1

    subdir_line = f"add_subdirectory({name})"
    existing = SRC_CMAKE.read_text(encoding="utf-8") if SRC_CMAKE.exists() else ""
    if subdir_line in (line.strip() for line in existing.splitlines()):
        print(f"error: '{subdir_line}' is already in {SRC_CMAKE}", file=sys.stderr)
        return 1

    project_dir.mkdir(parents=True)
    write_file(project_dir / "CMakeLists.txt", render(CMAKE_TEMPLATE, name))
    write_file(project_dir / "main.cpp", render(MAIN_TEMPLATE, name))

    prefix = "\n" if existing and not existing.endswith("\n") else ""
    with open(SRC_CMAKE, "a", encoding="utf-8", newline="\n") as f:
        f.write(f"{prefix}{subdir_line}\n")

    print(f"created {project_dir.relative_to(ROOT)}/")
    print("  CMakeLists.txt")
    print("  main.cpp")
    print(f"registered in {SRC_CMAKE.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
