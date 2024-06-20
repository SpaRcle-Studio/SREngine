<p align="center">
 <h1 align="center">SpaRcle Engine</h1>
  <p align="center">
    <img alt="Project Status: Active – The project is under active delopment!." src="https://www.repostatus.org/badges/latest/active.svg" />
    <img alt="CodeFactor." src="https://www.codefactor.io/repository/github/sparcle-studio/srengine/badge/dev" />
    <img alt="GitHub Contributors." src="https://img.shields.io/github/contributors/SpaRcle-Studio/SREngine" />
    <img alt="Issues." src="https://img.shields.io/github/issues/SpaRcle-Studio/SREngine?color=0088ff" />
    <img alt="Commit Activity." src="https://img.shields.io/github/commit-activity/m/SpaRcle-Studio/SREngine/dev" />
    <a href="https://discord.gg/NHuhNwFtYQ"><img alt="Discord server." src="https://img.shields.io/discord/768652124204433429?logo=discord&link=https%3A%2F%2Fdiscord.gg%2FqAr7Grz3RD" /></a>
    <a href="https://opencollective.com/sparcle-studio"><img alt="Open Colletive." src="https://opencollective.com/sparcle-studio/tiers/badge.svg" /></a>
  </p>
  <p align="center">
    <img alt="Build statistics." src="https://buildstats.info/github/chart/SpaRcle-Studio/SREngine?buildCount=50&branch=dev" />
  </p>

SpaRcle Engine is an ongoing game engine developed in C++. 
It aims to establish a strong base for game creation and is currently in the early stages of development, emphasizing the creation of a versatile and efficient architecture.
</p>

## Screenshots

<img width="1920" alt="image_2023-05-31_21-40-59" src="https://github.com/Monika0000/SREngine/assets/47291246/6bf73c99-81a2-4a3e-ad28-4c788884eb38">
<img width="1920" alt="image_2023-05-31_21-40-59" src="https://github.com/Monika0000/SREngine/assets/47291246/32cfdbcb-5a0d-4a74-9501-539da40379e2">

## Supported compilers
- [x] MSVC (stable)
- [x] GCC (stable)
- [ ] MinGW
- [ ] Cygwin
- [ ] Clang

## Supported platforms
- [x] Windows 10/11
- [x] Linux X11
- [ ] Linux Wayland
- [ ] Android

## Branches 
 * master - branch for releases
 * dev - active development branch 
 * features/* - branches for new features
 * tmp/* - temporary branches for dangerous experiments
 * release/* - branches for release candidates

## Building
 * [Windows Build Guide.](Documentation/WindowsBuild.md)
 * [Linux Build Guide.](Documentation/LinuxBuild.md)

## Used libraries
  * [ImGUI](https://github.com/ocornut/imgui)
  * [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
  * [imgui-node-editor](https://github.com/thedmd/imgui-node-editor)
  * [EvoScript](https://github.com/Monika0000/EvoScript)
  * [EvoVulkan](https://github.com/Monika0000/EvoVulkan)
  * [Assimp](https://github.com/assimp/assimp)
  * [Vulkan Memory Allocator](https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator)
  * [stb](https://github.com/nothings/stb)
  * [glm](https://github.com/g-truc/glm)
  * [Bullet3](https://github.com/bulletphysics/bullet3)
  * [PhysX](https://github.com/NVIDIAGameWorks/PhysX)
  * [Box2D](https://github.com/erincatto/box2d)
  * [json](https://github.com/nlohmann/json)
  * and more...
  
## Features
  * SpaRcle Shader Language (SRSL)
  * SpaRcle Logical Machine (SRLM) aka Blueprints 
  * Chunk system 
  * Render passes
  * Custom framebuffers
  * C++ scripting system
  * Animations
  * SSAO
  * Cascaded shadow mapping
  * Ray-marching
  * Physics
  * Font renderer
  * Vulkan pipeline
  * Multi-cameras renderer 
  * Geometry loader
  * Texture loader

## FAQ
 <details>
 <summary> Why SpaRcle Engine? </summary>
  
    It's a lightweight and simple Unity-like game engine that maximizes cross-platform 
    compatibility and utilizes fast and efficient C++ for scripting. 
    
    The engine offers the flexibility to customize the graphics pipeline 
    according to specific requirements.

    The ability to create endless procedurally generated worlds is provided 
    wtih a system that divides the world into regions and chunks.
 </details>


 # Contributors 
 <a href="https://github.com/SpaRcle-Studio/SREngine/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=SpaRcle-Studio/SREngine" />
</a>

## Star History 📈

<a href="https://star-history.com/#SpaRcle-Studio/SREngine&Date">
 <picture>
   <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=SpaRcle-Studio/SREngine&type=Date&theme=dark" />
   <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=SpaRcle-Studio/SREngine&type=Date" />
   <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=SpaRcle-Studio/SREngine&type=Date" />
 </picture>
</a>
