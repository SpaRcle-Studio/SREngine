//
// Created by Monika on 12.05.2025.
//

#include <Engine/EntryPoint.h>

#include <Engine/Launcher.h>
#include <Engine/Tests/TestManager.h>
#include <Engine/CLIManager.h>

#include <Utils/Common/CmdOptions.h>
#include <Utils/Tests/SharedPtrAutotests.h>

#include <Engine/Tests/AtlasBuilderTest.h>
#include <Engine/Tests/HTMLTest.h>

#include <Codegen/SpaRcleModuleApplicationCore.generated.hpp>

int SREngineEntryPoint(int argc, char** argv) {
    SR_UTILS_NS::StartupEngineProfiler();

    Codegen::RegisterModule_Application();

    if (!SR_UTILS_NS::RunTestSharedPtr()) {
        SR_PLATFORM_NS::WriteConsoleError("Application::PreInit() : shared pointer autotests failed!\n");
        return 10;
    }

    SR_CORE_NS::CLIManager::Instance().Init(argc, argv);

    if (SR_CORE_NS::CLIManager::Instance().IsFlagPresent(SR_CORE_NS::CLIFlags::UnitTests)) {
        SR_CORE_NS::TestManager::Instance().AddTest([]() {
            return SR_CORE_NS::Tests::AtlasBuilderTest::Run();
        }, "Atlas Builder Test");

        SR_CORE_NS::TestManager::Instance().AddTest([]() {
            return SR_CORE_NS::Tests::HTMLTest::Run();
        }, "HTML Test");

        SR_CORE_NS::TestManager::Instance().AddTest([]() {
            return SR_CORE_NS::Tests::CSSTest::Run();
        }, "CSS Test");

        SR_CORE_NS::TestManager::Instance().RunAll();
        return 0;
    }

    int32_t code = 0;

    {
        SR_HTYPES_NS::SharedPtr pLauncher = new SR_CORE_NS::Launcher();

        auto&& launcherInitStatus = pLauncher->InitLauncher();

        if (launcherInitStatus == SR_CORE_NS::LauncherInitStatus::Error) {
            SR_PLATFORM_NS::WriteConsoleError("Failed to initialize launcher!\n");
            code = 1;
        }
        else if (launcherInitStatus == SR_CORE_NS::LauncherInitStatus::Unpacking) {
            return code;
        }

        if (code == 0 && !pLauncher->EarlyInit()) {
            SR_ERROR("Failed to early initialize application!");
            code = 3;
        }

        if (code == 0 && !pLauncher->Init()) {
            SR_ERROR("Failed to initialize application!");
            code = 3;
        }

        if (code == 0 && !pLauncher->Execute()) {
            SR_ERROR("Failed to execute application!");
            code = 4;
        }

        pLauncher.AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    SR_HTYPES_NS::SharedPtrDynamicDataCounter::CheckMemoryLeaks();

    SR_UTILS_NS::ShutdownEngineProfiler();

    return code;
}