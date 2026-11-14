//
// Created by Monika on 12.05.2025.
//

#include <Engine/EntryPoint.h>
#include <Engine/LauncherEntryPoint.h>
#include <Utils/Platform/StdioTCPBridge.h>
#include <Utils/Platform/Platform.h>

#include <Utils/Common/CLIManager.h>
#include <Utils/Tests/TestManager.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/Reflection/ReflectedType.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Debug.h>

#include <Codegen/SpaRcleModuleApplicationCore.generated.hpp>

void ShutdownApplication() {
#ifdef SR_EMSCRIPTEN
    SR_PLATFORM_NS::SetWebApplicationShutdownCallback(nullptr);
    GetWebLauncher().AutoFree();
#endif
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

    SR_UTILS_NS::Reflection::DeInitReflection();
    SR_UTILS_NS::VFS::Instance().DeInitialize();
    SR_HTYPES_NS::SharedPtrDynamicDataCounter::CheckMemoryLeaks();
    SR_UTILS_NS::ShutdownEngineProfiler();
    SR_PLATFORM_NS::DeInitializePlatform();
}

int SREngineEntryPoint(int argc, char** argv) {
    for (int32_t i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--angelscript-dap-bridge") != 0) {
            continue;
        }

        uint32_t port = 4711;
        for (int32_t argument = 1; argument < argc; ++argument) {
            if (strcmp(argv[argument], "--port") != 0) {
                continue;
            }
            if (++argument == argc || !*argv[argument]) {
                SR_PLATFORM_NS::WriteConsoleError("SREngineEntryPoint() : --port requires a value.\n");
                return 1;
            }
            port = 0;
            for (const char* pDigit = argv[argument]; *pDigit; ++pDigit) {
                if (*pDigit < '0' || *pDigit > '9' || port > 6553) {
                    SR_PLATFORM_NS::WriteConsoleError("SREngineEntryPoint() : invalid DAP port.\n");
                    return 1;
                }
                port = port * 10 + *pDigit - '0';
            }
        }
        if (!port || port > 65535) {
            SR_PLATFORM_NS::WriteConsoleError("SREngineEntryPoint() : DAP port must be between 1 and 65535.\n");
            return 1;
        }
        return SR_PLATFORM_NS::RunStdioTCPBridge(static_cast<uint16_t>(port));
    }

    SR_UTILS_NS::StartupEngineProfiler();
    SR_PLATFORM_NS::InitializePlatform();
#ifdef SR_EMSCRIPTEN
    SR_PLATFORM_NS::SetWebApplicationShutdownCallback(ShutdownApplication);
#endif

    SR_UTILS_NS::Reflection::InitReflection();
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

    const int32_t code = LauncherEntryPoint();

    ShutdownApplication();

    return code;
}
