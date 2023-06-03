# SpaRcle Engine

<img width="1920" alt="image_2023-05-31_21-40-59" src="https://github.com/Monika0000/SREngine/assets/47291246/6bf73c99-81a2-4a3e-ad28-4c788884eb38">

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

## Building
 1. Clone repo 
 2. Run command "git submodule update --init --recursive"
 3. Install Clion 2020.1 / Visual Studio 2019
 4. Install [Vulkan SDK/Runtime](https://vulkan.lunarg.com/sdk/home) 1.3.211.0
 5. Install CMake 3.16.0
 6. Install [MS Build Tools](https://learn.microsoft.com/en-us/visualstudio/releases/2019/history) 14.29.30037 (if you using CLion) 
 7. Working with CMake (if you're using Visual Studio): 
    1. Choose the path to SREndine (Where the source code is).
    2. Choose the path where to build the binaries (SREngine/Build).
    3. Press Configure and choose your VS version.
    4. Press Generate
    5. Build and run Engine.exe with command line argument "-resources path-to-your-repository/Resources"
 8. Working with CLion: 
    1. Press Ctrl + Shift + S. 
    2. Build, Execution, Deployment -> Toolchains
    3. Add Visual Studio compiler
    4. Select architecture amd64
    5. Select SREngine folder and click "Reload CMake project"
    6. Click Run "SREngine" (Shift + F10)

## Used libraries
  * glm
  * OpenGL / GLFW / GLEW / glad
  * Bullet3
  * PhysX
  * Box2D
  * [ImGUI](https://github.com/ocornut/imgui)
  * [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
  * [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
  * [imgui-node-editor](https://github.com/thedmd/imgui-node-editor)
  * stbi
  * json
  * [EvoScript](https://github.com/Monika0000/EvoScript)
  * [EvoVulkan](https://github.com/Monika0000/EvoVulkan)
  * Assimp
  
  ## Features
  * SpaRcle Shader Language (SRSL)
  * Chunk system 
  * Render passes
  * Custom framebuffers
  * C++ scripting system
  * Animations 
  * Physics
  * Font renderer
  * Vulkan pipeline
  * Multi-cameras renderer 
  * Geometry loader
  * Texture loader
