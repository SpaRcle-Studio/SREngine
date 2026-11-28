#
# Created by Monika on 28.11.2026.
#
# PreToolUse hook for Bash/PowerShell.
# Shell edits of sources are always blocked (exit code 2, stderr is shown to the agent).
# Builds, compilers, codegen, .claude/scripts/build.py|run.py, the engine executable and .bat/.cmd scripts
# (they may build inside) require user confirmation ("ask"); SRENGINE_ALLOW_BUILD=1 in the
# environment of Claude Code disables this check for the whole session.

import json
import os
import re
import sys

BLOCKED_PROGRAMS = {
    "cmake", "cmake-gui", "ctest", "ninja", "msbuild", "make", "mingw32-make", "nmake",
    "cl", "clang", "clang++", "clang-cl", "gcc", "g++", "devenv",
}

SOURCE_EXTENSION = r"\.(cpp|cc|cxx|c|h|hpp|inl|srsl|as)\b"

SHELL_EDIT_PATTERNS = [
    (r"\bsed\b[^|;&]*\s-[a-zA-Z]*i", "sed -i"),
    (r"\bsed\b[^|;&]*--in-place", "sed --in-place"),
    (r"\bperl\b[^|;&]*\s-[a-zA-Z]*i", "perl -i"),
    (r"(?<![0-9&\-=])>>?\s*['\"]?[^\s'\"|;&>]*" + SOURCE_EXTENSION, "перенаправление вывода в исходник"),
    (r"\btee\b[^|;&]*" + SOURCE_EXTENSION, "tee в исходник"),
    (r"\b(Set-Content|Add-Content|Out-File|WriteAllText|WriteAllLines)\b[^|;]*" + SOURCE_EXTENSION, "запись PowerShell в исходник"),
]

SHELL_LAUNCHERS = {"cmd", "powershell", "pwsh", "bash", "sh", "start-process"}

SHELL_LAUNCHER_PATTERN = re.compile(
    r"\b(?:cmd|powershell|pwsh|bash|sh)(?:\.exe)?\s+(?:/[a-z]\s+|//[a-z]\s+|-\w+\s+)*?(?:/c|//c|-c|-command)\s+(?P<quote>[\"'])(?P<body>.*?)(?P=quote)(?=\s|$)",
    re.IGNORECASE | re.DOTALL)

SPLIT_PATTERN = re.compile(r"&&|\|\||[;|\n]|\$\(|`|\(")


def ReadInput():
    try:
        return json.loads(sys.stdin.buffer.read().decode("utf-8", errors="replace"))
    except Exception:
        return {}


def NormalizeProgram(token):
    token = token.strip("'\"")
    token = token.replace("\\", "/").split("/")[-1].lower()
    for suffix in (".exe", ".bat", ".cmd", ".ps1"):
        if token.endswith(suffix):
            token = token[:-len(suffix)]
    return token


def GetSegmentTokens(segment):
    tokens = segment.strip().split()
    while tokens and (tokens[0] in ("&", "sudo", "time", "call", "start", "exec", "env", "command") or re.match(r"^\w+=", tokens[0])):
        tokens = tokens[1:]
    return tokens


def FlattenQuoted(match):
    return re.sub(r"[\s|;&()`$]+", "_", match.group(0)[1:-1])


def FindBuildCommand(command):
    for match in SHELL_LAUNCHER_PATTERN.finditer(command):
        nested = FindBuildCommand(match.group("body"))
        if nested:
            return nested

    if re.search(r"\b(cmd|powershell|pwsh|bash|sh)(\.exe)?\s+(/c|//c|-c|-command)\b", command, re.IGNORECASE):
        nestedProgram = re.search(r"\b(cmake|ninja|msbuild|vcvars\w*|devenv)(\.exe|\.bat)?\b", command, re.IGNORECASE)
        if nestedProgram:
            return f"запуск `{nestedProgram.group(1).lower()}` во вложенном shell"

    unquoted = re.sub(r"'[^']*'|\"[^\"]*\"", FlattenQuoted, command)

    for segment in SPLIT_PATTERN.split(unquoted):
        tokens = GetSegmentTokens(segment)
        if not tokens:
            continue

        program = NormalizeProgram(tokens[0])

        if program in BLOCKED_PROGRAMS or program.startswith("vcvars"):
            return f"запуск `{program}`"

        if re.search(r"\.(bat|cmd)$", tokens[0].strip("'\""), re.IGNORECASE):
            return f"запуск скрипта `{program}` (может собирать)"

        if program in SHELL_LAUNCHERS:
            for token in tokens[1:]:
                if re.search(r"\.(bat|cmd|ps1)['\"]?$", token, re.IGNORECASE):
                    return f"запуск скрипта `{NormalizeProgram(token)}` (может собирать)"

    if re.search(r"codegen\.py", command, re.IGNORECASE):
        return "запуск кодогенерации"

    if re.search(r"\.claude[\\/]scripts[\\/]build\.py", command, re.IGNORECASE):
        return "сборка движка (.claude/scripts/build.py)"

    if re.search(r"\.claude[\\/]scripts[\\/]run\.py", command, re.IGNORECASE):
        return "запуск движка (.claude/scripts/run.py)"

    if re.search(r"SREngine_[^\s'\"]*\.exe", command, re.IGNORECASE) \
            and not re.search(r"^\s*(ls|dir|stat|file|du|Get-ChildItem|Get-Item|Test-Path)\b", command, re.IGNORECASE):
        return "запуск бинарника движка"

    return None


def FindShellEdit(command):
    if not re.search(SOURCE_EXTENSION, command, re.IGNORECASE):
        return None

    for pattern, name in SHELL_EDIT_PATTERNS:
        if re.search(pattern, command, re.IGNORECASE):
            return f"правка исходников через shell ({name}) запрещена CLAUDE.md: используй Edit/Write"

    if re.search(r"\b(python3?|py|node|ruby)\b", command, re.IGNORECASE) \
            and re.search(r"\.write\(|write_text|writeFileSync|open\([^)]*['\"][wa]", command):
        return "правка исходников скриптом запрещена CLAUDE.md: используй Edit/Write"

    return None


def Main():
    data = ReadInput()
    command = (data.get("tool_input") or {}).get("command") or ""
    if not command:
        return 0

    violation = FindShellEdit(command)
    if violation:
        sys.stderr.buffer.write(f"guard_shell.py : заблокировано — {violation}.\n".encode("utf-8"))
        return 2

    if os.environ.get("SRENGINE_ALLOW_BUILD") == "1":
        return 0

    buildCommand = FindBuildCommand(command)
    if buildCommand:
        reason = f"guard_shell.py : {buildCommand} — по CLAUDE.md сборку и запуск делает пользователь. Разрешить этот вызов?"
        output = {
            "hookSpecificOutput": {
                "hookEventName": "PreToolUse",
                "permissionDecision": "ask",
                "permissionDecisionReason": reason,
            }
        }
        sys.stdout.write(json.dumps(output))

    return 0


if __name__ == "__main__":
    sys.exit(Main())
