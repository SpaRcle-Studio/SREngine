//
// Created by innerviewer on 2024-03-18.
//

#include <Core/Tests/TestManager.h>
#include <Utils/Platform/Platform.h>
#include <Core/Launcher.h>

namespace SR_CORE_NS {
    void TestManager::RunAll(int argc, char** argv) {
        int32_t successes = 0;

        for (auto&& test : m_tests) {
            if (RunTest(test)) {
                successes++;
            }
        }

        if (m_engineTests.empty()) {
            if (m_tests.empty()) {
                SR_PLATFORM_NS::WriteConsoleLog("TestManager::RunAll() : no tests to run!\n");
            } else {
                SR_PLATFORM_NS::WriteConsoleLog(SR_FORMAT("TestManager::RunAll() : unit tests passed: {}/{}.", successes, m_tests.size()));
            }
            return;
        }

        SR_HTYPES_NS::SharedPtr pLauncher = new SR_CORE_NS::Launcher();
        auto&& launcherInitStatus = pLauncher->InitLauncher(argc, argv);

        if (launcherInitStatus == SR_CORE_NS::LauncherInitStatus::Error) {
            SR_PLATFORM_NS::WriteConsoleError("TestManager::RunAll() : failed to initialize launcher!\n");
            return;
        }

        if (launcherInitStatus == SR_CORE_NS::LauncherInitStatus::Unpacking) {
            SR_PLATFORM_NS::WriteConsoleError("TestManager::RunAll() : run the application at least once without tests!\n");
            return;
        }

        if (!pLauncher->EarlyInit()) {
            SR_ERROR("TestManager::RunAll() : failed to early initialize application!");
            return;
        }

        if (!pLauncher->Init()) {
            SR_ERROR("TestManager::RunAll() : failed to initialize application!");
            return;
        }

        SR_LOG("TestManager::RunAll() : SpaRcle Engine is being run in unit test mode!");

        m_argc = argc;
        m_argv = argv;

        for (auto&& test : m_engineTests) {
            if (RunEngineTest(test)) {
                successes++;
            }
        }

        SR_LOG("TestManager::RunAll() : unit tests passed: {}/{}.", successes, m_tests.size());
        SR_LOG("TestManager::RunAll() : destroying test instances...");

        pLauncher.AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    bool TestManager::RunTest(const TestManager::Test& test) {
        auto&& pApplication = SR_CORE_NS::Application::MakeShared();

        if (!pApplication->PreInit(m_argc, m_argv)) {
            SR_PLATFORM_NS::WriteConsoleError("Failed to pre-initialize application!\n");
            return false;
        }

        if (!pApplication->InitializeResourcesFolder(m_argc, m_argv)) {
            SR_ERROR("Failed to initialize resources folder!");
            return false;
        }

        if (!pApplication->EarlyInit()) {
            SR_ERROR("Failed to early initialize application!");
            return false;
        }

        SR_LOG("TestManager::RunTest() : running test '{}'.", test.first);

        auto&& result = test.second();

        pApplication->AutoFree([](auto&& pData) {
            delete pData;
        });

        return result;
    }

    bool TestManager::RunEngineTest(const TestManager::Test& test) {
        SR_LOG("TestManager::RunEngineTest() : running test '{}'.", test.first);

        auto&& result = test.second();
        return result;
    }
}
