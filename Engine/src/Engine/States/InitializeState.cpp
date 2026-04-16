//
// Created by Monika on 13.04.2024.
//

#include <Engine/States/InitializeState.h>
#include <Engine/Engine.h>
#include <Engine/GUI/EditorGUI.h>

#include <Graphics/Render/RenderContext.h>
#include <Graphics/Window/Window.h>
#include <Graphics/Window/BasicWindowImpl.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/Common/StoreUtils.h>

#include <Codegen/InitializeState.generated.hpp>

namespace SR_CORE_NS {
    SR_UTILS_NS::ThreadWorkerResult InitializeState::ExecuteImpl() {
        if (m_isInitialized) {
            return SR_UTILS_NS::ThreadWorkerResult::Success;
        }

        auto&& pEngine = GetContext().GetPointer<Engine>();
        auto&& pRenderContext = pEngine->GetRenderContext();
        if (pRenderContext->GetPipeline() && pRenderContext->GetPipeline()->IsAsyncEarlyInit()) {
            SR_LOG("InitializeState::Execute() : waiting for async early initialization of the render pipeline...");
            SR_PLATFORM_NS::Sleep(100);
            return SR_UTILS_NS::ThreadWorkerResult::Repeat;
        }

        auto&& pWindow = pEngine->GetMainWindow();
        auto&& pWindowImpl = pWindow ? pWindow->GetImplementation<SR_GRAPH_NS::BasicWindowImpl>() : nullptr;

        if (pWindow && pWindowImpl && !m_windowInititalized) {
            if (!pWindow->Open()) {
                SR_ERROR("Engine::InitializeRender() : failed to open the main window!");
                GetThreadsWorker()->StopAsync();
                return SR_UTILS_NS::ThreadWorkerResult::Break;
            }

            const auto resolution = SR_MATH_NS::UVector2(
                SR_UTILS_NS::StoreUtils::User::GetInt("MainWindowWidth", 0),
                SR_UTILS_NS::StoreUtils::User::GetInt("MainWindowHeight", 0)
            );

            const auto position = SR_MATH_NS::IVector2(
                SR_UTILS_NS::StoreUtils::User::GetInt("MainWindowPosX", SR_INT32_MAX),
                SR_UTILS_NS::StoreUtils::User::GetInt("MainWindowPosY", SR_INT32_MAX)
            );

            if (!resolution.HasZero() && position.x != SR_INT32_MAX && position.y != SR_INT32_MAX) {
                const bool isMaximized = SR_UTILS_NS::StoreUtils::User::GetBool("MainWindowIsMaximized", false);

                pWindowImpl->Move(position.x, position.y);
                pWindowImpl->Resize(resolution.x, resolution.y);

                if (isMaximized) {
                    pWindowImpl->Maximize();
                }
            }
            else {
                pWindowImpl->Centralize();
            }

            pRenderContext->SwitchWindow(pWindow);

            m_windowInititalized = true;
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

        pEngine->LoadStartupScene();

        m_isInitialized = true;

        return SR_UTILS_NS::ThreadWorkerResult::Success;
    }

    void InitializeState::FinalizeImpl() {
        auto&& pEngine = GetContext().GetPointer<Engine>();

        if (auto&& pWindow = pEngine->GetMainWindow()) {
            auto&& cachePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();

            if (!pWindow->GetSize().HasZero()) {
                SR_UTILS_NS::StoreUtils::User::SetInt("MainWindowWidth", pWindow->GetSize().x);
                SR_UTILS_NS::StoreUtils::User::SetInt("MainWindowHeight", pWindow->GetSize().y);
            }

            SR_UTILS_NS::StoreUtils::User::SetInt("MainWindowPosX", pWindow->GetPosition().x);
            SR_UTILS_NS::StoreUtils::User::SetInt("MainWindowPosY", pWindow->GetPosition().y);
            SR_UTILS_NS::StoreUtils::User::SetBool("MainWindowIsMaximized", pWindow->IsMaximized());

            SR_UTILS_NS::StoreUtils::Storage::Instance().Save();
        }

        if (auto&& pEditor = pEngine->GetEditor(); pEditor && pEditor->IsInitialized()) {
            pEditor->DeInit();
        }

        pEngine->AddSceneToQueue(SR_WORLD_NS::Scene::Ptr());

        do {
            SR_INFO("InitializeState::Finalize() : flushing scene...");
        }
        while (pEngine->FlushScene());

        pEngine->DestroyEditor();

        auto&& pRenderContext = pEngine->GetRenderContext();
        if (pRenderContext) {
            pRenderContext->Close();
        }
    }
}