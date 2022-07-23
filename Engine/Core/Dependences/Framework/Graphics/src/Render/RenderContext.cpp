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
    RenderContext::RenderContext()
        : Super(this)
    { }

    void RenderContext::Update() {
        /**
         * Все ресурсы при завершении работы рендера должны остаться только с одним use-point'ом.
         * В противном случае память никогда не освободится.
        */

        bool dirty = false;

        /// захватываем менеджер ресурсов, для выполнения синхронных операций
        SR_UTILS_NS::ResourceManager::LockSingleton();
        {
            dirty |= Update(m_techniques);
            dirty |= Update(m_framebuffers);
            dirty |= Update(m_textures);
            dirty |= Update(m_shaders);
        }
        SR_UTILS_NS::ResourceManager::UnlockSingleton();

        for (auto pIt = std::begin(m_scenes); pIt != std::end(m_scenes); ) {
            auto&& [pScene, pRenderScene] = *pIt;

            /// Если на сцене все еще есть объекты или технология рендера
            if (!pRenderScene.Do<bool>([](RenderScene* pRScene) -> bool { return pRScene->IsEmpty(); }, false)) {
                ++pIt;
                continue;
            }

            /// Как только уничтожается основная сцена, уничтожаем сцену рендера
            if (!pScene.Valid()) {
                SR_LOG("RenderContext::Update() : destroy render scene...");
                pRenderScene.AutoFree([](RenderScene* ptr) {
                    delete ptr;
                });
                pIt = m_scenes.erase(pIt);
                continue;
            }

            if (dirty) {
                pRenderScene->SetDirty();
            }

            ++pIt;
        }
    }

    bool RenderContext::Init() {
        m_pipeline = Environment::Get();
        m_pipelineType = m_pipeline->GetPipeLine();
        return true;
    }

    RenderContext::RenderScenePtr RenderContext::CreateScene(const SR_WORLD_NS::Scene::Ptr &scene) {
        RenderScenePtr pRenderScene;

        if (scene.RecursiveLockIfValid()) {
            auto&& dataStorage = scene->GetDataStorage();

            /// У каждой сцены может быть только одна сцена рендера
            if (dataStorage.GetPointerDef<RenderScene>(nullptr)) {
                SR_ERROR("RenderContext::CreateScene() : render scene is already exists!");
                scene.Unlock();
                return pRenderScene;
            }

            pRenderScene = new RenderScene(scene, this);

            m_scenes.emplace_back(std::make_pair(
                scene,
                pRenderScene
            ));

            dataStorage.SetValue<RenderScenePtr>(pRenderScene);
            scene.Unlock();
        }
        else {
            SR_ERROR("RenderContext::CreateScene() : scene is invalid!");
        }

        return pRenderScene;
    }

    void RenderContext::Register(Types::Framebuffer *pFramebuffer) {
        pFramebuffer->AddUsePoint();
        m_framebuffers.emplace_front(pFramebuffer);
    }

    void RenderContext::Register(Types::Shader *pShader) {
        pShader->AddUsePoint();
        m_shaders.emplace_front(pShader);
    }

    void RenderContext::Register(Types::Texture *pTexture) {
        pTexture->AddUsePoint();
        m_textures.emplace_front(pTexture);
    }

    void RenderContext::Register(RenderTechnique *pTechnique) {
        pTechnique->AddUsePoint();
        m_techniques.emplace_front(pTechnique);
    }

    bool RenderContext::IsEmpty() const {
        return
            m_shaders.empty() &&
            m_framebuffers.empty() &&
            m_textures.empty() &&
            m_scenes.empty() &&
            m_techniques.empty();
    }

    RenderContext::PipelinePtr RenderContext::GetPipeline() const {
        return Environment::Get();
    }
}
