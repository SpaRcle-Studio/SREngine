"""Append a read-only VFS resource archive to a statically linked desktop engine."""

import argparse
import fnmatch
import os
from pathlib import Path
import shutil
import struct
import zlib


MAGIC = b"SR_ENGINE_VFS_RESOURCES_V1"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("resources", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--platform", choices=("Windows", "Linux"), required=True)
    args = parser.parse_args()
    resources = args.resources.resolve(strict=True)
    if not resources.is_dir() or args.executable.resolve() == args.output.resolve():
        parser.error("Resources must be a directory and output must differ from input")

    masks = []
    section = ""
    for line in (resources / "Engine/Configs/PackExcludeSettings.conf").read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if line.startswith("[") and line.endswith("]"):
            section = line[1:-1]
        elif line and section in ("All", args.platform):
            masks.append(line.casefold())

    def excluded(path):
        relative = path.relative_to(resources).as_posix().casefold()
        return any(fnmatch.fnmatchcase(relative, mask) for mask in masks)

    files = []
    for directory, directories, names in os.walk(resources):
        parent = Path(directory)
        directories[:] = sorted(name for name in directories if not excluded(parent / name))
        files.extend(parent / name for name in sorted(names) if not excluded(parent / name))
    if len(files) > 65535:
        raise ValueError("Too many resource files for the VFS archive")
    data = bytearray(struct.pack("<H", len(files)))
    for path in files:
        name = ("Resources/" + path.relative_to(resources).as_posix()).encode("utf-8")
        content = path.read_bytes()
        if len(name) > 65535:
            raise ValueError(f"Resource path is too long: {path}")
        data.extend(struct.pack("<H", len(name)))
        data.extend(name)
        data.extend(struct.pack("<Q", len(content)))
        data.extend(content)
        if len(data) > 0xFFFFFFFF:
            raise ValueError("Resource archive exceeds 4 GiB")
    compressed = zlib.compress(data, 9)
    if len(compressed) > 0xFFFFFFFF:
        raise ValueError("Compressed archive exceeds 4 GiB")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(args.executable, args.output)
    with args.output.open("ab") as output:
        output.write(compressed)
        output.write(MAGIC)
        output.write(struct.pack("<QQ", len(data), len(compressed)))
    shutil.copymode(args.executable, args.output)


if __name__ == "__main__":
    main()
