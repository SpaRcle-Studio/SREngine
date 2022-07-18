//
// Created by Monika on 13.07.2022.
//

#ifndef SRENGINE_RENDERCONTEXT_H
#define SRENGINE_RENDERCONTEXT_H

#include <Render/MeshCluster.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
    class Shader;
    class Texture;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    /**
     * Здесь хранятся все контекстные ресурсы.
     * Исключение - меши, потому что они могут быть в нескольких экземплярах.
     * Управлением памяти мешей занимается MeshCluster, который у каждой RenderScene свой.
     */
    class RenderContext : public SR_UTILS_NS::NonCopyable {
    public:
        ~RenderContext() override = default;

    public:
        void Update();

        SR_NODISCARD bool IsEmpty() const;

    public:
        void Register(Types::Framebuffer* pFramebuffer);
        void Register(Types::Shader* pShader);
        void Register(Types::Texture* pTexture);

    private:
        template<typename T> bool Update(std::list<T>& resourceList);

    private:
        mutable std::recursive_mutex m_mutex;

        std::list<Types::Framebuffer*> m_framebuffers;
        std::list<Types::Shader*> m_shaders;
        std::list<Types::Texture*> m_textures;

        std::list<RenderScene*> m_scenes;

    };

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
                /// после освобождения ресурса необходимо перестроить сцену
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
