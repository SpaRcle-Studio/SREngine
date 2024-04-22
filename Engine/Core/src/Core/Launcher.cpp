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
    }

    bool Launcher::UnpackAndExecute() {
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
        //system("curl -OL https://raw.githubusercontent.com/SpaRcle-Studio/SRE2R/master/Resources.zip");

        auto&& applicationDirectory = SR_PLATFORM_NS::GetApplicationPath().GetFolder();
        SR_UTILS_NS::Path zipPath = applicationDirectory.Concat("Resources.zip");
        std::string command = "curl -o " + zipPath.ToString() + " -L https://raw.githubusercontent.com/SpaRcle-Studio/SRE2R/master/Resources.zip";
        system(command.c_str());
        SR_PLATFORM_NS::Unzip(zipPath, applicationDirectory);
        SR_PLATFORM_NS::WaitAndDelete(zipPath);

        //SR_UTILS_NS::Compression::Unzip(resourcePath, applicationDirectory);

        return false;
    }
}
