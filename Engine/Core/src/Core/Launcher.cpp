//
// Created by innerviewer on 2024-03-20.
//

#include <Core/Launcher.h>

#include <Utils/Resources/ResourceEmbedder.h>
#include <Utils/Common/Compression.h>

namespace SR_CORE_NS {
    LauncherInitStatus Launcher::InitLauncher(int argc, char** argv) {
        if (!PreInit(argc, argv)) {
            SR_PLATFORM_NS::WriteConsoleError("Launcher::Init() : failed to pre-initialize application!\n");
            return LauncherInitStatus::Error;
        }
#define SR_ENGINE_FLATPAK_BUILD
    #ifdef SR_ENGINE_FLATPAK_BUILD
        if (Super::InitializeResourcesFolder(argc, argv)) {
            SR_LOG("Launcher::InitLauncher() : resources folder found.");
            return LauncherInitStatus::Success;
        }

        auto&& flatpakResourcesPath = SR_UTILS_NS::Path("/app/share/SREngine/Resources");
        if (!flatpakResourcesPath.Exists()) {
            SR_ERROR("Launcher::InitLauncher() : necessary resources were not found. Please try reinstalling the application.");
            return LauncherInitStatus::Error;
        }

        if (flatpakResourcesPath.Copy(SR_UTILS_NS::ResourceManager::Instance().GetResPathRef())) {
            SR_LOG("Launcher::InitLauncher() : successfully copied resources from Flatpak sandbox.");
            return LauncherInitStatus::Success;
        }

        return LauncherInitStatus::Error;

    #else
        if (Super::InitializeResourcesFolder(argc, argv)) {
            SR_LOG("Launcher::InitLauncher() : resources folder found.");
            if (SR_UTILS_NS::HasCmdOption(argv, argv + argc, "--delete-old-app")) {
                DeleteOldApplication();
                CloneResources();
            }

            return LauncherInitStatus::Success;
        }

        if (!UnpackAndExecute()) {
            SR_ERROR("Launcher::InitLauncher() : failed to unpack and execute new application.");
            return LauncherInitStatus::Error;
        }

        return LauncherInitStatus::Unpacking;
    #endif
    }

    bool Launcher::UnpackAndExecute() {
        SR_LOG("Launcher::UnpackAndExecute() : trying to unpack the application.");

        auto&& applicationPath = SR_PLATFORM_NS::GetApplicationPath();
        SR_UTILS_NS::Path unpackDirectory = applicationPath.GetFolder().Concat( "SREngine");

        if (!unpackDirectory.CreateIfNotExists()) {
            SR_ERROR("Launcher::Unpack() : failed to create new application directory.");
            return false;
        }

        SR_UTILS_NS::Path newApplicationPath = unpackDirectory.Concat(applicationPath.GetBaseNameAndExt());
        bool copyResult = SR_PLATFORM_NS::Copy(applicationPath, newApplicationPath);
        bool exportResult = SR_UTILS_NS::ResourceEmbedder::Instance().ExportAllResources(unpackDirectory.Concat("Resources"));

        if (copyResult && exportResult) {
            /*char *c_path = const_cast<char*>(newApplicationPath.c_str());
            const char *c_arg = "--delete-old-app";
            char *const argv[] = {c_path, const_cast<char*>(c_arg), nullptr};
            char *const envp[] = { nullptr };
            execve(newApplicationPath.c_str(), argv, envp);*/

            SR_LOG("Launcher::UnpackAndExecute() : successfully copied the current executable and exported embedded resources.");
            SR_LOG("Launcher::UnpackAndExecute() : trying to execute the copied application.");

            /// TODO: Should we use execve/smth else for Linux here?
            /// P.S. The current process waits till the new one is finished, so we should come up with something else.
            SR_PLATFORM_NS::OpenFile(newApplicationPath, "--delete-old-app");
        }

        return true;
    }

    void Launcher::DeleteOldApplication() {
        auto&& applicationPath = SR_PLATFORM_NS::GetApplicationPath();
        auto&& oldApplicationPath = applicationPath.GetFolder().Concat("../" + applicationPath.GetBaseNameAndExt());

        if (oldApplicationPath.Exists()) {
            SR_LOG("Launcher::DeleteOldApplication() : old application found, trying to delete...");
        }
        else {
            SR_LOG("Launcher::DeleteOldApplication() : old application not found.");
            return;
        }

        SR_PLATFORM_NS::WaitAndDelete(oldApplicationPath);
        SR_PLATFORM_NS::WaitAndDelete(applicationPath.GetFolder().Concat("../srengine-log.txt"));
        SR_PLATFORM_NS::WaitAndDelete(applicationPath.GetFolder().Concat("../successful"));

        SR_LOG("Launcher::DeleteOldApplication() : old application deleted successfully.");
    }

    bool Launcher::CloneResources() {
    #ifdef SR_LINUX
        auto&& git2path = GetResourcesPath().Concat("Engine/Utilities/git2");
    #elif defined(SR_WIN32)
        auto&& git2path = GetResourcesPath().Concat("Engine/Utilities/git2.exe");
    #endif

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

        return true;
    }
}
