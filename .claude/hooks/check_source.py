#
# Created by Monika on 28.11.2026.
#
# PostToolUse hook for Edit/Write: checks the written C++ code against CLAUDE.md rules.
# The tool has already run; violations are returned to the agent as JSON "decision": "block" with a reason.

import json
import re
import sys

CPP_EXTENSIONS = (".cpp", ".cc", ".cxx", ".h", ".hpp", ".inl")
HEADER_EXTENSIONS = (".h", ".hpp")
SOURCE_EXTENSIONS = (".cpp", ".cc", ".cxx")

FORBIDDEN_STD = (
    "vector", "deque", "list", "forward_list", "map", "multimap", "unordered_map", "unordered_multimap",
    "set", "multiset", "unordered_set", "unordered_multiset", "string", "wstring", "u8string", "u16string",
    "u32string", "string_view", "wstring_view", "pair", "make_pair", "tuple", "make_tuple", "tie", "optional",
    "nullopt", "make_optional", "function", "bind", "ranges", "views", "unique_ptr", "make_unique",
    "shared_ptr", "make_shared", "weak_ptr", "enable_shared_from_this", "stack", "queue", "priority_queue",
    "to_string", "to_wstring", "stringstream", "ostringstream", "istringstream", "thread",
)

FORBIDDEN_INCLUDES = (
    "vector", "deque", "list", "map", "unordered_map", "set", "unordered_set", "string", "string_view",
    "optional", "functional", "tuple", "utility", "memory", "ranges", "sstream", "thread", "queue", "stack",
)

STD_PATTERN = re.compile(r"\bstd::(" + "|".join(FORBIDDEN_STD) + r")\b")
INCLUDE_PATTERN = re.compile(r"^\s*#\s*include\s*<(" + "|".join(FORBIDDEN_INCLUDES) + r")>", re.MULTILINE)
COMMENT_PATTERN = re.compile(r"//.*?$|/\*.*?\*/", re.MULTILINE | re.DOTALL)
STRING_PATTERN = re.compile(r"\"(?:\\.|[^\"\\\n])*\"")


def ReadInput():
    try:
        return json.loads(sys.stdin.buffer.read().decode("utf-8", errors="replace"))
    except Exception:
        return {}


def StripCommentsAndStrings(text):
    text = STRING_PATTERN.sub("\"\"", text)
    return COMMENT_PATTERN.sub("", text)


def GetWrittenText(toolName, toolInput):
    if toolName == "Write":
        return toolInput.get("content") or ""

    if toolName == "MultiEdit":
        return "\n".join((edit.get("new_string") or "") for edit in (toolInput.get("edits") or []))

    return toolInput.get("new_string") or ""


def CheckCode(text, path, isNewFile):
    problems = []
    code = StripCommentsAndStrings(text)

    stdUsages = sorted(set(STD_PATTERN.findall(code)))
    if stdUsages:
        problems.append("STL вместо типов движка: " + ", ".join("std::" + name for name in stdUsages)
                        + " (замени на SR_UTILS_NS::/SR_HTYPES_NS:: аналоги или объясни, почему оставлено)")

    includes = sorted(set(INCLUDE_PATTERN.findall(code)))
    if includes:
        problems.append("инклюд STL (" + ", ".join("<" + name + ">" for name in includes) + ") — STL уже в pch")

    if re.search(r"^\s*#\s*pragma\s+once", code, re.MULTILINE):
        problems.append("#pragma once — нужен guard #ifndef SR_ENGINE_<МОДУЛЬ>_<ФАЙЛ>_H")

    if re.search(r"\bnamespace\s*\{", code):
        problems.append("анонимный namespace — вынеси хелперы в отдельный файл с именованным namespace")

    if re.search(r"\bauto\s*\*|\bauto\s*&(?!&)", code):
        problems.append("auto*/auto& — используй auto&&")

    if re.search(r"^\s*using\s+namespace\b", code, re.MULTILINE):
        problems.append("using namespace запрещён")

    if isNewFile:
        normalizedPath = path.replace("\\", "/")

        if path.endswith(SOURCE_EXTENSIONS) and "/inc/" in normalizedPath:
            problems.append("cpp лежит в inc — cpp только в src")

        if path.endswith(HEADER_EXTENSIONS) and "/src/" in normalizedPath:
            problems.append("h лежит в src — h только в inc")

        if not re.match(r"\s*//\s*\n\s*//\s*Created by .+ on \d{2}\.\d{2}\.\d{4}\.", text):
            problems.append("нет шапки `// Created by <author> on DD.MM.YYYY.`")

        if path.endswith(HEADER_EXTENSIONS) and not re.search(r"^\s*#ifndef\s+SR_ENGINE_\w+_H\b", text, re.MULTILINE):
            problems.append("нет guard #ifndef SR_ENGINE_<МОДУЛЬ>_<ФАЙЛ>_H")

    return problems


def Main():
    data = ReadInput()
    toolName = data.get("tool_name") or ""
    toolInput = data.get("tool_input") or {}
    path = toolInput.get("file_path") or ""

    if not path.lower().endswith(CPP_EXTENSIONS):
        return 0

    normalizedPath = path.replace("\\", "/").lower()
    if normalizedPath.count("/libs/") > 1 or ("/libs/" in normalizedPath and "/engine/libs/" not in normalizedPath):
        return 0

    if "/codegen/" in normalizedPath or normalizedPath.endswith(".generated.hpp"):
        return 0

    text = GetWrittenText(toolName, toolInput)
    if not text:
        return 0

    problems = CheckCode(text, path, toolName == "Write")
    if not problems:
        return 0

    reason = "check_source.py : " + path + " нарушает CLAUDE.md:\n- " + "\n- ".join(problems) \
        + "\nИсправь, если это не осознанное исключение (тогда упомяни его в итоге)."
    sys.stdout.write(json.dumps({"decision": "block", "reason": reason}))
    return 0


if __name__ == "__main__":
    sys.exit(Main())
