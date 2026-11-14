#!/usr/bin/env python3
# Created by Codex on 14.11.2026.
"""Build the AngelScript breakpoint integration against an installed CLion SDK."""

import argparse
from pathlib import Path
import subprocess
import zipfile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--clion-home", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[2]
    source = root / "Tools/CLion/AngelScriptBreakpoints"
    output = args.output.resolve()
    classes = output / "classes"
    classes.mkdir(parents=True, exist_ok=True)
    sdk = args.clion_home.resolve()
    debugger_jar = sdk / "plugins/nativeDebug-plugin/lib/modules/intellij.cidr.debugger.core.jar"
    if not debugger_jar.is_file():
        parser.error("CLion native debugger SDK was not found")
    classpath = [*sorted((sdk / "lib").glob("*.jar")), debugger_jar]
    javac = sdk / "jbr/bin/javac.exe"
    if not javac.exists():
        javac = sdk / "jbr/bin/javac"
    import os
    options = ["--release", "21", "-encoding", "UTF-8", "-classpath",
               os.pathsep.join(str(path) for path in classpath), "-d", str(classes)]
    options.extend(str(path) for path in sorted((source / "src").rglob("*.java")))
    argfile = output / "javac.args"
    argfile.write_text("\n".join('"' + arg.replace("\\", "/").replace('"', '\\"') + '"' for arg in options), encoding="utf-8")
    subprocess.run([str(javac), "@" + str(argfile)], check=True)
    jar = output / "sparcle-angelscript-breakpoints.jar"
    with zipfile.ZipFile(jar, "w", zipfile.ZIP_DEFLATED) as archive:
        for base in (classes, source / "resources"):
            for path in sorted(base.rglob("*")):
                if path.is_file():
                    archive.write(path, path.relative_to(base).as_posix())
    distribution = output / "sparcle-angelscript-breakpoints.zip"
    with zipfile.ZipFile(distribution, "w", zipfile.ZIP_DEFLATED) as archive:
        archive.write(jar, "sparcle-angelscript-breakpoints/lib/" + jar.name)
    print(jar)
    print(distribution)


if __name__ == "__main__":
    main()
