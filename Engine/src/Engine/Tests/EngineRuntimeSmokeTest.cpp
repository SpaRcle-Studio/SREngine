//
// Created by Monika on 29.11.2025.
//

#include <Engine/Tests/EngineRuntimeSmokeTest.h>
#include <Engine/LauncherEntryPoint.h>
#include <Engine/States/DelayedActionsState.h>
#include <Engine/Engine.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/SceneRunner.h>
#include <Engine/GUI/Hierarchy.h>

#include <Graphics/Window/Window.h>

#include <Scripting/Cpp/ScriptSystem.h>

#include <Utils/Types/Thread.h>

#include <Codegen/EngineRuntimeSmokeTest.generated.hpp>

namespace SR_CORE_NS::Tests {
    DelayedActionsState::Ptr EngineRuntimeSmokeTest::GetDelayedActionState(Launcher* pLauncher) {
        auto&& pWorker = pLauncher->GetEngine()->GetThreadsWorker();
        if (!pWorker) {
            SR_ERROR("EngineRuntimeSmokeTest::GetDelayedActionState() : failed to get ThreadsWorker from Engine!");
            m_hasErrors = true;
            pLauncher->Close();
            return nullptr;
        }

        auto&& pState = pWorker->GetWorkerState(DelayedActionsState::GetClassStaticName()).DynamicCast<DelayedActionsState>();
        if (!pState) {
            SR_ERROR("EngineRuntimeSmokeTest::GetDelayedActionState() : failed to get DelayedActionsState from ThreadsWorker!");
            m_hasErrors = true;
            pLauncher->Close();
            return nullptr;
        }

        return pState;
    };

    SR_UTILS_NS::TestExecutionResult EngineRuntimeSmokeTest::Run() {
        m_hasErrors = false;

        DelayedActionsState* pState = nullptr;
        Launcher* pLauncher = nullptr;
        std::atomic<bool> isStateReady = false;

        std::thread thread([this, &pState, &pLauncher, &isStateReady]() {
            auto&& callback = [this, &pState, &pLauncher, &isStateReady](SR_CORE_NS::Launcher::Ptr& pLauncherArg) {
                SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : launcher initialized successfully.");
                pState = GetDelayedActionState(pLauncherArg.Get()).Get();
                pLauncher = pLauncherArg.Get();
                isStateReady = true;
            };

            const int code = LauncherEntryPoint(callback);
            if (code != 0) {
                SR_ERROR("EngineRuntimeSmokeTest::Run() : launcherEntryPoint in thread returned non-zero code: {}", code);
                m_hasErrors = true;
            }
        });

        while (!isStateReady) {
            SR_PLATFORM_NS::Sleep(100);
        }

        if (m_hasErrors) {
            SR_ERROR("EngineRuntimeSmokeTest::Run() : test failed due to errors during execution.");
            return SpaRcle::Utils::TestExecutionResult::Error;
        }

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : DelayedActionsState is ready.");

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : waiting five seconds...");
        SR_PLATFORM_NS::Sleep(5000);

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : waiting for scripting system to become idle...");
        SR_SCRIPTING_NS::ScriptSystem::Instance().WaitForIdle();

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : first step - load demo scene");

        pState->AddEngineAction([this](Engine& engine) {
            SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : executing delayed action in DelayedActionsState - setting game mode.");
            engine.AddSceneToQueue(SR_WORLD_NS::Scene::LoadScene("ModuleTests/RuntimeSmokeTest/test.scene"));
        });

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : waiting five seconds...");
        SR_PLATFORM_NS::Sleep(5000);

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : second step - setting game mode");

        pState->AddEngineAction([this](Engine& engine) {
            SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : executing delayed action in DelayedActionsState - setting game mode.");
            if (auto&& pEditor = engine.GetEditor()) {
                if (auto&& pHierarchy = pEditor->GetWidget<SR_CORE_GUI_NS::Hierarchy>()) {
                    if (auto&& pSceneRunner = dynamic_cast<SR_CORE_GUI_NS::SceneRunner*>(pHierarchy->GetSceneRunnerWidget())) {
                        pSceneRunner->PlayScene();
                        engine.SetGameMode(true);
                        engine.SetActive(true);
                        return;
                    }
                }
            }
            SR_ERROR("EngineRuntimeSmokeTest::Run() : failed to set game mode - SceneRunner not found!");
            m_hasErrors = true;
        });

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : waiting five seconds...");
        SR_PLATFORM_NS::Sleep(5000);

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : third step - unsetting game mode");
        pState->AddEngineAction([this](Engine& engine) {
            SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : executing delayed action in DelayedActionsState - unsetting game mode.");
            if (auto&& pEditor = engine.GetEditor()) {
                if (auto&& pHierarchy = pEditor->GetWidget<SR_CORE_GUI_NS::Hierarchy>()) {
                    if (auto&& pSceneRunner = dynamic_cast<SR_CORE_GUI_NS::SceneRunner*>(pHierarchy->GetSceneRunnerWidget())) {
                        pSceneRunner->ReturnScene();
                        engine.SetGameMode(false);
                        engine.SetActive(false);
                        return;
                    }
                }
            }
            SR_ERROR("EngineRuntimeSmokeTest::Run() : failed to set game mode - SceneRunner not found!");
            m_hasErrors = true;
        });

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : waiting five seconds...");
        SR_PLATFORM_NS::Sleep(5000);

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : four step - closing launcher");
        pState->AddEngineAction([](Engine& engine) {
            SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : executing delayed action in DelayedActionsState - closing launcher.");
            engine.GetMainWindow()->Close();
        });

        SR_LOG_TEST("EngineRuntimeSmokeTest::Run() : waiting for thread to join...");
        thread.join();

        if (m_hasErrors) {
            SR_ERROR("EngineRuntimeSmokeTest::Run() : test failed due to errors during execution.");
            return SpaRcle::Utils::TestExecutionResult::Error;
        }

        return SpaRcle::Utils::TestExecutionResult::Success;
    }
}
