//
// Created by innerviewer on 2024-03-20.
//

#include <Engine/Launcher.h>

#include <Utils/Resources/ResourceEmbedder.h>
#include <Utils/Common/Compression.h>
#include <Utils/Common/CLIManager.h>

namespace SR_CORE_NS {
    /**
     * @brief Initializes the launcher and ensures required resource folders and assets are available.
     *
     * Performs pre-initialization and platform-specific resource setup, optionally unpacking embedded
     * resources and cloning resource repositories when necessary.
     *
     * @return LauncherInitStatus `Success` if launcher initialization and resource setup completed
     *         and required resources are available, `Error` otherwise.
     */
    LauncherInitStatus Launcher::InitLauncher() {
        if (!PreInit()) {
            SR_PLATFORM_NS::WriteConsoleError("Launcher::Init() : failed to pre-initialize application!\n");
            return LauncherInitStatus::Error;
        }

    #if defined(SR_ENGINE_FLATPAK_BUILD) || defined(SR_ANDROID)
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
    #ifdef SR_LINUX
        auto&& git2path = GetResourcesPath().Concat("Engine/Utilities/git2");
    #elif defined(SR_WIN32)
        auto&& git2path = GetResourcesPath().Concat("Engine/Utilities/git2.exe");
    #endif

    #ifndef SR_ANDROID
        auto&& cachePath = GetResourcesPath().Concat("Cache");
        if (!cachePath.Create()) {
            SR_ERROR("Launcher::CloneResources() : failed to create cache directory.");
            return false;
        }

        std::string command =
                git2path.ToStringRef() + " clone https://github.com/SpaRcle-Studio/SRE2R " +
                cachePath.Concat("SRE2R").ToStringRef() +
                " -b release/0.0.7 --depth 1";

        SR_SYSTEM_LOG("Launcher::CloneResources() : cloning repository...\n" + command);

        system(command.c_str());

        SR_UTILS_NS::Path zipPath = cachePath.Concat("SRE2R/Resources.zip");
        SR_PLATFORM_NS::Unzip(zipPath, GetResourcesPath());
    #endif

        return true;
    }
}