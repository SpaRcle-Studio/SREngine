# SpaRcle Engine Roadmap

=== "Roadmap"
    ??? engine "Engine"
        - [X] ECS and scenes
            * [X] EntityRef
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
        - [ ] Animations editor
    
    ??? scripting "Scripting"
        * [X] Serialization
        * [X] Flux Blueprints 
        * [X] C++ Engine API
        * [X] C++ Dynamic linking
        * [ ] C++ Static linking (in progress)
        * [ ] C++ Plugins
        * [ ] C++ Scripts compiler standardization (have problems with abi compatibility)
    
    ??? renderer "Render"
        - [X] Graphics API
            * [X] Vulkan
            * [X] WebGPU
            * [ ] DirectX (not planned in near future)
            * [ ] Metal (not planned in near future)
            * [ ] OpenGL (deprecated API)
            * [ ] WebGL (deprecated API)
        
        - [X] Animations
            * [X] Skeletal animations
            * [X] Animation blending (need to optimize)
            * [ ] Keyframe animations
    
        - [X] Shaders
            * [X] SpaRcle Shader Language (SRSL)
            * [X] Preprocessor and includes
            * [X] Vertex, Fragment, Compute shaders
            * [X] Shader hot-reloading and caching
            * [X] SSBO support
            * [X] Normal mapping
            * [ ] Tessellation and Geometry shaders
    
        - [X] UI
            * [X] Text rendering
                * [X] TTF fonts and colored emojis  
                * [X] SDF / MSDF / MSTDF support
                * [ ] Advanced text rendering (formatting)
            * [X] Sprite slicing
            * [X] Windows/Widgets
                * [X] Layout system
                * [X] Buttons
                * [X] Sliders
                * [X] Scroll areas
                * [ ] Input fields
                * [ ] Checkboxes
                * [ ] Docking
    
        - [X] Features
            * [X] Skybox 
            * [X] Custom render pipeline and custom passess
            * [X] Post-processing
            * [X] MSAA
            * [X] Multi-cameras rendering
            * [X] Bufferization
            * [X] Frustum culling
            * [X] Bloom
            * [X] SSAO
            * [X] Graphics settings
            * [X] Volumetric fog
            * [X] Volumetric clouds
            * [ ] Particle system (in progress)
            * [ ] SSR
            * [ ] PBR
            * [ ] Batched rendering
            * [ ] Multithreading rendering
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
        - [X] Raycasting
        - [ ] Soft bodies
        - [ ] Vehicles
        - [ ] Joints
        - [ ] Cloth simulation
        - [ ] Multithreading support
    
    
    ??? audio "Audio"
        - [X] OpenAL backend
        - [X] Audio sources
        - [X] Audio listener
        - [ ] Audio streaming
        - [ ] Audio effects (reverb, echo, etc.)
        - [ ] 3D audio occlusion
        - [ ] EFX support
    
    
    ??? android "Platforms"
        --8<-- "Documentation/Platforms.md"

=== "In develop"
    ## Our current active areas of development
    - Work on standardizing graphic settings
    - Linux wayland support
    - On UI system