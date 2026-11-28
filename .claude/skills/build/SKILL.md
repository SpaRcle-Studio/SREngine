---
name: build
description: Build SREngine ONLY when the user explicitly asks to build/compile the engine in this message (e.g. "собери движок", "build debug") — CMake reconfigure with codegen, then the engine build — and fix errors caused by own changes. Never use it on your own initiative to verify changes.
argument-hint: "[debug|release] [--target <target>|all] [--no-configure]"
---

The user explicitly asked to build. Arguments: `$ARGUMENTS` (default: `debug`, target `SREngine`, with configure).

1. Run the build only through the script, from the repo root, in the background (`run_in_background`) — it takes minutes:
   ```
   python .claude/scripts/build.py --config <debug|release> [--target <target>|all] [--no-configure] [--keep-going]
   ```
   - The script reconfigures CMake (this runs `CI/scripts/codegen.py`) and runs `cmake --build` of the existing IDE build directory (`cmake-build-debug-visual-studio` / `cmake-build-release-visual-studio`) inside the MSVC environment with English diagnostics.
   - Do not compile single files, call `cl`/`ninja`/`cmake` directly or write your own build scripts: codegen and dependencies are skipped that way.
   - Skip configure (`--no-configure`) only if the user asked for it; new `cpp` files and reflection changes need configure.
   - Target `SREngine` is the engine executable with all its modules. Use `all` only if asked: it also builds script modules from `Resources/CMakeLists.txt`, which the editor regenerates at runtime and which may be stale.
2. When it finishes, read the summary in the task output; open `<build dir>/claude-build.log` only around the reported errors (grep, not the whole file).
3. Errors caused by changes of this session — fix them and rebuild (with `--no-configure` if no `cpp`/reflection/CMake changes). Errors in code you did not touch — do not fix, report them with `file:line` and the likely cause.
4. Report: build directory, configuration, OK/FAILED, what was fixed, what remains.
