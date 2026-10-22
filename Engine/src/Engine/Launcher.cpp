//
// Created by innerviewer on 2024-03-20.
//

#include <Engine/Launcher.h>

#include <Utils/Resources/ResourceEmbedder.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Common/Compression.h>
#include <Utils/Common/CLIManager.h>
#include <Utils/Platform/Platform.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Profile/TracyContext.h>
#include <Utils/Network/GitHubDownloader.h>

namespace SR_CORE_NS {
    LauncherInitStatus Launcher::InitLauncher() {
        SR_TRACY_ZONE;

        if (!PreInit()) {
            SR_PLATFORM_NS::WriteConsoleError("Launcher::Init() : failed to pre-initialize application!\n");
            return LauncherInitStatus::Error;
        }

    #if defined(SR_ENGINE_FLATPAK_BUILD) || defined(SR_ANDROID) || defined(SR_EMSCRIPTEN)
        if (InitializeResourcesFolder()) {
            return LauncherInitStatus::Success;
        }

        SR_ERROR("Launcher::InitLauncher() : failed to initialize resources folder!\n");
        return LauncherInitStatus::Error;
    #else
        if (InitializeResourcesFolder()) {
            return LauncherInitStatus::Success;
        }

        SR_LOG("Launcher::InitLauncher() : resources folder found.");

        if (UnpackEmbedded()) {
            SR_LOG("Launcher::InitLauncher() : embedded resources unpacked.");
        }

        if (!InitializeResourcesFolder()) {
            SR_ERROR("Launcher::InitLauncher() : failed to initialize resources folder!\n");
            return LauncherInitStatus::Error;
        }

        if (CloneResources() && InitializeResourcesFolder()) {
            SR_LOG("Launcher::InitLauncher() : resources cloned.");
            return LauncherInitStatus::Success;
        }
        else {
            SR_ERROR("Launcher::InitLauncher() : failed to clone resources!\n");
            return LauncherInitStatus::Error;
        }
    #endif
    }

    bool Launcher::UnpackEmbedded() {
        SR_LOG("Launcher::UnpackEmbedded() : unpacking embedded resources...");

        if (SR_UTILS_NS::CLIManager::Instance().GetProjectPath()) {
            SR_ERROR("Launcher::UnpackEmbedded() : unable to unpack embedded resources in project mode!");
            return false;
        }

        auto&& applicationPath = SR_PLATFORM_NS::GetApplicationPath();
        SR_UTILS_NS::Path unpackDirectory = applicationPath.GetFolder().GetPrevious().GetPrevious();
        return SR_UTILS_NS::ResourceEmbedder::Instance().ExportAllResources(unpackDirectory.Concat("Resources"));
    }

    bool Launcher::CloneResources() {
        auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
    #if !defined(SR_ANDROID) && !defined(SR_EMSCRIPTEN)
        auto&& cachePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
        if (!cachePath.CreateDirectories()) {
            SR_ERROR("Launcher::CloneResources() : failed to create cache directory!");
            return false;
        }
        SR_UTILS_NS::VFS::Instance().ResolvePath(cachePath, SR_UTILS_NS::FileMode::Write);
        SR_NETWORK_NS::GitHubCloneContext context;
        SR_UTILS_NS::String branch = "release/{}"_format(SR_ENGINE_VERSION);
        context.branch = branch;
        context.url = "https://github.com/SpaRcle-Studio/SRE2R";
        SR_NETWORK_NS::GitHubDownloader::CloneRepo(context, cachePath.Concat("SRE2R"));
        SR_PLATFORM_NS::Unzip(cachePath.Concat("SRE2R/Resources.zip"), resourcesPath);
    #endif

        return true;
    }
}
