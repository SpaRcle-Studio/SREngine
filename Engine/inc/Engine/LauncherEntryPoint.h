//
// Created by Monika on 29.11.2025.
//

#ifndef SR_ENGINE_LAUNCHER_ENTRY_POINT_H
#define SR_ENGINE_LAUNCHER_ENTRY_POINT_H

#include <Engine/Launcher.h>

#include <Utils/Resources/ResourceManager.h>

using LauncherEntryPointAfterInitCallback = SR_HTYPES_NS::Function<void(SR_CORE_NS::Launcher::Ptr&)>;

static int LauncherEntryPoint(const LauncherEntryPointAfterInitCallback& afterInitCallback = LauncherEntryPointAfterInitCallback()) {
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

    if (code == 0 && afterInitCallback) {
        afterInitCallback(pLauncher);
    }

    if (code == 0 && !pLauncher->Execute()) {
        SR_ERROR("Failed to execute application!");
        code = 5;
    }

    pLauncher.AutoFree([](auto&& pData) {
        delete pData;
    });

    return code;
}

#endif //SR_ENGINE_LAUNCHER_ENTRY_POINT_H
