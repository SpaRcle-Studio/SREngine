import subprocess
from pathlib import Path

LIBRARIES = [
    "Engine",
    "Graphics",
    "Audio",
    "Scripting",
    "ImmediateGUI",
    "Utils",
    "Physics",
]

LIMIT = 65535


def find_build_dirs(root: Path):
    return sorted(
        p for p in root.iterdir()
        if p.is_dir() and "build" in p.name.lower()
    )


def choose_build(builds):
    if not builds:
        print("Не найдено ни одной build-папки.")
        exit(1)

    print("Найденные build-папки:\n")

    for i, build in enumerate(builds):
        print(f"[{i}] {build}")

    while True:
        try:
            index = int(input("\nВыберите build: "))
            if 0 <= index < len(builds):
                return builds[index]
        except ValueError:
            pass

        print("Некорректный ввод.")


def find_objects(build_dir: Path, library: str):
    if library == "Engine":
        return list((build_dir / "Engine" / "CMakeFiles" / "Engine.dir").rglob("*.obj"))

    root = (build_dir / "Engine" / "libs" / library / "CMakeFiles" / f"{library}.dir")

    if not root.exists():
        return []

    return list(root.rglob("*.obj"))


def analyze_obj(obj: Path):
    try:
        result = subprocess.run(
            ["dumpbin", "/symbols", str(obj)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding="utf-8",
            errors="ignore",
            check=True,
        )
    except FileNotFoundError:
        print("Не найден dumpbin.exe")
        exit(1)

    count = 0

    for line in result.stdout.splitlines():
        if " External " in line:
            count += 1

    return count


def main():
    root = Path(__file__).resolve().parent.parent.parent

    build = choose_build(find_build_dirs(root))

    print(f"\nИспользуется build: {build}\n")

    print(f"{'Library':<15}{'Objects':>10}{'Symbols':>12}")
    print("-" * 40)

    total_symbols = 0
    total_objects = 0

    heavy_objects = []

    messages = []

    for library in LIBRARIES:
        print(f"Loading {library}...")
        objects = find_objects(build, library)

        if not objects:
            print(f"Library {library} not found or has no object files.")
            continue

        lib_symbols = 0

        print(f"Analyzing {len(objects)} object files in {library}...")
        for obj in objects:
            symbols = analyze_obj(obj)
            lib_symbols += symbols

            heavy_objects.append((symbols, obj))

        total_symbols += lib_symbols
        total_objects += len(objects)

        messages.append(f"{library:<15}" f"{len(objects):>10}" f"{lib_symbols:>12}")

    print("-" * 40)

    for message in messages:
        print(message)

    print("-" * 40)
    print(f"{'Total':<15}" f"{total_objects:>10}" f"{total_symbols:>12}")

    heavy_objects.sort(reverse=True, key=lambda x: x[0])

    print("\nTop 20 heaviest object files:\n")

    for symbols, obj in heavy_objects[:20]:
        print(f"{symbols:>8}  {obj.relative_to(build)}")


if __name__ == "__main__":
    main()