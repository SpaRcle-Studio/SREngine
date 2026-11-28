---
name: new-file
description: Create a new SREngine C++ header/source pair with the correct location, header comment, include guard, includes and codegen include.
argument-hint: "<Module>/<Path>/<Name> [reflected]"
disable-model-invocation: true
---

Create the file pair for `$ARGUMENTS` following CLAUDE.md:

1. Location: `h` only in `inc`, `cpp` only in `src` of the module (`Engine/inc/Engine/...` + `Engine/src/Engine/...`, or `Engine/libs/<Module>/inc/<Module>/...` + `Engine/libs/<Module>/src/<Module>/...`). Look at neighbouring files of the same directory first.
2. Header comment with the current date (author: as in the user's recent files, e.g. `Monika`):
   ```cpp
   //
   // Created by Monika on DD.MM.YYYY.
   //
   ```
3. Guard `SR_ENGINE_<MODULE>_<PATH>_<FILE>_H` in UPPER_SNAKE_CASE, no `#pragma once`. Examples: `Engine/World/TerrainGrass.h` → `SR_ENGINE_WORLD_TERRAIN_GRASS_H`; `Physics/GravityField.h` → `SR_ENGINE_PHYSICS_GRAVITY_FIELD_H`.
4. The header includes the module `stdInclude.h` (directly or through another module header), otherwise codegen breaks — see [.claude/docs/Codegen.md](../../docs/Codegen.md).
5. Includes are grouped by module with blank lines: current module, then Engine → Graphics → Physics → Audio → Utils → Codegen → others. No STL includes (they are in pch).
6. If the header has `SR_CLASS`/`SR_STRUCT`/`SR_ENUM*` (argument `reflected` or the content needs reflection): read [.claude/docs/Codegen.md](../../docs/Codegen.md), and put `#include <Codegen/<FileName>.generated.hpp>` as the LAST include of the paired `cpp`, one per header.
7. Do not add the files to CMakeLists. Tell the user to reload CMake, since a new `cpp` was added.
