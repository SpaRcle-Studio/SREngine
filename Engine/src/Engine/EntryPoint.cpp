//
// Created by Monika on 12.05.2025.
//

#include <Engine/EntryPoint.h>
#include <Engine/LauncherEntryPoint.h>

#include <Utils/Common/CLIManager.h>
#include <Utils/Tests/TestManager.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/Reflection/ReflectedType.h>
#include <Utils/Debug.h>

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

    {
        SR_TRACY_ZONE_N("Unregistering application module");
        Codegen::UnregisterModule_Application();
    }

    SR_UTILS_NS::Reflection::DestroyTypeInfoPool();
    SR_PLATFORM_NS::InitializeHooks([](SR_PLATFORM_NS::PlatformHooks& hooks) { });
    SR_HTYPES_NS::SharedPtrDynamicDataCounter::CheckMemoryLeaks();
    SR_UTILS_NS::ShutdownEngineProfiler();
    SR_PLATFORM_NS::DeInitializePlatform();
}

int SREngineEntryPoint(int argc, char** argv) {
    SR_UTILS_NS::StartupEngineProfiler();
    SR_PLATFORM_NS::InitializePlatform();

    {
        SR_TRACY_ZONE_N("Registering application module");
        Codegen::RegisterModule_Application();
    }

    SR_UTILS_NS::CLIManager::Instance().Init(argc, argv);

    if (SR_UTILS_NS::CLIManager::Instance().IsFlagPresent(SR_UTILS_NS::CLIFlags::UnitTests)) {
        auto&& result = SR_UTILS_NS::TestManager::Instance().RunAll();
        if (!SR_UTILS_NS::CLIManager::Instance().IsFlagPresent(SR_UTILS_NS::CLIFlags::ContinueAfterTests) || result != SR_UTILS_NS::TestExecutionResult::Success) {
            ShutdownApplication();
            return static_cast<int>(result);
        }
    }

    const int code = LauncherEntryPoint();

    ShutdownApplication();

    return code;
}