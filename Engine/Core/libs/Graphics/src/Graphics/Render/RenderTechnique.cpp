//
// Created by Monika on 17.07.2022.
//

#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Pass/GroupPass.h>

namespace SR_GRAPH_NS {
    RenderTechnique* RenderTechnique::Load(const SR_UTILS_NS::Path &rawPath) {
        SR_TRACY_ZONE;

        /// Данный ресурс может иметь копии

        auto&& path = SR_UTILS_NS::Path(rawPath).RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

        auto&& pRenderTechnique = new RenderTechnique();

        pRenderTechnique->SetId(path.ToStringRef(), false /** auto register */);

        if (!pRenderTechnique->Reload()) {
            SR_ERROR("RenderTechnique::Load() : failed to load render technique!\n\tPath: " + path.ToString());
            delete pRenderTechnique;
            return nullptr;
        }

        /// отложенная ручная регистрация
        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pRenderTechnique);

        return pRenderTechnique;
    }

    bool RenderTechnique::Load() {
        SetDirty();

        m_loadState = LoadState::Loading;

        return true;
    }

    bool RenderTechnique::Unload() {
        m_loadState = LoadState::Unloading;

        return Settings::Unload();
    }

    bool RenderTechnique::Build() {
        SR_TRACY_ZONE;

        /// Метод выполняется в графическом контексте

        if (m_hasErrors) {
            return false;
        }

        if (!m_dirty) {
            SRHalt("RenderTechnique::Build() : render technique isn't dirty!");
            return false;
        }

        /// Очишаем старые данные, если они были
        ClearSettings();

        /// Загружаем новые данные
        auto&& document = LoadDocument();
        if (!document.Valid()) {
            SR_ERROR("RenderTechnique::Build() : failed to load xml document!");
            m_loadState = LoadState::Error;
            return false;
        }

        if (auto&& settings = document.Root().GetNode("Technique")) {
            if (!LoadSettings(settings)) {
                SR_ERROR("RenderTechnique::Build() : failed to load render technique!");
                m_loadState = LoadState::Error;
                return false;
            }
        }
        else {
            SR_ERROR("RenderTechnique::Build() : \"Technique\" node not found!");
            m_loadState = LoadState::Error;
            return false;
        }

        SR_GRAPH_LOG("RenderTechnique::Build() : building \"" + std::string(GetName()) + "\" render technique...");

        /// Инициализируем все успешно загруженнеы проходы
        for (auto&& pPass : m_passes) {
            pPass->Init();
        }

        m_loadState = LoadState::Loaded;
        m_dirty = false;

        return true;
    }

    bool RenderTechnique::LoadSettings(const SR_XML_NS::Node &node) {
        SR_TRACY_ZONE;

        m_name = node.GetAttribute("Name").ToString();

        for (auto&& passNode : node.GetNodes()) {
            if (passNode.NameView() == "Queues") {
                for (auto&& queueNode : passNode.GetNodes()) {
                    auto&& queue = m_queues.emplace_back();
                    for (auto&& queuePassNode : queueNode.GetNodes()) {
                        auto&& name = queuePassNode.GetAttribute("Name").ToString();
                        if (auto&& pPass = FindPass(name)) {
                            queue.emplace_back(pPass);
                        }
                        else {
                            SR_ERROR("RenderTechnique::LoadSettings() : pass \"" + name + "\" for queue not found!");
                        }
                    }
                }
                continue;
            }

            if (auto&& pPass = SR_ALLOCATE_RENDER_PASS(passNode)) {
                pPass->SetRenderTechnique(this);
                m_passes.emplace_back(pPass);
            }
            else {
                SR_ERROR("RenderTechnique::LoadSettings() : failed to load \"" + passNode.Name() + "\" pass!");
            }
        }

        if (!m_passes.empty() && m_queues.empty()) {
            SR_ERROR("RenderTechnique::LoadSettings() : passes was loaded, but queue is empty!\n\tTechnique: " + GetResourcePath().ToStringRef());
            return false;
        }

        return true;
    }

    void RenderTechnique::ClearSettings() {
        SR_TRACY_ZONE;

        DeInitPasses();
        m_queues.clear();
        m_name.clear();
    }
}
