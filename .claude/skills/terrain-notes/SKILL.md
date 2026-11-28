---
name: terrain-notes
description: Non-obvious constraints of SREngine terrain (LOD octree chunks, marching cubes, triplanar) and grass. Use before changing terrain or grass code or shaders.
user-invocable: false
paths:
  - Engine/**/World/Terrain*
  - Resources/Engine/Shaders/MarchingCubes/**
  - Resources/Engine/Shaders/terrain*
  - Resources/Engine/Prefabs/Terrain.prefab
---

Before editing, read [.claude/docs/Terrain.md](../../docs/Terrain.md) in full. Shader changes also need [.claude/docs/Shaders.md](../../docs/Shaders.md).

New non-obvious findings go into `.claude/docs/Terrain.md`, not here.
