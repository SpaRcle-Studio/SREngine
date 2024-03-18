//
// Created by innerviewer on 2024-03-18.
//

#include <Core/Tests/TestManager.h>
#include <Utils/Platform/Platform.h>
#include <Core/Application.h>

namespace SR_CORE_NS {
    void TestManager::RunAll(int argc, char** argv) {
        auto&& pApplication = SR_CORE_NS::Application::MakeShared();

        int32_t code = 0;

        if (!pApplication->PreInit(argc, argv)) {
            SR_PLATFORM_NS::WriteConsoleError("Failed to pre-initialize application!\n");
            code = 1;
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

        SR_LOG("Unit tests passed: {}/{}.", successes, m_tests.size());
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