#include <Engine/GUI/GameBuildJob.h>
#include <Engine/GUI/GameBuildRuntime.h>
#include <Scripting/Cpp/ScriptSystem.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/DirectoryVFSBackend.h>
#include <Utils/FileSystem/IVFSBackend.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Network/Download.h>

namespace SR_CORE_GUI_NS {
    GameBuildJob::GameBuildJob(const ProjectSettings& settings)
        : m_pProjectSettings(SRNew<ProjectSettings>())
    {
        m_pProjectSettings->projectName = settings.projectName;
        m_pProjectSettings->mainScene = settings.mainScene;
        m_pProjectSettings->version = settings.version;
        m_pProjectSettings->packages = settings.packages;
        m_pProjectSettings->enableCppScripts = settings.enableCppScripts;
        m_pProjectSettings->buildProfiles = settings.buildProfiles;
        m_pProjectSettings->activeBuildProfile = settings.activeBuildProfile;
    }

    GameBuildJob::~GameBuildJob() {
        m_pProjectSettings->DeleteResource();
    }

    GameBuildProfile* GameBuildJob::GetActiveProfile() const {
        if (m_pProjectSettings->activeBuildProfile >= m_pProjectSettings->buildProfiles.size()) {
            return nullptr;
        }
        return &m_pProjectSettings->buildProfiles[m_pProjectSettings->activeBuildProfile];
    }

    SR_UTILS_NS::String GameBuildJob::GetReleaseTag() const {
        const SR_UTILS_NS::StringView branch = SR_ENGINE_BRANCH;
        if (branch.starts_with("release/")) {
            return "v{}"_format(SR_ENGINE_VERSION);
        }
        return "dev-latest";
    }

    SR_UTILS_NS::Path GameBuildJob::GetBuildCachePath() const {
        return SR_PLATFORM_NS::GetApplicationUserDataDirectory().Concat("BuildCache")
            .Concat(GetReleaseTag() == "dev-latest" ? "latest" : SR_ENGINE_VERSION);
    }

    SR_UTILS_NS::Path GameBuildJob::GetOutputPath() const {
        const auto profile = GetActiveProfile();
        if (!profile) {
            return {};
        }
        if (profile->outputPath.IsAbs()) {
            return profile->outputPath;
        }
        auto root = CoreResLoader::GetResPath();
        SR_UTILS_NS::VFS::Instance().ResolvePath(root, SR_UTILS_NS::FileMode::Write);
        return root.GetPrevious().Concat(profile->outputPath);
    }

    void GameBuildJob::SetStatus(SR_UTILS_NS::String status, bool error) {
        if (onStatus) {
            onStatus(status, error);
        }
        if (error) {
            SR_ERROR("GameBuildJob::SetStatus() : {}", status);
        }
        else {
            SR_INFO("GameBuildJob::SetStatus() : {}", status);
        }
    }

    bool GameBuildJob::CollectBuildResources(SR_UTILS_NS::SortedVector<SR_UTILS_NS::Path>& paths) const {
        SR_TRACY_ZONE;
        SR_LOG("GameBuildJob::CollectBuildResources() : collecting resources files to build...");

        paths.clear();
        paths.reserve(2048);

        const auto resourcesPath = CoreResLoader::GetResPath();
        auto&& cachePath = CoreResLoader::GetCachePath();
        auto&& cppAPI = SR_SCRIPTING_NS::ScriptSystem::Instance().GetAPIFolder();
        auto&& packedFiles = resourcesPath.Concat("Packed");
        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> excludeEnginePaths = {
            resourcesPath.Concat("Cache"),
            resourcesPath.Concat("Samples"),
            resourcesPath.Concat("Engine/ModuleTests"),
            resourcesPath.Concat("Engine/Utilities")
        };
        if (!GetActiveProfile()->packEditor) {
            excludeEnginePaths.emplace_back(resourcesPath.Concat("Editor"));
        }
        SR_UTILS_NS::VFS::Instance().Enumerate(resourcesPath, [&](const SR_UTILS_NS::VFSEntry& entry) {
            if (entry.type != SR_UTILS_NS::FSItemType::File ||
                entry.extension == "cpp" || entry.extension == "h" || entry.extension == "hpp" ||
                entry.relativePath.ends_with(".exe") || entry.relativePath.ends_with(".dll") || entry.relativePath.ends_with(".pdb") ||
                entry.relativePath.starts_with(cachePath) || entry.relativePath.starts_with(packedFiles) ||
                entry.relativePath.contains("CMakeLists.txt") ||
                entry.relativePath.starts_with(cppAPI) ||
                entry.relativePath.contains("/.idea/") || entry.relativePath.contains("/.git/")) {
                return;
            }
            for (auto&& path : excludeEnginePaths) {
                if (entry.relativePath == path.ToStringView() ||
                    (entry.relativePath.starts_with(path.ToStringView()) &&
                        entry.relativePath.size() > path.size() && entry.relativePath[path.size()] == '/')) {
                    return;
                }
            }

            if (SR_PLATFORM_NS::IsAbsolutePath(entry.relativePath)) {
                SRHalt("GameBuildJob::CollectBuildResources() : relative path are absolute!");
                return;
            }

            paths.insert(entry.relativePath);
        }, true);

        SR_LOG("GameBuildJob::CollectBuildResources() : collected {} files.", paths.size());

        paths.insert(".srproject");

        return paths.size() <= SR_UINT16_MAX;
    }

