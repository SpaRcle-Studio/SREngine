---
name: precheck
description: Review the current uncommitted SREngine changes against CLAUDE.md rules before handing them to the user.
argument-hint: "[file or directory to limit the check]"
disable-model-invocation: true
context: fork
agent: rules-reviewer
---

Check the current uncommitted changes of the SREngine repository against CLAUDE.md. Scope: $ARGUMENTS (if empty, all changed and untracked files under `Engine/` and `Resources/`; skip `.claude/` and third-party `libs/*/libs/`).

Report violations only in lines that were added or changed in the diff, with `file:line`, the rule and a suggested fix. Code that was there before the change is listed separately as "pre-existing", at most 10 entries.
