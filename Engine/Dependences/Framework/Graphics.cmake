
set(GRAPHICS_SRC
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Mesh.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Texture.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Material.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/WindowFormat.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Types/Skybox.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Loaders/ObjLoader.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Loaders/FbxLoader.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Loaders/ImageLoader.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Loaders/TextureLoader.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/Render.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/Shader.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/Camera.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Render/PostProcessing.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Lighting/Light.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Lighting/DirectionalLight.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Lighting/Spotlight.cpp
        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Lighting/PointLight.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Window/Window.cpp

        ${FRAMEWORK_ROOT_DIR}/Graphics/src/Environment/OpenGL.cpp
        )

set(GRAPHICS_INC_PUBLIC
        ${FRAMEWORK_ROOT_DIR}/Graphics/inc
        ${FRAMEWORK_ROOT_DIR}/Depends/inc
        ${FRAMEWORK_ROOT_DIR}/Depends/glew/include
        )

set(GRAPHICS_INC_PRIVATE

        )

set(GRAPHICS_INC_INSTANCE

        )