    bool GameBuildJob::ExportPlatform(SR_UTILS_NS::StringView platformName, SR_UTILS_NS::StringView assetName) {
        if (isCancelled && isCancelled()) {
            return false;
        }
        SetStatus("Exporting {}..."_format(platformName));
        SR_INFO("GameBuildJob::ExportPlatform() : exporting {} platform...", platformName);
        auto&& pProfile = GetActiveProfile();
        if (!pProfile) {
            return false;
        }

        const auto cachePath = GetBuildCachePath();
        if (!cachePath.CreateDirectories()) {
            SetStatus("Failed to create engine build cache.", true);
            return false;
        }

        const auto cachedArtifact = cachePath.Concat(assetName);
        if (!cachedArtifact.IsFile()) {
            const auto url = "{}/releases/download/{}/{}"_format(EngineRepository, GetReleaseTag(), assetName);
            SetStatus("Downloading {}..."_format(platformName));
            SR_NETWORK_NS::DownloadRequest request;
            request.url = url;
            request.destination = cachedArtifact;
            request.isCancelled = isCancelled;
            request.transferProgress = onDownload;
            if (!SR_NETWORK_NS::Download(request)) {
                SetStatus("Failed to download {} build."_format(platformName), true);
                return false;
            }
        }

        if (isCancelled && isCancelled()) {
            return false;
        }
        SetStatus("Packing {}..."_format(platformName));

        auto outputPath = m_outputRoot.Concat(platformName);
        if (!outputPath.CreateDirectories()) {
            SetStatus("Failed to create output directory for {}."_format(platformName), true);
            return false;
        }

        const SR_UTILS_NS::String projectFileName = SR_UTILS_NS::Path(m_pProjectSettings->projectName.ToString()).ConvertToFileName();
        SR_UTILS_NS::String outputFileName;
        const bool desktop = platformName == "Windows" || platformName == "Linux";
        if (desktop && pProfile->desktopPackageMode == DesktopBuildPackageMode::PortableZip) {
            outputFileName = "{}.zip"_format(projectFileName);
        }
        else if (platformName == "Windows") {
            outputFileName = "{}.exe"_format(projectFileName);
        }
        else if (platformName == "Linux") {
            outputFileName = projectFileName;
        }
        else if (platformName == "Android") {
            const auto architecture = assetName.find("arm64-v8a") != SR_UTILS_NS::StringView::npos ? "arm64-v8a" : "x86_64";
            outputFileName = "{}-{}.apk"_format(projectFileName, architecture);
        }
        else {
            outputFileName = "{}.zip"_format(projectFileName);
        }
        const auto outputArtifact = outputPath.Concat(outputFileName);
        if (!cachedArtifact.Copy(outputArtifact)) {
            SetStatus("Failed to stage {} build."_format(platformName), true);
            return false;
        }

        if ((platformName == "Windows" || platformName == "Linux") && !RepackDesktop(outputArtifact)) {
            return false;
        }
        if (platformName == "Android" && !RepackAndroid(outputArtifact)) {
            return false;
        }
        if (platformName == "Emscripten" && !RepackEmscripten(outputArtifact)) {
            return false;
        }
        if (platformName == "Linux" && pProfile->desktopPackageMode == DesktopBuildPackageMode::Monolithic) {
            SR_PLATFORM_NS::CopyPermissions(SR_PLATFORM_NS::GetApplicationPath(), outputArtifact);
        }

        return true;
    }

