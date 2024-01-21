#include <Utils/macros.h>

#include "../../Graphics/src/Graphics/Pipeline/TextureHelper.cpp"
#include "../../Graphics/src/Graphics/Pipeline/Pipeline.cpp"
#include "../../Graphics/src/Graphics/Pipeline/EmptyPipeline.cpp"
#include "../../Graphics/src/Graphics/Pipeline/FrameBufferQueue.cpp"

#include "../../Graphics/src/Graphics/Overlay/Overlay.cpp"

#include "../../Graphics/src/Graphics/Lighting/DirectionalLight.cpp"
#include "../../Graphics/src/Graphics/Lighting/ILightComponent.cpp"
#include "../../Graphics/src/Graphics/Lighting/PointLight.cpp"
#include "../../Graphics/src/Graphics/Lighting/SpotLight.cpp"
#include "../../Graphics/src/Graphics/Lighting/AreaLight.cpp"
#include "../../Graphics/src/Graphics/Lighting/ProbeLight.cpp"
#include "../../Graphics/src/Graphics/Lighting/LightSystem.cpp"

#include "../../Graphics/src/Graphics/Loaders/FbxLoader.cpp"
#include "../../Graphics/src/Graphics/Loaders/ImageLoader.cpp"
#include "../../Graphics/src/Graphics/Loaders/ObjLoader.cpp"
#include "../../Graphics/src/Graphics/Loaders/SRSL.cpp"
#include "../../Graphics/src/Graphics/Loaders/SRSLParser.cpp"
#include "../../Graphics/src/Graphics/Loaders/TextureLoader.cpp"
#include "../../Graphics/src/Graphics/Loaders/ShaderProperties.cpp"

#include "../../Graphics/src/Graphics/Memory/TextureConfigs.cpp"
#include "../../Graphics/src/Graphics/Memory/MeshManager.cpp"
#include "../../Graphics/src/Graphics/Memory/UBOManager.cpp"
#include "../../Graphics/src/Graphics/Memory/ShaderProgramManager.cpp"
#include "../../Graphics/src/Graphics/Memory/ShaderUBOBlock.cpp"
#include "../../Graphics/src/Graphics/Memory/CameraManager.cpp"
#include "../../Graphics/src/Graphics/Memory/IGraphicsResource.cpp"

#include "../../Graphics/src/Graphics/Font/Font.cpp"
#include "../../Graphics/src/Graphics/Font/FontLoader.cpp"
#include "../../Graphics/src/Graphics/Font/SDF.cpp"
#include "../../Graphics/src/Graphics/Font/ITextComponent.cpp"
#include "../../Graphics/src/Graphics/Font/Text2D.cpp"
#include "../../Graphics/src/Graphics/Font/Text3D.cpp"
#include "../../Graphics/src/Graphics/Font/TextBuilder.cpp"
#include "../../Graphics/src/Graphics/Font/Glyph.cpp"
#include "../../Graphics/src/Graphics/Font/FreeType.cpp"

#include "../../Graphics/src/Graphics/UI/Canvas.cpp"
#include "../../Graphics/src/Graphics/UI/Anchor.cpp"
#include "../../Graphics/src/Graphics/UI/Gizmo.cpp"

#include "../../Graphics/src/Graphics/Render/ScriptableRenderTechnique.cpp"
#include "../../Graphics/src/Graphics/Render/IRenderTechnique.cpp"
#include "../../Graphics/src/Graphics/Render/FlatCluster.cpp"
#include "../../Graphics/src/Graphics/Render/RenderScene.cpp"
#include "../../Graphics/src/Graphics/Render/RenderTechnique.cpp"
#include "../../Graphics/src/Graphics/Render/MeshCluster.cpp"
#include "../../Graphics/src/Graphics/Render/RenderContext.cpp"
#include "../../Graphics/src/Graphics/Render/SortedMeshQueue.cpp"
#include "../../Graphics/src/Graphics/Render/DebugRenderer.cpp"
#include "../../Graphics/src/Graphics/Render/RenderSettings.cpp"
#include "../../Graphics/src/Graphics/Render/RenderStrategy.cpp"

#include "../../Graphics/src/Graphics/Types/Geometry/DebugWireframeMesh.cpp"
#include "../../Graphics/src/Graphics/Types/Geometry/DebugLine.cpp"
#include "../../Graphics/src/Graphics/Types/Geometry/IndexedMesh.cpp"
#include "../../Graphics/src/Graphics/Types/Geometry/ProceduralMesh.cpp"
#include "../../Graphics/src/Graphics/Types/Geometry/Mesh3D.cpp"
#include "../../Graphics/src/Graphics/Types/Geometry/MeshComponent.cpp"
#include "../../Graphics/src/Graphics/Types/Geometry/SkinnedMesh.cpp"
#include "../../Graphics/src/Graphics/Types/Geometry/Sprite.cpp"

#include "../../Graphics/src/Graphics/Types/IRenderComponent.cpp"
#include "../../Graphics/src/Graphics/Types/EditorGrid.cpp"
#include "../../Graphics/src/Graphics/Types/Framebuffer.cpp"
#include "../../Graphics/src/Graphics/Types/Material.cpp"
#include "../../Graphics/src/Graphics/Types/Mesh.cpp"
#include "../../Graphics/src/Graphics/Types/Skybox.cpp"
#include "../../Graphics/src/Graphics/Types/Texture.cpp"
#include "../../Graphics/src/Graphics/Types/GraphicsCommand.cpp"
#include "../../Graphics/src/Graphics/Types/Camera.cpp"
#include "../../Graphics/src/Graphics/Types/Shader.cpp"
#include "../../Graphics/src/Graphics/Types/RenderTexture.cpp"

#include "../../Graphics/src/Graphics/Utils/MeshUtils.cpp"

#include "../../Graphics/src/Graphics/Window/Window.cpp"
#include "../../Graphics/src/Graphics/Window/BasicWindowImpl.cpp"

#if defined(SR_USE_IMGUI)
    #include "../../Graphics/src/Graphics/Overlay/ImGuiOverlay.cpp"
#endif

#if defined(SR_USE_VULKAN)
    #include "../../Graphics/src/Graphics/Pipeline/Vulkan/VulkanPipeline.cpp"
    #include "../../Graphics/src/Graphics/Pipeline/Vulkan/VulkanMemory.cpp"
    #include "../../Graphics/src/Graphics/Pipeline/Vulkan/VulkanKernel.cpp"

    #if defined(SR_LINUX)
        #include "../../Graphics/src/Graphics/Pipeline/Vulkan/X11SurfaceInit.cpp"
    #endif

    #if defined(SR_USE_IMGUI)
        #include "../../Graphics/src/Graphics/Overlay/VulkanImGuiOverlay.cpp"
    #endif

    #if defined(SR_TRACY_ENABLE)
        #include "../../Graphics/src/Graphics/Pipeline/Vulkan/VulkanTracy.cpp"
    #endif
#endif

#if defined(SR_WIN32)
    #include "../../Graphics/src/Graphics/Window/Win32Window.cpp"
#endif

#if defined(SR_ANDROID)
    #include "../../Graphics/src/Graphics/Window/AndroidWindow.cpp"
#endif

#if defined(SR_LINUX)
    #include "../../Graphics/src/Graphics/Window/X11Window.cpp"
#endif