# SpaRcle Engine

## Supported compilers
- [x] MSVC
- [x] MinGW
- [ ] Cygwin
- [ ] Clang
- [ ] GCC

## Supported platforms
- [x] Windows 10
- [ ] Ubuntu
- [ ] Arch
- [ ] Redhat
- [ ] Android

## Building
 1. Install [Vulkan SDK/Runtime](https://vulkan.lunarg.com/sdk/home)
 2. Install Cmake 
 3. Run command "git submodule update --init --recursive"
 4. Add command argument "-resources path-to-our-repository/Resources"

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

## Exists systems
  * Types
      * Thread - обертка над стандартным классом, с некоторыми дополнениями
      * SafePtr - универсальный умный указатель, обеспечивает сохранность данных в многопоточной среде
      * Singleton
  * Math
      * Quaternion
      * Vector3
      * Vector2
      * Matrix4x4
  * Graphics
      * Node editor
      * Mesh-cluster
      * GUI 
      * OBJ-loader
      * FBX-loader
      * Texturing
        * Compressing BC1-BC7 (Only Vulkan)
      * Shaders
      * Materials
      * PostProcessing
        * Saturation (Only OpenGL)
        * Bloom (Slow) (Only OpenGL)
        * Color correction (Base) (Only OpenGL)
  * Physics (Не начато)
      * Rigidbody (Base component)
  * Scripting (Полностью сделано через EvoScript)
  * Audio (Не начато)
  * World
      * Scene 
      * GameObject (Используется частично паттерн ECS)
         * Transform
         * Hierarchy-transformation (80%)
         * Component
      * Chunk-System - чанковая система, которая разбивает мир на чанки и регионы, позволяя удаляться на огромные расстояния от центра мира без каких либо артефактов, производя для этого "сдвиги"
  * Input system (Только стандартый ввод Windows)
  * Memory management
      * ResourceManager
      * IResource - interface for control resource units
  * Debug and logging
  * Command Manager
 
## Editor
  * Grid (Only OpenGL)
  * Manipulation tools
  * Inspector 
  * Hierarchy
  * Asset explorer
  * World edit
  * Visual Evo Script
