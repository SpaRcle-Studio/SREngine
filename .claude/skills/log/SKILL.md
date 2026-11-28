---
name: log
description: Analyze the last SREngine run log (errors, warnings, crashes) and return only the relevant findings.
argument-hint: "[what to look for, e.g. terrain, shader name, crash]"
disable-model-invocation: true
context: fork
agent: log-analyst
---

Analyze the log of the last SREngine run: `%LOCALAPPDATA%\SpaRcle-Studio\SREngine\Logs\srengine.log` (not the one in the build `Bin`).

Focus: $ARGUMENTS (if empty: all errors, asserts, crashes and repeated warnings).
