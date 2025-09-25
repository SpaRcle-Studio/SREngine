//
// Created by Monika on 12.05.2025.
//

#include <Engine/EntryPoint.h>
#include <Engine/Launcher.h>

#include <Utils/Common/CLIManager.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Tests/TestManager.h>
#include <Utils/Profile/TracyContext.h>

#include <Codegen/SpaRcleModuleApplicationCore.generated.hpp>

void ShutdownApplication() {
    SR_UTILS_NS::GetSingletonManager()->DestroyAll();
    if (SR_UTILS_NS::ResourceManager::Instance().IsInitialized()) {
        SR_UTILS_NS::ResourceManager::Instance().DeInitialize();
    }
    if (SR_UTILS_NS::Debug::Instance().IsInitialized()) {
        SR_UTILS_NS::Debug::Instance().DeInitialize();
    }
    SR_HTYPES_NS::Thread::Factory::Instance().PrintThreads();
    SR_HTYPES_NS::Thread::Factory::Instance().DeInitialize();
    SR_HTYPES_NS::SharedPtrDynamicDataCounter::CheckMemoryLeaks();
    SR_UTILS_NS::ShutdownEngineProfiler();
}

int SREngineEntryPoint(int argc, char** argv) {
    SR_UTILS_NS::StartupEngineProfiler();
    SR_PLATFORM_NS::InitializePlatform();

    Codegen::RegisterModule_Application();

    SR_UTILS_NS::CLIManager::Instance().Init(argc, argv);

    if (SR_UTILS_NS::CLIManager::Instance().IsFlagPresent(SR_UTILS_NS::CLIFlags::UnitTests)) {
        auto&& result = SR_UTILS_NS::TestManager::Instance().RunAll();
        if (!SR_UTILS_NS::CLIManager::Instance().IsFlagPresent(SR_UTILS_NS::CLIFlags::ContinueAfterTests) || result != SR_UTILS_NS::TestExecutionResult::Success) {
            ShutdownApplication();
            return static_cast<int>(result);
        }
    }

    int32_t code = 0;

    SR_HTYPES_NS::SharedPtr pLauncher = new SR_CORE_NS::Launcher();

    auto&& launcherInitStatus = pLauncher->InitLauncher();

    if (!SR_UTILS_NS::ResourceManager::Instance().IsInitialized()) {
        if (!SR_UTILS_NS::ResourceManager::Instance().Initialize(pLauncher->GetResourcesPath(), pLauncher->GetEngineResourcesPath())) {
            SR_PLATFORM_NS::WriteConsoleError("Failed to initialize resources manager!");
            code = 1;
        }
    }

    if (launcherInitStatus == SR_CORE_NS::LauncherInitStatus::Error) {
        SR_PLATFORM_NS::WriteConsoleError("Failed to initialize launcher!\n");
        code = 2;
    }

    if (code == 0 && !pLauncher->EarlyInit()) {
        SR_ERROR("Failed to early initialize application!");
        code = 3;
    }

    if (code == 0 && !pLauncher->Init()) {
        SR_ERROR("Failed to initialize application!");
        code = 4;
    }

    if (code == 0 && !pLauncher->Execute()) {
        SR_ERROR("Failed to execute application!");
        code = 5;
    }

    pLauncher.AutoFree([](auto&& pData) {
        delete pData;
    });

    ShutdownApplication();

    return code;
}