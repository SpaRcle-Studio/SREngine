---
name: run
description: Run the built SREngine executable ONLY when the user explicitly asks or allows it in this conversation (e.g. "прогони тесты", "запусти движок") — unit tests in headless mode by default, or with given arguments. Never use it on your own initiative to verify changes.
argument-hint: "[debug|release] [tests | -- <engine arguments>]"
---

The user explicitly asked to run the engine. Arguments: `$ARGUMENTS` (default: `debug`, unit tests).

1. Run only through the script, from the repo root, in the background (`run_in_background`):
   ```
   python .claude/scripts/run.py --config <debug|release> [--timeout <seconds>] [-- <engine arguments>]
   ```
   - Without engine arguments it runs `--unit-tests --headless`, the same as CI (`.github/workflows/WindowsTestsCI.yml`): exit code 0 = success.
   - Engine CLI (`Utils/Common/CLIManager.h`): flags `--unit-tests`, `--continue-after-tests`, `--headless`, `--validation`, `--error-warn-as-assert`, `--disable-editor`, `--no-gpu-assist`; options `--resources <dir>`, `--log-dir <dir>`, `--run-scene <scene>`; the first non-option argument is a project file.
   - Run the editor with a window (`--editor`) only if the user asked for exactly that; it does not exit by itself — use a short `--timeout` or tell the user to close it.
   - Do not run the exe directly or with your own scripts: the timeout and the log summary are in the script.
2. If the build may be outdated (sources changed after the last build), say so; build only if the user asked for it (`/build`).
3. When it finishes, read the summary in the task output. Details: `<build dir>/claude-run.log` and the engine log `%LOCALAPPDATA%\SpaRcle-Studio\SREngine\Logs\srengine.log` — grep around the errors or use `/log`, do not read them whole.
4. Success for tests, as in CI: exit code 0, `TestManager::RunAll() : all tests finished!`, `EngineRuntimeSmokeTest::Run() : launcher initialized successfully.` and `Debugger has been stopped with no errors and warnings!`.
5. Report: command, exit code, test results (success/error/skipped), failed tests with the cause. Fix only failures caused by changes of this session, and only if the user asked to fix.