    bool GameBuildJob::Build() {
        if (isCancelled && isCancelled()) {
            return false;
        }
        auto&& pProfile = GetActiveProfile();
        if (!pProfile) {
            SetStatus("No active build profile.", true);
            return false;
        }

        const auto version = SR_UTILS_NS::String(SR_ENGINE_VERSION);
        const bool latest = GetReleaseTag() == "dev-latest";
        const auto suffix = latest ? "-dev" : "";

        SetStatus("Saving project configuration...");

        if (!m_pProjectSettings->SaveAsset(".srproject")) {
            SetStatus("Failed to save project settings before build.", true);
            return false;
        }

        m_outputRoot = GetOutputPath();

        SR_INFO("GameBuildExported::Build() : building project for \"{}\"", m_outputRoot);

        SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::IVFSBackend> pBackend = new SR_UTILS_NS::DirectoryVFSBackend(m_outputRoot);
        SR_UTILS_NS::VFS::Instance().Mount(m_outputRoot, pBackend.Get(), 0);
        pBackend.SetDeleter([](SR_UTILS_NS::IVFSBackend* pVFS) {
            SR_UTILS_NS::VFS::Instance().Unmount(pVFS);
            delete pVFS;
        });

        SR_UTILS_NS::EnumReflector::ForEach<SR_UTILS_NS::PlatformType>([&](SR_UTILS_NS::PlatformType platform) {
            const auto platformPath = m_outputRoot.Concat(SR_UTILS_NS::EnumReflector::ToStringAtom(platform));
            if (platformPath.IsDir()) {
                SR_UTILS_NS::VFS::Instance().Delete(platformPath);
            }
        });

        SetStatus("Collecting project resources...");
        if (!CollectBuildResources(m_resourcePaths)) {
            SetStatus("Project contains too many resource files.", true);
            return false;
        }

        if ((pProfile->windows || pProfile->linux) && pProfile->desktopPackageMode == DesktopBuildPackageMode::Monolithic) {
            SetStatus("Packing project resources...");
            SR_TRACY_ZONE_N("Desktop packing");
            m_desktopPackedBinary.clear();
            m_desktopPackedBinary.shrink_to_fit();
            const auto resourceCount = static_cast<uint16_t>(m_resourcePaths.size());
            AppendBinary(m_desktopPackedBinary, resourceCount);
            SR_UTILS_NS::String resourceData;
            SR_UTILS_NS::String resourceName;
            for (uint16_t i = 0; i < resourceCount; ++i) {
                if (isCancelled && isCancelled()) {
                    return false;
                }
                auto resourceFile = SR_UTILS_NS::VFS::Instance().OpenFile(m_resourcePaths[i], SR_UTILS_NS::FileMode::Read);
                if (!resourceFile || !resourceFile.Read(resourceData)) {
                    SetStatus("Failed to read resource: {}"_format(m_resourcePaths[i]), true);
                    return false;
                }

                resourceName = m_resourcePaths[i].ToStringView();
                if (resourceName.starts_with("Resources/")) {
                    resourceName = resourceName.substr(10);
                }
                resourceName = m_resourcePaths[i] == ".srproject" ? SR_UTILS_NS::String(".srproject") :
                    "Resources/{}"_format(resourceName);

                if (resourceName.size() > SR_UINT16_MAX) {
                    SetStatus("Resource name is too long: {}"_format(m_resourcePaths[i]), true);
                    return false;
                }

                const auto nameSize = static_cast<uint16_t>(resourceName.size());
                const uint64_t contentSize = resourceData.size();
                AppendBinary(m_desktopPackedBinary, nameSize);
                m_desktopPackedBinary.append(resourceName.data(), resourceName.size());
                AppendBinary(m_desktopPackedBinary, contentSize);
                m_desktopPackedBinary.append(resourceData.data(), resourceData.size());
                if (onProgress) {
                    onProgress(static_cast<float_t>(i + 1) / resourceCount);
                }
            }
        }

        bool success = true;
        const uint32_t targetCount = static_cast<uint32_t>(pProfile->windows) + static_cast<uint32_t>(pProfile->linux) +
            static_cast<uint32_t>(pProfile->androidArm64) + static_cast<uint32_t>(pProfile->androidX64) + static_cast<uint32_t>(pProfile->emscripten);
        uint32_t completed = 0;
        auto exportTarget = [&](SR_UTILS_NS::StringView platform, SR_UTILS_NS::StringView asset) {
            if (isCancelled && isCancelled()) {
                success = false;
                return;
            }
            success &= ExportPlatform(platform, asset);
            if (onProgress && targetCount > 0) {
                onProgress(static_cast<float_t>(++completed) / targetCount);
            }
        };
        const auto desktopSuffix = pProfile->desktopPackageMode == DesktopBuildPackageMode::Monolithic ? "_monolithic" : "";
        if (pProfile->windows) {
            exportTarget("Windows", "SREngine_v{}{}_windows.x86_64{}.exe"_format(version, suffix, desktopSuffix));
        }
        if (pProfile->linux) {
            exportTarget("Linux", "SREngine_v{}{}_linux.x86_64{}"_format(version, suffix, desktopSuffix));
        }
        if (pProfile->androidArm64) {
            exportTarget("Android", "SREngine_v{}{}_android.arm64-v8a.apk"_format(version, suffix));
        }
        if (pProfile->androidX64) {
            exportTarget("Android", "SREngine_v{}{}_android.x86_64.apk"_format(version, suffix));
        }
        if (pProfile->emscripten) {
            exportTarget("Emscripten", "SREngine_v{}{}_emscripten.zip"_format(version, suffix));
        }

        if (success) {
            if (onProgress) {
                onProgress(1.f);
            }
            SetStatus("Build completed.");
        }
        else if (!isCancelled || !isCancelled()) {
            SetStatus("Export failed. See the engine log for details.", true);
        }
        return success;
    }


}
