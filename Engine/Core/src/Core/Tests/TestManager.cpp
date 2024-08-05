//
// Created by innerviewer on 2024-03-18.
//

#include <Core/Tests/TestManager.h>
#include <Utils/Platform/Platform.h>
#include <Core/Launcher.h>

namespace SR_CORE_NS {
    void TestManager::RunAll(int argc, char** argv) {
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

        if (!pLauncher->Init()) {
            SR_ERROR("TestManager::RunAll() : failed to initialize application!");
            return;
        }

        SR_LOG("TestManager::RunAll() : SpaRcle Engine is being run in unit test mode!");

        m_argc = argc;
        m_argv = argv;

        int32_t successes = 0;
        for (auto&& test : m_tests) {
            SR_LOG("TestManager::RunAll() : Running test '{}()'.", test.first);
            if (RunTest(test.second)) {
                successes++;
            }
        }

        SR_LOG("TestManager::RunAll() : unit tests passed: {}/{}.", successes, m_tests.size());
        SR_LOG("TestManager::RunAll() : destroying test instances...");

        pLauncher.AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    bool TestManager::RunTest(const TestManager::TestFn &test) {
        auto&& pApplication = SR_CORE_NS::Application::MakeShared();

        if (!pApplication->PreInit(m_argc, m_argv)) {
            SR_PLATFORM_NS::WriteConsoleError("Failed to pre-initialize application!\n");
            return false;
        }

        auto&& result = test();

        pApplication->AutoFree([](auto&& pData) {
            delete pData;
        });

        return result;
    }
}