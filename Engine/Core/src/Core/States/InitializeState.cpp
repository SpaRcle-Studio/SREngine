//
// Created by Monika on 13.04.2024.
//

#include <Core/States/InitializeState.h>

#include <Graphics/Render/RenderContext.h>
#include <Graphics/Window/Window.h>

#include <Core/Engine.h>
#include <Core/GUI/EditorGUI.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult InitializeState::ExecuteImpl() {
        if (m_isInitialized) {
            return SR_UTILS_NS::ThreadWorkerResult::Success;
        }

        auto&& pEngine = GetContext().GetPointer<Engine>();
        auto&& pRenderContext = pEngine->GetRenderContext();

        auto&& pWindow = pEngine->GetMainWindow();
        auto&& pWindowImpl = pWindow ? pWindow->GetImplementation<SR_GRAPH_NS::BasicWindowImpl>() : nullptr;

        if (pWindow && pWindowImpl) {
            if (!pWindow->Open()) {
                SR_ERROR("Engine::InitializeRender() : failed to open the main window!");
                GetThreadsWorker()->StopAsync();
                return SR_UTILS_NS::ThreadWorkerResult::Break;
            }

            auto&& cachePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
            auto&& windowSettingsPath = cachePath.Concat("WindowSettings.xml");

            const bool windowSettingsExist = windowSettingsPath.Exists();

            if (windowSettingsExist) {
                auto&& windowSettings = SR_XML_NS::Document::Load(windowSettingsPath);

                auto&& rootNode = windowSettings.Root().TryGetNode("Settings");

                auto&& resolution = rootNode.TryGetNode("Size").TryGetAttribute<SR_MATH_NS::UVector2>(0);
                auto&& position = rootNode.TryGetNode("Position").TryGetAttribute<SR_MATH_NS::IVector2>(0);
                const bool isMaximized = rootNode.GetAttribute("IsMaximized").ToBool(false);

                pWindowImpl->Move(position.x, position.y);

                if (isMaximized) {
                    pWindowImpl->Maximize();
                }
            }
            else {
                pWindowImpl->Centralize();
            }

            pRenderContext->SwitchWindow(pWindow);
        }

        if (!SR_THIS_THREAD) {
            SR_ERROR("Engine::InitializeRender() : this thread is nullptr!");
            GetThreadsWorker()->StopAsync();
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        SR_THIS_THREAD->GetContext()->SetValue<SR_GRAPH_NS::RenderContext::Ptr>(pRenderContext);

        if (!pRenderContext) {
            SR_ERROR("Engine::InitializeRender() : failed to get render context!");
            GetThreadsWorker()->StopAsync();
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        if (!pRenderContext->Init()) {
            SR_ERROR("Engine::InitializeRender() : failed to initialize the render context!");
            GetThreadsWorker()->StopAsync();
            return SR_UTILS_NS::ThreadWorkerResult::Break;
        }

        if (auto&& pEditor = pEngine->GetEditor(); pEditor && pEditor->Enabled()) {
            pEditor->Init();
        }

        m_isInitialized = true;

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }

    void InitializeState::FinalizeImpl() {
        auto&& pEngine = GetContext().GetPointer<Engine>();

        if (auto&& pWindow = pEngine->GetMainWindow()) {
            auto&& cachePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
            auto&& windowSettingsPath = cachePath.Concat("WindowSettings.xml");

            auto&& windowSettings = SR_XML_NS::Document::New();
            auto&& rootNode = windowSettings.Root().AppendNode("Settings");

            if (!pWindow->GetSize().HasZero()) {
                rootNode.AppendNode("Size").AppendAttribute(pWindow->GetSize());
            }

            rootNode.AppendNode("Position").AppendAttribute(pWindow->GetPosition());
            rootNode.AppendAttribute("IsMaximized", pWindow->IsMaximized());

            windowSettings.Save(windowSettingsPath);
        }

        if (auto&& pEditor = pEngine->GetEditor(); pEditor && pEditor->IsInitialized()) {
            pEditor->DeInit();
        }

        pEngine->SetScene(SR_WORLD_NS::Scene::Ptr());

        do {
            SR_INFO("InitializeState::Finalize() : flushing scene...");
        }
        while (pEngine->FlushScene());

        auto&& pRenderContext = pEngine->GetRenderContext();
        if (pRenderContext) {
            pRenderContext->Close();
        }
    }
}