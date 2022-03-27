
if (CYGWIN)
    #include_directories("$ENV{VULKAN_SDK}/Include")
else()
    include_directories(${Vulkan_INCLUDE_DIRS})
    find_package(Vulkan REQUIRED FATAL_ERROR)
endif()

set(GRAPHICS_SRC
        ${FRAMEWORK_ROOT_DIR}/Unity/Graphics.cxx
        ${FRAMEWORK_ROOT_DIR}/Unity/ImGUI.cxx

        #[[{FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Geometry/Mesh3D.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Geometry/DebugWireframeMesh.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Geometry/IndexedMesh.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Mesh.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Texture.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Material.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/WindowFormat.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Skybox.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/EditorGrid.cpp

        #${FRAMEWORK_ROOT_DIR}/Graphics/src/Animations/Bone.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Memory/MeshManager.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Loaders/ObjLoader.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Loaders/ImageLoader.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Loaders/TextureLoader.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/ShaderGenerator.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/Render.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/Shader.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/Camera.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/PostProcessing.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/ColorBuffer.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/MeshCluster.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Lighting/Light.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Lighting/DirectionalLight.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Lighting/Spotlight.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Lighting/PointLight.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Window/Window.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/GUI/ICanvas.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/GUI/old/GUIWindow.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/GUI/old/DockSpace.cpp

        #${FRAMEWORK_ROOT_DIR}/Graphics/src/Environment/Environment.cpp
        #${FRAMEWORK_ROOT_DIR}/Graphics/src/Environment/TextureHelper.cpp
        #${FRAMEWORK_ROOT_DIR}/Graphics/src/Environment/OpenGL.cpp
        #${FRAMEWORK_ROOT_DIR}/Graphics/src/Environment/Vulkan.cpp
        #${FRAMEWORK_ROOT_DIR}/Graphics/src/Environment/Vulkan/VulkanMemory.cpp
        #${FRAMEWORK_ROOT_DIR}/Graphics/src/Environment/Vulkan/VulkanImGUI.cpp

        ############################################################

        #${FRAMEWORK_ROOT_DIR}/Depends/imgui/imgui.cpp
        #${FRAMEWORK_ROOT_DIR}/Depends/imgui/imgui_draw.cpp
        #${FRAMEWORK_ROOT_DIR}/Depends/imgui/imgui_widgets.cpp
        #${FRAMEWORK_ROOT_DIR}/Depends/imgui/imgui_tables.cpp

        #${FRAMEWORK_ROOT_DIR}/Depends/imgui/backebds/imgui_impl_allegro5.cpp
        #${FRAMEWORK_ROOT_DIR}/Depends/imgui/backebds/imgui_impl_dx9.cpp
        #${FRAMEWORK_ROOT_DIR}/Depends/imgui/backebds/imgui_impl_dx10.cpp
        #${FRAMEWORK_ROOT_DIR}/Depends/imgui/backebds/imgui_impl_dx11.cpp]]
        )

set(GRAPHICS_INC_PUBLIC
        ${FRAMEWORK_ROOT_DIR}/Graphics/inc
        ${FRAMEWORK_ROOT_DIR}/Depends/inc
        ${FRAMEWORK_ROOT_DIR}/Depends/EvoVulkan/Core/inc
        ${FRAMEWORK_ROOT_DIR}/Depends/cmp_core/source

        ${FRAMEWORK_ROOT_DIR}/Depends/glew/include
        ${FRAMEWORK_ROOT_DIR}/Depends/FbxLoader/inc
        #${FRAMEWORK_ROOT_DIR}/Depends/tinyobjloader/inc

        ${Vulkan_INCLUDE_DIRS}
        )

set(GRAPHICS_INC_PRIVATE

        )

set(GRAPHICS_INC_INSTANCE

        )

