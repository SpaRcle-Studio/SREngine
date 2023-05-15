# SpaRcle Engine

![image](https://user-images.githubusercontent.com/47291246/216782896-990a3a54-820d-49ec-aca0-f1ef992170ca.png)

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

## Building
 1. Install Clion 2020.1 / Visual Studio 2019
 2. Install [Vulkan SDK/Runtime](https://vulkan.lunarg.com/sdk/home) 1.3.211.0
 3. Install CMake 3.16.0
 4. Run command "git submodule update --init --recursive"
 5. Working with CMake (if you're using Visual Studio): 
    1. Choose the path to SREndine (Where the source code is).
    2. Choose the path where to build the binaries (SREngine/Build).
    3. Press Configure and choose your VS version.
    4. Press Generate
 6. Build and run Engine.exe with command line argument "-resources path-to-your-repository/Resources"

## Used libraries
  * glm
  * OpenGL / GLFW / GLEW / glad
  * Bullet3
  * [ImGUI](https://github.com/ocornut/imgui)
  * [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo)
  * [tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
  * [imgui-node-editor](https://github.com/thedmd/imgui-node-editor)
  * stbi
  * json
  * [EvoScript](https://github.com/Monika0000/EvoScript)
  * [EvoVulkan](https://github.com/Monika0000/EvoVulkan)
  * Assimp
  * PhysX
  * Box2D
  
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
