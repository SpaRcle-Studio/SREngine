#
# Created by Monika on 28.11.2026.
#
# Runs the built SREngine executable (unit tests in headless mode by default) with a timeout.
# The full output goes to <build dir>/claude-run.log, stdout gets only a short summary.
#
# Usage: python .claude/scripts/run.py [--config debug|release] [--dir <build dir>] [--timeout <seconds>]
#                                      [--editor] [-- <engine arguments>]
#   no engine arguments  -> --unit-tests --headless (as in CI)
#   --editor             -> run without arguments (editor with window), only on explicit user request

import argparse
import glob
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

DEFAULT_TEST_ARGUMENTS = ["--unit-tests", "--headless"]

SUMMARY_PATTERN = re.compile(r"TestManager::RunAll\(\) : (running \d+ tests|running test|all tests finished|some tests finished|test .* fatal)"
                             r"|Debugger has been stopped|EngineRuntimeSmokeTest::Run\(\)")
RESULT_COUNT_PATTERN = re.compile(r"^\s+(Success|Error|Skipped):\s*\d+\s*$")
CLI_HELP_PATTERN = re.compile(r"^\s+--[a-z\-]+\s*$")
PROBLEM_PATTERN = re.compile(r"\b(error|fatal|assert|exception|crash|failed)\b", re.IGNORECASE)
ANSI_PATTERN = re.compile(r"\x1b\[[0-9;]*m")

MAX_REPORTED_LINES = 40


def FindExecutable(buildDirectory):
    executables = glob.glob(os.path.join(buildDirectory, "Bin", "SREngine_*.exe"))
    if not executables:
        return None
    return max(executables, key=os.path.getmtime)


def Main():
    parser = argparse.ArgumentParser(description="Run the built SREngine executable (unit tests by default).")
    parser.add_argument("--config", choices=sorted(DEFAULT_BUILD_DIRECTORIES.keys()), default="debug")
    parser.add_argument("--dir", help="build directory (absolute or relative to the repo root)")
    parser.add_argument("--timeout", type=int, default=600, help="seconds before the process is killed")
    parser.add_argument("--editor", action="store_true", help="run the editor without arguments")
    parser.add_argument("engine_arguments", nargs=argparse.REMAINDER, help="arguments after -- are passed to the engine")
    arguments = parser.parse_args()

    buildDirectory = os.path.join(ROOT_DIRECTORY, arguments.dir or DEFAULT_BUILD_DIRECTORIES[arguments.config])
    executablePath = FindExecutable(buildDirectory)
    if not executablePath:
        print(f"run.py : no Bin/SREngine_*.exe in {buildDirectory}. Build it first (/build).")
        return 2

    engineArguments = [argument for argument in arguments.engine_arguments if argument != "--"]
    if not engineArguments and not arguments.editor:
        engineArguments = DEFAULT_TEST_ARGUMENTS

    logPath = os.path.join(buildDirectory, "claude-run.log")
    command = [executablePath] + engineArguments
    print(f"run.py : {subprocess.list2cmdline(command)}")
    print(f"run.py : timeout {arguments.timeout} s, log {logPath}")

    summaryLines = []
    problemLines = []
    started = time.time()
    timedOut = False

    with open(logPath, "w", encoding="utf-8") as logFile:
        process = subprocess.Popen(command, cwd=os.path.dirname(executablePath), stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

        try:
            for rawLine in process.stdout:
                line = ANSI_PATTERN.sub("", rawLine.decode("utf-8", errors="replace")).rstrip()
                logFile.write(line + "\n")

                if SUMMARY_PATTERN.search(line) or RESULT_COUNT_PATTERN.match(line):
                    summaryLines.append(line)
                elif not CLI_HELP_PATTERN.match(line) and PROBLEM_PATTERN.search(line) and line not in problemLines:
                    problemLines.append(line)

                if time.time() - started > arguments.timeout:
                    timedOut = True
                    process.kill()
                    break

            process.wait(timeout=max(1, arguments.timeout - (time.time() - started)))
        except subprocess.TimeoutExpired:
            timedOut = True
            process.kill()
            process.wait()

    duration = time.time() - started
    if timedOut:
        print(f"run.py : TIMEOUT after {duration:.0f} s, process killed")
    else:
        print(f"run.py : exit code {process.returncode}, {duration:.0f} s")

    for line in summaryLines[-MAX_REPORTED_LINES:]:
        print("  " + line[:400])

    if problemLines:
        print(f"run.py : {len(problemLines)} line(s) with errors/asserts, first {min(len(problemLines), MAX_REPORTED_LINES)}:")
        for line in problemLines[:MAX_REPORTED_LINES]:
            print("  " + line[:400])

    print(f"run.py : full log: {logPath} (engine log: %LOCALAPPDATA%\\SpaRcle-Studio\\SREngine\\Logs\\srengine.log)")

    if timedOut:
        return 124

    return process.returncode


if __name__ == "__main__":
    sys.exit(Main())
