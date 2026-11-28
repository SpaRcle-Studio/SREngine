---
name: render-notes
description: Non-obvious constraints of SREngine rendering (RenderQueue, srptech pipeline, G-buffer, low-res passes, post effects). Use before changing Graphics render code, passes or pipelines.
user-invocable: false
paths:
  - Engine/libs/Graphics/**/Pass/**
  - Engine/libs/Graphics/**/Pipeline/**
  - Engine/libs/Graphics/**/Render/**
  - Engine/libs/Graphics/**/PostProcess/**
  - Engine/libs/Graphics/**/Lighting/**
  - Engine/libs/Graphics/**/Clouds/**
  - Engine/libs/Graphics/**/Fog/**
  - "**/*.srptech"
---

Before editing, read [.claude/docs/Render.md](../../docs/Render.md) in full.

New non-obvious findings go into `.claude/docs/Render.md`, not here.
