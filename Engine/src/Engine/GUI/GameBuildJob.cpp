//
// Created by OpenAI Codex on 12.11.2026.
//

#include <Engine/GUI/GameBuildJob.h>
#include <Engine/GUI/GameBuildRuntime.h>

#include <Scripting/Base/ScriptSystem.h>

#include <Graphics/Loaders/TextureLoader.h>
#include <Graphics/Loaders/TextureContainer.h>

#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/DirectoryVFSBackend.h>
#include <Utils/FileSystem/IVFSBackend.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Network/Download.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Serialization/SRASerialization.h>
#include <Utils/Serialization/Serialization.h>

namespace SR_CORE_GUI_NS {
    static bool IsBuildTexture(const SR_UTILS_NS::Path& path) {
        SR_UTILS_NS::String extension(path.GetExtensionView());
        for (char& character : extension) {
            if (character >= 'A' && character <= 'Z') {
                character = static_cast<char>(character - 'A' + 'a');
            }
        }
        return extension == "png" || extension == "jpg" || extension == "jpeg" || extension == "tga" || extension == "bmp" || extension == "hdr";
    }

    GameBuildJob::GameBuildJob(const ProjectSettings& settings)
        : m_pProjectSettings(SRNew<ProjectSettings>())
    {
        m_pProjectSettings->projectName = settings.projectName;
        m_pProjectSettings->mainScene = settings.mainScene;
        m_pProjectSettings->version = settings.version;
        m_pProjectSettings->packages = settings.packages;
        m_pProjectSettings->buildExcludedPaths = settings.buildExcludedPaths;
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

    void GameBuildJob::BeginStage(SR_UTILS_NS::String label, float_t start, float_t span) {
        m_stageLabel = std::move(label);
        m_stageStart = start;
        m_stageSpan = span;
        SetProgress(0.f);
    }

    void GameBuildJob::SetProgress(float_t progress) {
        SetProgress(progress, progress);
    }

    void GameBuildJob::SetProgress(float_t progress, float_t detailProgress) {
        const float_t stageProgress = std::clamp(progress, 0.f, 1.f);
        const float_t overall = (m_targetIndex + m_stageStart + m_stageSpan * stageProgress) / std::max(1u, m_targetCount);
        m_lastProgress = std::max(m_lastProgress, overall);
        if (onProgress) {
            onProgress(m_lastProgress);
        }
        if (onBuildProgress) {
            onBuildProgress(m_lastProgress, detailProgress < 0.f ? -1.f : std::clamp(detailProgress, 0.f, 1.f), m_stageLabel);
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
                entry.relativePath.starts_with(cachePath) ||
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

            const auto relative = SR_UTILS_NS::Path(entry.relativePath).RemoveSubPath(resourcesPath);
            for (auto&& excluded : m_pProjectSettings->buildExcludedPaths) {
                if (excluded.IsEmpty()) {
                    continue;
                }
                const auto excludedPath = excluded.RemoveSubPath(resourcesPath);
                const auto name = relative.ToStringView();
                const auto prefix = excludedPath.ToStringView();
                if (name == prefix || name == "{}.meta"_format(prefix)
                    || (name.starts_with(prefix) && name.size() > prefix.size() && name[prefix.size()] == '/')) {
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

    bool GameBuildJob::ExportPlatform(SR_UTILS_NS::StringView platformName, SR_UTILS_NS::StringView assetName, bool downloadOnly) {
        BeginStage("{}: engine artifact"_format(platformName), 0.f, downloadOnly ? 1.f : 0.03f);
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
        if (downloadOnly || !cachedArtifact.IsFile()) {
            const auto url = "{}/releases/download/{}/{}"_format(EngineRepository, GetReleaseTag(), assetName);
            SetStatus("Downloading {}..."_format(platformName));
            SR_NETWORK_NS::DownloadRequest request;
            request.url = url;
            request.destination = cachedArtifact;
            request.isCancelled = isCancelled;
            request.transferProgress = [this](uint64_t completed, uint64_t total) {
                if (onDownload) {
                    onDownload(completed, total);
                }
                SetProgress(total ? static_cast<float_t>(completed) / static_cast<float_t>(total) : -1.f);
            };
            if (!SR_NETWORK_NS::Download(request)) {
                SetStatus("Failed to download {} build."_format(platformName), true);
                return false;
            }
        }

        if (isCancelled && isCancelled()) {
            return false;
        }
        if (downloadOnly) {
            SetProgress(1.f);
            return true;
        }
        BeginStage("{}: preparing textures"_format(platformName), 0.03f, 0.87f);
        if (!PreparePlatformResources(platformName)) {
            return false;
        }
        BeginStage("{}: collecting package resources"_format(platformName), 0.90f, 0.04f);
        if ((platformName == "Windows" || platformName == "Linux")
            && pProfile->desktopPackageMode == DesktopBuildPackageMode::Monolithic && !PackDesktopResources()) {
            return false;
        }
        SetStatus("Packing {}..."_format(platformName));
        BeginStage("{}: packing and signing"_format(platformName), 0.94f, 0.05f);
        SetProgress(-1.f);

        auto outputPath = m_outputRoot.Concat(platformName);
        if (!outputPath.CreateDirectories()) {
            SetStatus("Failed to create output directory for {}."_format(platformName), true);
            return false;
        }

        const SR_UTILS_NS::String projectFileName = SR_UTILS_NS::Path(m_pProjectSettings->projectName).ConvertToFileName();
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
        const auto finalArtifact = outputPath.Concat(outputFileName);
        const auto outputArtifact = m_outputRoot.Concat("Staging").Concat(platformName).Concat("Artifact").Concat(outputFileName);
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
        BeginStage("{}: publishing build"_format(platformName), 0.99f, 0.01f);
        if ((isCancelled && isCancelled()) || !SR_UTILS_NS::VFS::Instance().ReplaceFile(outputArtifact, finalArtifact)) {
            SetStatus("Failed to publish {} build."_format(platformName), true);
            return false;
        }

        SetProgress(1.f);
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

        if (!m_outputRoot.CreateDirectories()) {
            SetStatus("Failed to create Builds directory.", true);
            return false;
        }
        SetStatus("Saving build project configuration...");
        SR_UTILS_NS::SRASerializer projectSerializer;
        projectSerializer.SetUseTabs(true);
        projectSerializer.SetUseNumericDepth(false);
        projectSerializer.BeginObject(SR_UTILS_NS::SerializationId::Create("asset"));
        projectSerializer.WriteString(m_pProjectSettings->GetMeta()->GetFactoryName(), SR_UTILS_NS::SerializationId::Create("type"));
        projectSerializer.BeginObject(SR_UTILS_NS::SerializationId::Create("ptr"));
        m_pProjectSettings->Save(projectSerializer);
        projectSerializer.EndObject();
        projectSerializer.EndObject();
        if (!SR_UTILS_NS::VFS::Instance().WriteFileAtomic(m_outputRoot.Concat("Project/.srproject"), projectSerializer.ToStringBase())) {
            SetStatus("Failed to stage project configuration.", true);
            return false;
        }
        m_textureExporter.isCancelled = isCancelled;
        m_textureExporter.useGpu = pProfile->textureGpuEncoding;
        m_textureExporter.useAstc = pProfile->textureAstcEncoding;
        m_textureExporter.useEtc2 = pProfile->textureEtc2Encoding;
        m_textureExporter.cpuUsagePercent = pProfile->textureCpuUsagePercent;
        m_textureExporter.onStatus = [this](SR_UTILS_NS::String message) {
            SetStatus(std::move(message));
        };

        SetStatus("Collecting project resources...");
        if (!CollectBuildResources(m_sourceResourcePaths)) {
            SetStatus("Project contains too many resource files.", true);
            return false;
        }


        return ProcessTargets(false);
    }

    bool GameBuildJob::PackDesktopResources() {
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
            if (!ReadBuildResource(m_resourcePaths[i], resourceData)) {
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
            SetProgress(static_cast<float_t>(i + 1) / resourceCount);
        }

        return true;
    }

    bool GameBuildJob::ReadBuildResource(const SR_UTILS_NS::Path& path, SR_UTILS_NS::String& data) const {
        for (auto&& artifact : m_resourceOverrides) {
            if (artifact.resourcePath == path) {
                return SR_UTILS_NS::FileSystem::ReadFile(artifact.buildPath, data);
            }
        }
        return SR_UTILS_NS::FileSystem::ReadFile(path, data);
    }

    bool GameBuildJob::PreparePlatformResources(SR_UTILS_NS::StringView platform) {
        SR_TRACY_ZONE;
        m_resourcePaths.clear();
        m_resourceOverrides.clear();
        const auto profile = platform == "Android" ? SR_GRAPH_NS::TextureExportProfile::Mobile
            : platform == "Emscripten" ? GetActiveProfile()->webTextureProfile : SR_GRAPH_NS::TextureExportProfile::Desktop;
        const auto resources = CoreResLoader::GetResPath();
        m_textureExporter.requireBlockAlignedTextures = platform == "Emscripten";
        const auto stagedRoot = m_outputRoot.Concat("Staging").Concat(platform);
        uint32_t compressedTextureCount = 0;
        uint32_t losslessTextureCount = 0;
        uint32_t omittedFallbackCount = 0;
        uint64_t omittedFallbackBytes = 0;
        m_resourceOverrides.emplace_back(TextureBuildArtifact { ".srproject", m_outputRoot.Concat("Project/.srproject") });
        SR_UTILS_NS::Vector<double_t> workWeights(m_sourceResourcePaths.size());
        double_t totalWork = 0.0;
        double_t completedWork = 0.0;
        uint32_t textureCount = 0;
        uint32_t textureIndex = 0;
        for (uint32_t index = 0; index < m_sourceResourcePaths.size(); ++index) {
            if (isCancelled && isCancelled()) {
                return false;
            }
            double_t weight = 1.0;
            if (IsBuildTexture(m_sourceResourcePaths[index])) {
                ++textureCount;
                auto file = SR_UTILS_NS::VFS::Instance().OpenFile(m_sourceResourcePaths[index], SR_UTILS_NS::FileMode::Read);
                if (file) {
                    uint8_t header[4096]{};
                    const auto count = file.Read(header, sizeof(header));
                    SR_GRAPH_NS::TextureSourceInfo image;
                    weight = SR_GRAPH_NS::TextureLoader::ReadSourceInfo(SR_UTILS_NS::StringView(reinterpret_cast<const char*>(header), count), image)
                        ? static_cast<double_t>(image.width) * image.height : static_cast<double_t>(std::max(uint64_t(1), file.GetSize()));
                }
            }
            workWeights[index] = weight;
            totalWork += weight;
        }
        totalWork = std::max(1.0, totalWork);
        for (uint32_t index = 0; index < m_sourceResourcePaths.size(); ++index) {
            if (isCancelled && isCancelled()) {
                return false;
            }
            const auto path = m_sourceResourcePaths[index];
            SR_UTILS_NS::String extension(path.GetExtensionView());
            for (char& character : extension) {
                if (character >= 'A' && character <= 'Z') {
                    character = static_cast<char>(character - 'A' + 'a');
                }
            }
            const bool texture = extension == "png" || extension == "jpg" || extension == "jpeg" || extension == "tga"
                || extension == "bmp" || extension == "hdr";
            if (!texture) {
                if (extension != "bc1" && extension != "bc2" && extension != "bc3" && extension != "bc4"
                    && extension != "bc5" && extension != "bc6h" && extension != "bc7" && extension != "astc"
                    && extension != "etc2" && extension != "eac" && extension != "rgba8" && extension != "rgba16f") {
                    m_resourcePaths.insert(path);
                }
                completedWork += workWeights[index];
                SetProgress(static_cast<float_t>(completedWork / totalWork));
                continue;
            }
            SR_GRAPH_NS::ImageMetaInfo metadata;
            const auto metaPath = path.ConcatExt(".meta");
            if (metaPath.IsFile()) {
                SR_UTILS_NS::SRADeserializer deserializer;
                if (!deserializer.LoadFromFile(metaPath) || !metadata.Load(deserializer)) {
                    SetStatus("Invalid texture metadata: {}"_format(metaPath), true);
                    return false;
                }
            }
            bool sourceRequired = metadata.cpuUsage;
            static constexpr SR_UTILS_NS::StringView skyboxSides[] { "right", "left", "top", "bottom", "front", "back" };
            for (const auto side : skyboxSides) {
                if (SR_UTILS_NS::StringView(path.GetBaseNameView()) != side) {
                    continue;
                }
                bool completeSkybox = true;
                for (const auto sibling : skyboxSides) {
                    completeSkybox &= path.GetPrevious().Concat(sibling).ConcatExt(path.GetExtensionView()).IsFile();
                }
                sourceRequired |= completeSkybox;
                break;
            }
            if (platform == "Android" && sourceRequired) {
                metadata.compressionPolicy = SR_GRAPH_NS::TextureCompressionPolicy::Lossless;
            }
            SR_UTILS_NS::Vector<TextureBuildArtifact> variants;
            m_stageLabel = "{}: textures {}/{}"_format(platform, ++textureIndex, textureCount);
            m_textureExporter.onProgress = [&, index](float_t progress) {
                SetProgress(static_cast<float_t>((completedWork + workWeights[index] * progress) / totalWork), progress);
            };
            SetProgress(static_cast<float_t>(completedWork / totalWork), 0.f);
            const bool prepared = m_textureExporter.Prepare(path, metadata, profile, m_outputRoot, variants);
            m_textureExporter.onProgress = nullptr;
            if (!prepared) {
                if (isCancelled && isCancelled()) {
                    return false;
                }
                SetStatus("Texture preparation failed: {}"_format(path), true);
                return false;
            }
            if (metadata.compressed) {
                if (platform == "Android" || ((platform == "Windows" || platform == "Linux") && !GetActiveProfile()->desktopTextureFallback)) {
                    const auto relative = path.RemoveSubPath(resources);
                    for (uint32_t remaining = static_cast<uint32_t>(variants.size()); remaining > 0; --remaining) {
                        const uint32_t variantIndex = remaining - 1;
                        const auto extension = variants[variantIndex].resourcePath.GetExtensionView();
                        if (variants[variantIndex].resourcePath != relative && extension != "rgba8" && extension != "rgba16f") {
                            continue;
                        }
                        auto file = SR_UTILS_NS::VFS::Instance().OpenFile(variants[variantIndex].buildPath, SR_UTILS_NS::FileMode::Read);
                        if (file) {
                            omittedFallbackBytes += file.GetSize();
                        }
                        ++omittedFallbackCount;
                        variants.erase(variants.begin() + variantIndex);
                        metadata.preparedVariants.erase(metadata.preparedVariants.begin() + variantIndex);
                        metadata.preparedHashes.erase(metadata.preparedHashes.begin() + variantIndex);
                    }
                }
                ++compressedTextureCount;
            }
            else {
                ++losslessTextureCount;
            }
            for (auto&& variant : variants) {
                variant.resourcePath = resources.Concat(variant.resourcePath);
                m_resourcePaths.insert(variant.resourcePath);
                m_resourceOverrides.emplace_back(std::move(variant));
            }
            if (platform == "Android" && metadata.compressed) {
                const auto placeholder = stagedRoot.Concat(path.RemoveSubPath(resources));
                if (!SR_UTILS_NS::VFS::Instance().WriteFileAtomic(placeholder, SR_GRAPH_NS::TextureContainer::SourcePlaceholder)) {
                    SetStatus("Failed to stage texture placeholder: {}"_format(path), true);
                    return false;
                }
                m_resourcePaths.insert(path);
                m_resourceOverrides.emplace_back(TextureBuildArtifact { path, placeholder });
            }
            const auto stagedMetadata = stagedRoot.Concat(metaPath.RemoveSubPath(resources));
            SR_UTILS_NS::SRASerializer serializer;
            serializer.SetUseTabs(true);
            serializer.SetUseNumericDepth(false);
            metadata.Save(serializer);
            if (!SR_UTILS_NS::VFS::Instance().WriteFileAtomic(stagedMetadata, serializer.ToStringBase())) {
                SetStatus("Failed to stage texture metadata: {}"_format(metaPath), true);
                return false;
            }
            m_resourcePaths.insert(metaPath);
            m_resourceOverrides.emplace_back(TextureBuildArtifact { metaPath, stagedMetadata });
            if (sourceRequired) {
                m_resourcePaths.insert(path);
            }
            completedWork += workWeights[index];
            SetProgress(static_cast<float_t>(completedWork / totalWork));
        }
        m_textureExporter.onProgress = nullptr;
        SetProgress(1.f);
        SR_INFO("GameBuildJob::PreparePlatformResources() : {}: {} textures with accepted GPU compression, {} lossless textures",
            platform, compressedTextureCount, losslessTextureCount);
        SR_INFO("GameBuildJob::PreparePlatformResources() : {}: omitted {} compatibility variants, {} bytes",
            platform, omittedFallbackCount, omittedFallbackBytes);
        return m_resourcePaths.size() <= SR_UINT16_MAX;
    }

    bool GameBuildJob::ReinstallArtifacts() {
        m_outputRoot = GetOutputPath();
        SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::IVFSBackend> pBackend = new SR_UTILS_NS::DirectoryVFSBackend(m_outputRoot);
        SR_UTILS_NS::VFS::Instance().Mount(m_outputRoot, pBackend.Get(), 0);
        pBackend.SetDeleter([](SR_UTILS_NS::IVFSBackend* pVFS) {
            SR_UTILS_NS::VFS::Instance().Unmount(pVFS);
            delete pVFS;
        });
        return ProcessTargets(true);
    }

    bool GameBuildJob::ProcessTargets(bool downloadOnly) {
        const auto pProfile = GetActiveProfile();
        if (!pProfile) {
            SetStatus("No active build profile.", true);
            return false;
        }
        const auto version = SR_UTILS_NS::String(SR_ENGINE_VERSION);
        const auto suffix = GetReleaseTag() == "dev-latest" ? "-dev" : "";
        bool success = true;
        const uint32_t targetCount = static_cast<uint32_t>(pProfile->windows) + static_cast<uint32_t>(pProfile->linux) +
            static_cast<uint32_t>(pProfile->androidArm64) + static_cast<uint32_t>(pProfile->androidX64) + static_cast<uint32_t>(pProfile->emscripten);
        uint32_t completed = 0;
        m_targetCount = targetCount;
        m_lastProgress = 0.f;
        if (targetCount == 0) {
            SetStatus("Select at least one platform.", true);
            return false;
        }
        auto exportTarget = [&](SR_UTILS_NS::StringView platform, SR_UTILS_NS::StringView asset) {
            if (isCancelled && isCancelled()) {
                success = false;
                return;
            }
            m_targetIndex = completed;
            if (ExportPlatform(platform, asset, downloadOnly)) {
                ++completed;
            }
            else {
                success = false;
                ++completed;
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
            SetStatus(downloadOnly ? "Selected GitHub artifacts downloaded. Export the project to use them." : "Build completed.");
        }
        else if (!isCancelled || !isCancelled()) {
            SetStatus(downloadOnly ? "Artifact download failed. See the engine log for details." : "Export failed. See the engine log for details.", true);
        }
        return success;
    }


}
