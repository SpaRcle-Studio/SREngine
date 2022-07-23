//
// Created by Monika on 13.07.2022.
//

#ifndef SRENGINE_RENDERCONTEXT_H
#define SRENGINE_RENDERCONTEXT_H

#include <Render/MeshCluster.h>
#include <Utils/World/Scene.h>
#include <Utils/Types/SafePointer.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
    class Shader;
    class Texture;
    class Skybox;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderTechnique;
    class Environment;

    /**
     * Здесь хранятся все контекстные ресурсы.
     * Исключение - меши, потому что они могут быть в нескольких экземплярах.
     * Управлением памяти мешей занимается MeshCluster, который у каждой RenderScene свой.
     */
    class RenderContext : public SR_HTYPES_NS::SafePtr<RenderContext> {
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using PipelinePtr = Environment*;
        using Super = SR_HTYPES_NS::SafePtr<RenderContext>;
    public:
        RenderContext();
        virtual ~RenderContext() = default;

    public:
        void Update();

    public:
        bool Init();

        RenderScenePtr CreateScene(const SR_WORLD_NS::Scene::Ptr& scene);

        void Register(Types::Framebuffer* pFramebuffer);
        void Register(Types::Shader* pShader);
        void Register(Types::Texture* pTexture);
        void Register(RenderTechnique* pTechnique);

        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD PipelinePtr GetPipeline() const;

    private:
        template<typename T> bool Update(std::list<T>& resourceList);

    private:
        std::list<Types::Framebuffer*> m_framebuffers;
        std::list<Types::Shader*> m_shaders;
        std::list<Types::Texture*> m_textures;
        std::list<RenderTechnique*> m_techniques;

        std::list<std::pair<SR_WORLD_NS::Scene::Ptr, RenderScenePtr>> m_scenes;

        PipelinePtr m_pipeline = nullptr;
        PipeLineType m_pipelineType = PipeLineType::Unknown;

    };

    /// ------------------------------------------------------------------------------

    template<typename T> bool RenderContext::Update(std::list<T> &resourceList) {
        bool dirty = false;

        for (auto pIt = std::begin(resourceList); pIt != std::end(resourceList); ) {
            auto&& pResource = *pIt;

            if (pResource->GetCountUses() == 1) {
                pResource->FreeVideoMemory();
                /// Сперва ставим ресурс на уничтожение
                pResource->Destroy();
                /// Затем убираем use-point, чтобы его можно было синхронно освободить.
                /// Иначе ресурс может дважды уничтожиться.
                pResource->RemoveUsePoint();
                pIt = resourceList.erase(pIt);
                /// После освобождения ресурса необходимо перестроить все контекстные сцены рендера.
                dirty |= true;
            }
            else {
                ++pIt;
            }
        }

        return dirty;
    }
}

#endif //SRENGINE_RENDERCONTEXT_H
