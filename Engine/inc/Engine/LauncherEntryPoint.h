//
// Created by Monika on 29.11.2025.
//

#ifndef SR_ENGINE_LAUNCHER_ENTRY_POINT_H
#define SR_ENGINE_LAUNCHER_ENTRY_POINT_H

#include <Engine/Launcher.h>

#include <Utils/Resources/ResourceManager.h>
#include <Utils/Platform/Platform.h>

using LauncherEntryPointAfterInitCallback = SR_HTYPES_NS::Function<void(SR_CORE_NS::Launcher::Ptr&)>;

enum LauncherEntryPointErrorCode : int32_t {
    LauncherEntryPointErrorCode_Success = 0,
    LauncherEntryPointErrorCode_ResourcesError,
    LauncherEntryPointErrorCode_LauncherError,
    LauncherEntryPointErrorCode_AppEarlyError,
    LauncherEntryPointErrorCode_AppInitError,
    LauncherEntryPointErrorCode_ExecuteError
};

#ifdef SR_EMSCRIPTEN
static SR_HTYPES_NS::SharedPtr<SR_CORE_NS::Launcher>& GetWebLauncher() {
    static SR_HTYPES_NS::SharedPtr<SR_CORE_NS::Launcher> launcher;
    return launcher;
}
#endif

static int32_t LauncherEntryPoint(const LauncherEntryPointAfterInitCallback& afterInitCallback = LauncherEntryPointAfterInitCallback()) {
    SR_TRACY_ZONE;

#ifdef SR_EMSCRIPTEN
    auto& pLauncher = GetWebLauncher();
    pLauncher = new SR_CORE_NS::Launcher();
#else
    SR_HTYPES_NS::SharedPtr pLauncher = new SR_CORE_NS::Launcher();
#endif

    auto&& launcherInitStatus = pLauncher->InitLauncher();

    if (launcherInitStatus == SR_CORE_NS::LauncherInitStatus::Error) {
        SR_PLATFORM_NS::WriteConsoleError("Failed to initialize launcher!\n");
        return LauncherEntryPointErrorCode_LauncherError;
    }

    if (!SR_UTILS_NS::ResourceManager::Instance().IsInitialized() && !SR_UTILS_NS::ResourceManager::Instance().Initialize()) {
        SR_PLATFORM_NS::WriteConsoleError("Failed to initialize resources manager!");
        return LauncherEntryPointErrorCode_ResourcesError;
    }

    if (!pLauncher->EarlyInit()) {
        SR_ERROR("LauncherEntryPoint() : failed to early initialize application!");
        return LauncherEntryPointErrorCode_AppEarlyError;
    }

    if (!pLauncher->Init()) {
        SR_ERROR("LauncherEntryPoint() : failed to initialize application!");
        return LauncherEntryPointErrorCode_AppInitError;
    }

    if (afterInitCallback) {
        afterInitCallback(pLauncher);
    }

    if (!pLauncher->Execute()) {
        SR_ERROR("LauncherEntryPoint() : failed to execute application!");
        return LauncherEntryPointErrorCode_ExecuteError;
    }
    return LauncherEntryPointErrorCode_Success;
}

#endif //SR_ENGINE_LAUNCHER_ENTRY_POINT_H
