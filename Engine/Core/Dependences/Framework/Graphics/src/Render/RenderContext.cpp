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
            dirty |= Update(m_skyboxes);
            dirty |= Update(m_framebuffers);
            dirty |= Update(m_materials);
            dirty |= Update(m_textures);
            dirty |= Update(m_shaders);
        }
        SR_UTILS_NS::ResourceManager::UnlockSingleton();

        for (auto pIt = std::begin(m_scenes); pIt != std::end(m_scenes); ) {
            auto&& [pScene, pRenderScene] = *pIt;

            /// Нет смысла синхронизировать сцену рендера, так как она еще способна сама позаботиться о себе
            if (pScene.Valid()) {
                if (dirty) {
                    pRenderScene->SetDirty();
                }

                ++pIt;
                continue;
            }

            /// Синхронизируем и проверяем, есть ли еще на сцене объекты
            if (!pRenderScene.Do<bool>([](RenderScene* pRScene) -> bool {
                pRScene->Synchronize();
                return pRScene->IsEmpty();
            }, false)) {
                ++pIt;
                continue;
            }

            /// Как только уничтожается основная сцена, уничтожаем сцену рендера
            SR_LOG("RenderContext::Update() : destroy render scene...");
            pRenderScene.AutoFree([](RenderScene* ptr) {
                delete ptr;
            });
            pIt = m_scenes.erase(pIt);
        }
    }

    bool RenderContext::Init() {
        m_pipeline = Environment::Get();
        m_pipelineType = m_pipeline->GetPipeLine();

        /// ----------------------------------------------------------------------------

        Memory::TextureConfig config;

        config.m_format = ColorFormat::RGBA8_UNORM;
        config.m_filter = TextureFilter::NEAREST;
        config.m_compression = TextureCompression::None;
        config.m_mipLevels = 1;
        config.m_alpha = SR_UTILS_NS::BoolExt::None;
        config.m_cpuUsage = false;

        /// ----------------------------------------------------------------------------

        if ((m_defaultTexture = SR_GTYPES_NS::Texture::Load("Engine/Textures/default.png", config))) {
            m_defaultTexture->AddUsePoint();
        }
        else {
            SR_ERROR("RenderContext::Init() : failed to load default texture!")
        }

        /// ----------------------------------------------------------------------------

        /// так как вписать в код данные текстуры невозможно, то она хранится в виде base64, текстура размером 1x1 белого цвета формата png
        const std::string image = "iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAABmJLR0QA/wD/AP+gvaeTAAAADUlEQVQI12N48eIFOwAINALALwGcPAAAAABJRU5ErkJggg==";

        if ((m_noneTexture = SR_GTYPES_NS::Texture::LoadFromMemory(SR_UTILS_NS::StringUtils::Base64Decode(image), config))) {
            m_noneTexture->AddUsePoint();
        }
        else {
            SR_ERROR("RenderContext::Init() : failed to create none texture!")
            return false;
        }

        /// ----------------------------------------------------------------------------

        if ((m_defaultMaterial = SR_GTYPES_NS::Material::Load("Engine/Materials/default.mat"))) {
            m_defaultMaterial->AddUsePoint();
        }
        else {
            SR_ERROR("RenderContext::Init() : failed to load default material!");
        }

        /// ----------------------------------------------------------------------------

        return true;
    }

    void RenderContext::Close() {
        if (m_noneTexture) {
            m_noneTexture->RemoveUsePoint();
            m_noneTexture = nullptr;
        }

        if (m_defaultTexture) {
            m_defaultTexture->RemoveUsePoint();
            m_defaultTexture = nullptr;
        }

        if (m_defaultMaterial) {
            m_defaultMaterial->RemoveUsePoint();
            m_defaultMaterial = nullptr;
        }
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

    void RenderContext::Register(RenderContext::MaterialPtr pMaterial) {
        pMaterial->AddUsePoint();
        m_materials.emplace_front(pMaterial);
    }

    void RenderContext::Register(RenderContext::SkyboxPtr pSkybox) {
        pSkybox->AddUsePoint();
        m_skyboxes.emplace_front(pSkybox);
    }

    bool RenderContext::IsEmpty() const {
        return
            m_shaders.empty() &&
            m_framebuffers.empty() &&
            m_textures.empty() &&
            m_materials.empty() &&
            m_skyboxes.empty() &&
            m_scenes.empty() &&
            m_techniques.empty();
    }

    RenderContext::PipelinePtr RenderContext::GetPipeline() const {
        return m_pipeline;
    }

    PipeLineType RenderContext::GetPipelineType() const {
        return m_pipelineType;
    }

    RenderContext::MaterialPtr RenderContext::GetDefaultMaterial() const {
        return m_defaultMaterial;
    }

    void RenderContext::SetDirty() {
        for (auto&& [pScene, pRenderScene] : m_scenes) {
            pRenderScene.Do([](RenderScene* ptr) {
                ptr->SetDirty();
            });
        }
    }

    RenderContext::TexturePtr RenderContext::GetDefaultTexture() const {
        return m_defaultTexture ? m_defaultTexture : m_noneTexture;
    }

    RenderContext::TexturePtr RenderContext::GetNoneTexture() const {
        return m_noneTexture;
    }
}
