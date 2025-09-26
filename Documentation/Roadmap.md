# SpaRcle Engine Roadmap


??? editor "Editor"
    - [X] ImGUI editor
    - [X] Project creation  
    - [ ] Build exporting (planned)
    - [ ] Use own UI-system for editor

??? scripting "Scripting"
    - [X] Scripting
        * [X] C++ Engine API
        * [X] C++ Dynamic linking
        * [ ] C++ Static linking (planned)

??? renderer "Render"
    - [X] Graphics API
        * [X] Vulkan
        * [ ] OpenGL
        * [ ] WebGL (planned)
        * [ ] DirectX (never)
        * [ ] Metal (not planned in near future)

    - [X] Shaders
        * [X] SpaRcle Shader Language (SRSL)
        * [X] Vertex, Fragment, Compute shaders
        * [X] Shader hot-reloading and caching
        * [X] Normal mapping
        * [X] Skeletal animation
        * [ ] Tessellation and Geometry shaders

    - [X] Features
        * [X] Cascaded shadow maps
        * [X] Skybox 
        * [X] Custom render pipeline
        * [X] Post-processing
        * [X] MSAA
        * [X] Multi-cameras rendering
        * [ ] Particle system (planned)
        * [ ] Bloom
        * [ ] SSAO
        * [ ] PBR

??? physics "Physics"
    - [X] Basic collision detection
    - [X] Rigid bodies
    - [X] Physics materials
    - [X] Physics debugging visualization
    - [ ] Soft bodies
    - [ ] Vehicles
    - [ ] Joints
    - [ ] Cloth simulation
    - [ ] Raycasting
    - [ ] Multithreading support


???+ android "Platforms"
    --8<-- "Documentation/Platforms.md"