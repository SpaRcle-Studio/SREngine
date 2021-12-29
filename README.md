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

## Used libraries
  * glm
  * OpenGL / GLFW / GLEW / glad
  * Bullet3
  * ImGUI
  * tinyobjloader
  * stbi
  * json
  * EvoScript
  * EvoVulkan

## Exists systems
  * Math
      * Quaternion
      * Vector3
      * Vector2
      * Matrix4x4
  * Graphics
      * Mesh render
      * GUI 
      * OBJ-loader
      * Texturing
        * Compressing BC1-BC7
      * Shaders
      * Materials
      * PostProcessing
        * Saturation
        * Bloom (Slow)
        * Color correction (Base)
  * Physics
      * Rigidbody (Base component)
  * Scripting
  * Audio
  * ECS
      * Scene 
      * GameObject
         * Transform
         * Hierarchy-transformation (80%)
      * Component
  * Input system
  * Memory management
      * IResource - interface for control resource units
  * Debug and logging
 
## Editor
  * Grid
  * Manipulation tools
  * Inspector 
  * Hierarchy (70%)
  * Render settings
