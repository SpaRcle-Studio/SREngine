<p align="center">
 <h1 align="center">SpaRcle Engine</h2>
 <p align="center">Get dynamically generated GitHub stats on your READMEs!</p>
</p>
  <p align="center">
    <img alt="Project Status: Active – The project is under active delopment!." src="https://www.repostatus.org/badges/latest/active.svg" />
    <img alt="CodeFactor." src="https://www.codefactor.io/repository/github/sparcle-studio/srengine/badge/dev" />
    <img alt="GitHub Contributors." src="https://img.shields.io/github/contributors/SpaRcle-Studio/SREngine" />
    <img alt="Issues" src="https://img.shields.io/github/issues/SpaRcle-Studio/SREngine?color=0088ff" />
  </p>

SpaRcle Engine is an ongoing game engine developed in C++. 
It aims to establish a strong base for game creation and is currently in the early stages of development, emphasizing the creation of a versatile and efficient architecture.

## Screenshots

<img width="1920" alt="image_2023-05-31_21-40-59" src="https://github.com/Monika0000/SREngine/assets/47291246/6bf73c99-81a2-4a3e-ad28-4c788884eb38">
<img width="1920" alt="image_2023-05-31_21-40-59" src="https://github.com/Monika0000/SREngine/assets/47291246/32cfdbcb-5a0d-4a74-9501-539da40379e2">

## Supported compilers
- [x] MSVC (Stable)
- [x] MinGW
- [ ] Cygwin
- [x] Clang
- [ ] GCC

## Supported platforms
- [x] Windows 10
- [ ] Ubuntu
- [ ] Arch
- [ ] Redhat
- [ ] Android

## Branches 
 * master - branch for releases
 * dev - active development branch 
 * features/* - branches for new features
 * tmp/* - temporary branches for dangerous experiments

## Building  
 > [!IMPORTANT]
 > ```Requirements:```
 > - 0.1. Install Clion 2020.1 or newer / Visual Studio 2019 or newer
 > - 0.2. Install [Vulkan SDK/Runtime](https://vulkan.lunarg.com/sdk/home) 1.3.211.0
 > - 0.3. Install CMake 3.16.0
 > - 0.4. Install [MS Build Tools](https://download.visualstudio.microsoft.com/download/pr/996d318f-4bd0-4f73-8554-ea3ed556ce9b/9610a60ad452c33dd3f9e8d3b4ce5d88d278f8b063d88717e08e1c0c13c29233/vs_BuildTools.exe) for Visual Studio 16.11.29 (if you are using CLion)
 1. ```Clone repository via the command "git clone https://github.com/SpaRcle-Studio/SREngine"```
 2. ```Switch to the "dev" (or another one) branch via the command "git checkout branch_name"```
 3. ```Run command "git submodule update --init --recursive" in repository folder```
 <details>
 <summary> 4. Working with CMake (if you're using Visual Studio): </summary>
  
    - 4.1 Choose the path to the SREngine folder (where the source code is located).
  
    - 4.2 Choose the path where to build the binaries (SREngine/Build).
     
    - 4.3 Press "Configure" and choose your VS version.
    
    - 4.4 Press "Generate"
 </details>
 <details>
 <summary> 5. Working with CLion: </summary>
  
    - 5.1 Press Ctrl + Alt + S to open Settings window
    
    - 5.2. Select "Build, Execution, Deployment" on the left
    
    - 5.3. Select "Toolchains"
    
    - 5.4. Add (Alt + Insert) Visual Studio compiler
    
    - 5.5. Select amd64 in "Architecture:"
    
    - 5.6. Repeat 5.2
    
    - 5.7. Select "CMake"
    
    - 5.8. Pass "-j*" argument as "Build options", while * is a number of your logical processors minus 2
    
    - 5.9. In Project window right-click SREngine folder and click "Reload CMake Project"
    
    - 5.10. Click "Run 'SREngine'" (Shift + F10)
 </details>

## Used libraries
  * [ImGUI](https://github.com/ocornut/imgui)
  * [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
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
