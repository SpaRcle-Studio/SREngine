#
# Created by Monika on 28.11.2026.
#
# Builds SREngine the same way the IDE does: CMake reconfigure (runs CI/scripts/codegen.py) and
# `cmake --build` of an existing build directory inside the MSVC environment.
# The full log goes to <build dir>/claude-build.log, stdout gets only a short summary of errors.
#
# Usage: python .claude/scripts/build.py [--config debug|release] [--dir <build dir>]
#                                        [--target SREngine|all|<target>] [--no-configure] [--keep-going]

import argparse
import os
import re
import subprocess
import sys
import time

ROOT_DIRECTORY = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

DEFAULT_BUILD_DIRECTORIES = {
    "debug": "cmake-build-debug-visual-studio",
    "release": "cmake-build-release-visual-studio",
}

VSWHERE_PATH = r"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"

ERROR_PATTERN = re.compile(r"\berror [A-Z]+\d+|fatal error|^FAILED:|CMake Error|unresolved external|LINK : fatal", re.IGNORECASE)

MAX_REPORTED_ERRORS = 40


def ReadCache(buildDirectory):
    cachePath = os.path.join(buildDirectory, "CMakeCache.txt")
    if not os.path.isfile(cachePath):
        return None

    cache = {}
    with open(cachePath, encoding="utf-8", errors="replace") as file:
        for line in file:
            match = re.match(r"^([A-Za-z_0-9]+):[A-Z]+=(.*)$", line.rstrip("\n"))
            if match:
                cache[match.group(1)] = match.group(2)

    return cache


def FindVcvars(cache):
    compilerPath = cache.get("CMAKE_CXX_COMPILER", "").replace("\\", "/")
    marker = "/VC/Tools/MSVC/"
    if marker in compilerPath:
        vcvarsPath = compilerPath.split(marker)[0] + "/VC/Auxiliary/Build/vcvars64.bat"
        if os.path.isfile(vcvarsPath):
            return vcvarsPath

    if os.path.isfile(VSWHERE_PATH):
        result = subprocess.run([VSWHERE_PATH, "-latest", "-prerelease", "-products", "*", "-property", "installationPath"],
                                capture_output=True, text=True)
        installationPath = result.stdout.strip().splitlines()[0] if result.stdout.strip() else ""
        vcvarsPath = os.path.join(installationPath, "VC", "Auxiliary", "Build", "vcvars64.bat")
        if installationPath and os.path.isfile(vcvarsPath):
            return vcvarsPath

    return None


def GetMsvcEnvironment(vcvarsPath):
    result = subprocess.run(f'cmd /d /s /c ""{vcvarsPath}" >nul && set"', capture_output=True)
    if result.returncode != 0:
        return None

    environment = {}
    for line in result.stdout.decode("utf-8", errors="replace").splitlines():
        if "=" in line:
            name, value = line.split("=", 1)
            environment[name] = value

    environment["VSLANG"] = "1033"
    return environment


def RunStep(name, command, environment, logFile):
    logFile.write(f"\n===== {name}: {subprocess.list2cmdline(command)}\n")
    logFile.flush()

    errors = []
    started = time.time()
    process = subprocess.Popen(command, cwd=ROOT_DIRECTORY, env=environment, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    for rawLine in process.stdout:
        line = rawLine.decode("utf-8", errors="replace").rstrip()
        logFile.write(line + "\n")
        if ERROR_PATTERN.search(line) and line not in errors:
            errors.append(line)

    process.wait()
    duration = time.time() - started
    print(f"build.py : {name} - {'OK' if process.returncode == 0 else 'FAILED (code ' + str(process.returncode) + ')'}, {duration:.0f} s")

    return process.returncode, errors


def Main():
    parser = argparse.ArgumentParser(description="Configure (with codegen) and build SREngine.")
    parser.add_argument("--config", choices=sorted(DEFAULT_BUILD_DIRECTORIES.keys()), default="debug")
    parser.add_argument("--dir", help="build directory (absolute or relative to the repo root)")
    parser.add_argument("--target", default="SREngine", help="SREngine (engine with all its modules), all, or any CMake target")
    parser.add_argument("--no-configure", action="store_true", help="skip CMake reconfigure and codegen")
    parser.add_argument("--keep-going", action="store_true", help="continue building other targets after an error")
    arguments = parser.parse_args()

    buildDirectory = os.path.join(ROOT_DIRECTORY, arguments.dir or DEFAULT_BUILD_DIRECTORIES[arguments.config])
    cache = ReadCache(buildDirectory)
    if cache is None:
        print(f"build.py : no CMakeCache.txt in {buildDirectory}. Configure it once from the IDE first.")
        return 2

    cmakePath = cache.get("CMAKE_COMMAND") or "cmake"

    vcvarsPath = FindVcvars(cache)
    if not vcvarsPath:
        print("build.py : vcvars64.bat not found (neither near CMAKE_CXX_COMPILER nor via vswhere).")
        return 2

    environment = GetMsvcEnvironment(vcvarsPath)
    if environment is None:
        print(f"build.py : failed to initialize the MSVC environment from {vcvarsPath}.")
        return 2

    logPath = os.path.join(buildDirectory, "claude-build.log")
    print(f"build.py : {buildDirectory} ({cache.get('CMAKE_BUILD_TYPE', '?')}), target {arguments.target}, log {logPath}")

    allErrors = []
    with open(logPath, "w", encoding="utf-8") as logFile:
        if not arguments.no_configure:
            code, errors = RunStep("configure + codegen", [cmakePath, "-S", ROOT_DIRECTORY, "-B", buildDirectory], environment, logFile)
            allErrors.extend(errors)
            if code != 0:
                PrintErrors(allErrors, logPath)
                return code

        buildCommand = [cmakePath, "--build", buildDirectory]
        if arguments.target != "all":
            buildCommand += ["--target", arguments.target]
        if arguments.keep_going and cache.get("CMAKE_GENERATOR", "").startswith("Ninja"):
            buildCommand += ["--", "-k", "0"]

        code, errors = RunStep("build", buildCommand, environment, logFile)
        allErrors.extend(errors)

    PrintErrors(allErrors, logPath)
    return code


def PrintErrors(errors, logPath):
    if not errors:
        return

    print(f"build.py : {len(errors)} error line(s), first {min(len(errors), MAX_REPORTED_ERRORS)}:")
    for line in errors[:MAX_REPORTED_ERRORS]:
        print("  " + line[:400])
    print(f"build.py : full log: {logPath}")


if __name__ == "__main__":
    sys.exit(Main())
