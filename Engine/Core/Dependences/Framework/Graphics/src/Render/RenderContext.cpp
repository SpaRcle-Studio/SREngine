//
// Created by Monika on 18.07.2022.
//

#include <Render/RenderContext.h>
#include <Render/RenderScene.h>

#include <Types/Framebuffer.h>
#include <Types/Shader.h>
#include <Types/Texture.h>
#include <Types/RenderTexture.h>

namespace SR_GRAPH_NS {
    void RenderContext::Update() {
        SR_LOCK_GUARD

        /**
         * Все ресурсы при завершении работы рендера должны остаться только с одним use-point'ом.
         * В противном случае память никогда не освободится.
        */

        bool dirty = false;

        /// захватываем менеджер ресурсов, для выполнения синхронных операций
        SR_UTILS_NS::ResourceManager::LockSingleton();
        {
            dirty |= Update(m_framebuffers);
            dirty |= Update(m_textures);
            dirty |= Update(m_shaders);
        }
        SR_UTILS_NS::ResourceManager::UnlockSingleton();

        if (!dirty) {
            return;
        }

        for (auto&& scene : m_scenes) {
            scene->SetDirty();
        }
    }

    void RenderContext::Register(Types::Framebuffer *pFramebuffer) {
        SR_LOCK_GUARD
        pFramebuffer->AddUsePoint();
        m_framebuffers.emplace_front(pFramebuffer);
    }

    void RenderContext::Register(Types::Shader *pShader) {
        SR_LOCK_GUARD
        pShader->AddUsePoint();
        m_shaders.emplace_front(pShader);
    }

    void RenderContext::Register(Types::Texture *pTexture) {
        SR_LOCK_GUARD
        pTexture->AddUsePoint();
        m_textures.emplace_front(pTexture);
    }

    bool RenderContext::IsEmpty() const {
        SR_LOCK_GUARD
        return m_shaders.empty() && m_framebuffers.empty() && m_textures.empty();
    }
}
