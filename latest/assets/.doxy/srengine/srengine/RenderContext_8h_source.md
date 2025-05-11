

# File RenderContext.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**RenderContext.h**](RenderContext_8h.md)

[Go to the documentation of this file](RenderContext_8h.md)


```C++
//
// Created by Monika on 13.07.2022.
//

#ifndef SR_ENGINE_GRAPHICS_RENDER_CONTEXT_H
#define SR_ENGINE_GRAPHICS_RENDER_CONTEXT_H

#include <Graphics/macros.h>

#include <Utils/World/Scene.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/SafePointer.h>

#include <Graphics/Render/MeshCluster.h>
#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
    class Shader;
    class Camera;
    class Texture;
    class Skybox;
}

namespace SR_GRAPH_NS {
    class BaseMaterial;
    class Window;
    class RenderScene;
    class IRenderTechnique;
    class Pipeline;

    SR_ENUM_NS_CLASS_T(RCUpdateQueueState, uint8_t,
       Begin = 0,
       Framebuffers,
       Shaders,
       Textures,
       Techniques,
       Skyboxes,
       End
    );

    class RenderContext : public SR_HTYPES_NS::SafePtr<RenderContext> {
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Pipeline>;
        using Super = SR_HTYPES_NS::SafePtr<RenderContext>;
        using MaterialPtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::BaseMaterial>;
        using TexturePtr = SR_GTYPES_NS::Texture*;
        using SkyboxPtr = SR_GTYPES_NS::Skybox*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using WindowPtr = SR_HTYPES_NS::SharedPtr<Window>;
        using RenderScenes = std::list<std::pair<SR_WORLD_NS::Scene::Ptr, RenderScenePtr>>;
    public:
        using Ptr = SR_HTYPES_NS::SafePtr<RenderContext>;

    public:
        RenderContext();
        virtual ~RenderContext();

    public:
        void SwitchWindow(WindowPtr pWindow);

        void PrepareFrame();

        bool Update() noexcept;

        bool Init();
        void Close();

        void SetDirty();

        void OnResize(const SR_MATH_NS::UVector2& size);
        void OnMultiSampleChanged();

    public:
        RenderScenePtr CreateScene(const SR_WORLD_NS::Scene::Ptr& scene);

        void Register(FramebufferPtr pFrameBuffer);
        void Register(SR_GTYPES_NS::Shader* pShader);
        void Register(SR_GTYPES_NS::Texture* pTexture);
        void Register(IRenderTechnique* pTechnique);
        void Register(MaterialPtr pMaterial);
        void Register(SkyboxPtr pSkybox);

        SR_NODISCARD bool IsOptimizedRenderUpdateEnabled() const noexcept { return m_isOptimizedUpdateEnabled; }
        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD bool IsDirty() const;
        SR_NODISCARD const RenderContext::PipelinePtr& GetPipeline() const;
        SR_NODISCARD RenderContext::PipelinePtr& GetPipeline();
        SR_NODISCARD WindowPtr GetWindow() const;
        SR_NODISCARD PipelineType GetPipelineType() const;
        SR_NODISCARD MaterialPtr GetDefaultMaterial() const;
        SR_NODISCARD MaterialPtr GetDefaultUIMaterial() const { return m_defaultUIMaterial; }
        SR_NODISCARD TexturePtr GetDefaultTexture() const;
        SR_NODISCARD TexturePtr GetNoneTexture() const;
        SR_NODISCARD ShaderPtr GetCurrentShader() const noexcept;
        SR_NODISCARD FramebufferPtr FindFramebuffer(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD FramebufferPtr FindFramebuffer(SR_UTILS_NS::StringAtom name, CameraPtr pCamera) const;
        SR_NODISCARD SR_MATH_NS::UVector2 GetWindowSize() const;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Shader*>& GetShaders() const noexcept;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Framebuffer*>& GetFramebuffers() const noexcept;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Texture*>& GetTextures() const noexcept;
        SR_NODISCARD const std::vector<IRenderTechnique*>& GetRenderTechniques() const noexcept;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Skybox*>& GetSkyboxes() const noexcept;
        SR_NODISCARD const RenderScenes& GetScenes() const noexcept { return m_scenes; }

        void SetOptimizedRenderUpdateEnabled(bool enabled) noexcept { m_isOptimizedUpdateEnabled = enabled; }
        bool SetCurrentShader(ShaderPtr pShader);
        void GarbageCollect() { m_isNeedGarbageCollection = true; }

    private:
        bool LoadDefaultResources();
        bool InitPipeline();

        template<typename T> bool RegisterResource(T* pResource) {
            SRAssert2(!m_isClosed, "RenderContext is closed");
            if (auto&& pGraphicsResource = dynamic_cast<Memory::IGraphicsResource*>(pResource)) {
                if (pGraphicsResource->GetRenderContext()) {
                    SRHalt("Resource already registered in some context!");
                    return false;
                }

                pGraphicsResource->SetRenderContext(this);
            }

            if (auto&& pIResource = dynamic_cast<SR_UTILS_NS::IResource*>(pResource)) {
                pIResource->AddUsePoint();
            }

            return true;
        }

        template<typename T> bool Update(T& resourceList) noexcept;

    private:
        RCUpdateQueueState m_updateState = RCUpdateQueueState::Begin;

        std::vector<SR_GTYPES_NS::Framebuffer*> m_framebuffers;
        std::vector<SR_GTYPES_NS::Shader*> m_shaders;
        std::vector<TexturePtr> m_textures;
        std::vector<IRenderTechnique*> m_techniques;
        std::vector<SkyboxPtr> m_skyboxes;

        RenderScenes m_scenes;

        WindowPtr m_window;

        MaterialPtr m_defaultUIMaterial = nullptr;
        MaterialPtr m_defaultMaterial = nullptr;
        TexturePtr m_defaultTexture = nullptr;
        TexturePtr m_noneTexture = nullptr;

        PipelinePtr m_pipeline = nullptr;

        bool m_isClosed = false;
        bool m_hasChangedFrameBuffers = false;

        bool m_isNeedGarbageCollection = false;
        bool m_isOptimizedUpdateEnabled = false;

    };


    template<typename T> bool RenderContext::Update(T& resourceList) noexcept {
        SR_TRACY_ZONE;
        
        bool dirty = false;

        static auto&& freeVideoMemory = [](SR_UTILS_NS::IResource* pResource) {
            if (auto&& pGraphicsResource = dynamic_cast<Memory::IGraphicsResource*>(pResource)) {
                pGraphicsResource->FreeVideoMemory();
                pGraphicsResource->DeInitGraphicsResource();
            }
        };

        for (auto pIt = std::begin(resourceList); pIt != std::end(resourceList); ) {
            auto&& pRenderResource = *pIt;

            auto&& pResource = dynamic_cast<SR_UTILS_NS::IResource*>(pRenderResource);

            if (pResource) {
                const bool removed = pResource->Execute([&]() -> bool {
                    if (pResource->GetCountUses() == 1) {
                        SRAssert(pResource->GetContainerParents().empty());

                        freeVideoMemory(pResource);

                        pResource->RemoveUsePoint();
                        pIt = resourceList.erase(pIt);
                        dirty |= true;
                        return true;
                    }

                    return false;
                });

                if (!removed) {
                    ++pIt;
                }
            }
            else {
                freeVideoMemory(pResource);
                ++pIt;
            }
        }

        return dirty;
    }
}

#endif //SR_ENGINE_GRAPHICS_RENDER_CONTEXT_H
```


