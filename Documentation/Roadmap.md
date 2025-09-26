# SpaRcle Engine Roadmap

??? engine "Engine"
    - [X] ECS and scenes
    - [X] Resource management
        * [X] Assets
        * [X] Resource hot-reloading
        * [ ] Asset libraries
        * [ ] Delayed resource loading
    - [X] Asset importing
        * [X] Textures (PNG, JPG)
        * [X] 3D Models (OBJ, FBX, BLEND)
        * [X] Audio (WAV, OGG, MP3)
        * [X] Fonts (TTF)
    - [X] Codegen and reflection system
    - [ ] Loading screen

??? editor "Editor"
    - [X] ImGUI editor (placeholder)
    - [X] Project creation  
    - [ ] Build exporting (planned)
    - [ ] Use own UI-system for editor

??? scripting "Scripting"
    - [X] Scripting
        * [X] Serialization
        * [X] C++ Engine API
        * [X] C++ Dynamic linking
        * [ ] C++ Static linking (planned)

??? renderer "Render"
    - [X] Graphics API
        * [X] Vulkan
        * [ ] OpenGL
        * [ ] WebGL (planned)
        * [ ] DirectX (not planned in near future)
        * [ ] Metal (not planned in near future)

    - [X] Shaders
        * [X] SpaRcle Shader Language (SRSL)
        * [X] Vertex, Fragment, Compute shaders
        * [X] Shader hot-reloading and caching
        * [X] Normal mapping
        * [X] Skeletal animation
        * [ ] Tessellation and Geometry shaders

    - [X] UI
        * [X] Text rendering
            * [X] TTF fonts and colored emojis  
            * [ ] Advanced text rendering (formatting)
        * [X] Sprite slicing
        * [ ] Windows/Widgets
            * [ ] Layout system
            * [ ] Buttons
            * [ ] Input fields
            * [ ] Sliders
            * [ ] Checkboxes
            * [ ] Scroll areas
            * [ ] Docking

    - [X] Features
        * [X] Skybox 
        * [X] Custom render pipeline
        * [X] Post-processing
        * [X] MSAA
        * [X] Multi-cameras rendering
        * [ ] Particle system (planned)
        * [ ] Bloom
        * [ ] SSAO
        * [ ] PBR
        * [ ] Batched rendering
        * [ ] Graphics settings
        * [X] Light system
            * [X] Cascaded shadow maps
            * [X] Directional lights
            * [ ] Point lights
            * [ ] Spot lights
            * [ ] Area lights   
            * [ ] Light probes
            

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


??? audio "Audio"
    - [X] OpenAL backend
    - [X] Audio sources
    - [X] Audio listener
    - [ ] Audio streaming
    - [ ] Audio effects (reverb, echo, etc.)
    - [ ] 3D audio occlusion
    - [ ] EFX support


???+ android "Platforms"
    --8<-- "Documentation/Platforms.md"