//
// Created by Monika on 13.07.2022.
//

#ifndef SR_ENGINE_GRAPHICS_RENDER_CONTEXT_H
#define SR_ENGINE_GRAPHICS_RENDER_CONTEXT_H

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
    class Material;
}

namespace SR_GRAPH_NS {
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
       Materials,
       Skyboxes,
       ShadersGC,
       End
    );

    /**
     * Здесь хранятся все контекстные ресурсы.
     * Исключение - меши, потому что они могут быть в нескольких экземплярах.
     * Управлением памяти мешей занимается MeshCluster, который у каждой RenderScene свой.
     */
    class RenderContext : public SR_HTYPES_NS::SafePtr<RenderContext> {
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using PipelinePtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Pipeline>;
        using Super = SR_HTYPES_NS::SafePtr<RenderContext>;
        using MaterialPtr = SR_GTYPES_NS::Material*;
        using TexturePtr = SR_GTYPES_NS::Texture*;
        using SkyboxPtr = SR_GTYPES_NS::Skybox*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using WindowPtr = SR_HTYPES_NS::SafePtr<Window>;
        using RenderScenes = std::list<std::pair<SR_WORLD_NS::Scene::Ptr, RenderScenePtr>>;
    public:
        explicit RenderContext(const WindowPtr& pWindow);
        virtual ~RenderContext();

    public:
        void UpdateFramebuffers();

        void Update() noexcept;

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

        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD PipelinePtr GetPipeline() const;
        SR_NODISCARD WindowPtr GetWindow() const;
        SR_NODISCARD PipelineType GetPipelineType() const;
        SR_NODISCARD MaterialPtr GetDefaultMaterial() const;
        SR_NODISCARD MaterialPtr GetDefaultUIMaterial() const { return m_defaultUIMaterial; }
        SR_NODISCARD TexturePtr GetDefaultTexture() const;
        SR_NODISCARD TexturePtr GetNoneTexture() const;
        SR_NODISCARD ShaderPtr GetCurrentShader() const noexcept;
        SR_NODISCARD FramebufferPtr FindFramebuffer(const std::string& name) const;
        SR_NODISCARD FramebufferPtr FindFramebuffer(const std::string& name, CameraPtr pCamera) const;
        SR_NODISCARD SR_MATH_NS::UVector2 GetWindowSize() const;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Shader*>& GetShaders() const noexcept;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Framebuffer*>& GetFramebuffers() const noexcept;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Texture*>& GetTextures() const noexcept;
        SR_NODISCARD const std::vector<IRenderTechnique*>& GetRenderTechniques() const noexcept;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Material*>& GetMaterials() const noexcept;
        SR_NODISCARD const std::vector<SR_GTYPES_NS::Skybox*>& GetSkyboxes() const noexcept;
        SR_NODISCARD const RenderScenes& GetScenes() const noexcept { return m_scenes; }

        void SetCurrentShader(ShaderPtr pShader);

    private:
        bool InitPipeline();

        template<typename T> bool RegisterResource(T* pResource) {
            if (auto&& pGraphicsResource = dynamic_cast<Memory::IGraphicsResource*>(pResource)) {
                if (pGraphicsResource->GetRenderContext()) {
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
        std::vector<MaterialPtr> m_materials;
        std::vector<SkyboxPtr> m_skyboxes;

        RenderScenes m_scenes;

        WindowPtr m_window;

        MaterialPtr m_defaultUIMaterial = nullptr;
        MaterialPtr m_defaultMaterial = nullptr;
        TexturePtr m_defaultTexture = nullptr;
        TexturePtr m_noneTexture = nullptr;

        PipelinePtr m_pipeline = nullptr;

    };

    /// ------------------------------------------------------------------------------

    template<typename T> bool RenderContext::Update(T& resourceList) noexcept {
        SR_TRACY_ZONE;
        
        bool dirty = false;

        static auto&& freeVideoMemory = [](SR_UTILS_NS::IResource* pResource) {
            /// Ресурс необязательно имеет видеопамять, а лишь содержит другие ресурсы, например материал.
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
                        /// После освобождения ресурса необходимо перестроить все контекстные сцены рендера.
                        dirty |= true;
                        return true;
                    }

                    return false;
                });

                /// TODO: это безопасно?
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
