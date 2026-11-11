//
// Created by OpenAI Codex on 09.11.2026.
//

#include <Engine/GUI/GameBuildExporter.h>

#include <Scripting/Cpp/ScriptSystem.h>

#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/DirectoryVFSBackend.h>
#include <Utils/FileSystem/File.h>
#include <Utils/FileSystem/Archive.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Resources/ResourceManager.h>

#include <zlib/zlib.h>

#include <Codegen/GameBuildExporter.generated.hpp>

namespace SR_CORE_GUI_NS {
    static constexpr SR_UTILS_NS::StringView EngineRepository = "https://github.com/SpaRcle-Studio/SREngine";
    static constexpr SR_UTILS_NS::StringView PackedDataMagic = "MAGIC_ENGINE_MODULE_DATA";

    template<typename T> static void AppendBinary(SR_UTILS_NS::String& data, const T& value) {
        data.append(reinterpret_cast<const char*>(&value), sizeof(T));
    }

    static bool ReadBinary(SR_UTILS_NS::StringView data, SR_UTILS_NS::SizeType& position, void* pValue, SR_UTILS_NS::SizeType size) {
        if (position + size > data.size()) {
            return false;
        }
        memcpy(pValue, data.data() + position, size);
        position += size;
        return true;
    }

    GameBuildExporter::GameBuildExporter()
        : Super("Game Build Exporter", SR_MATH_NS::IVector2(680, 720))
    { }

    GameBuildExporter::~GameBuildExporter() = default;

    void GameBuildExporter::OnOpen() {
        if (LoadProjectSettings()) {
            m_cppScriptsFound = false;
            SR_UTILS_NS::VFS::Instance().Enumerate(
                SR_UTILS_NS::ResourceManager::Instance().GetResPath(),
                [this](const SR_UTILS_NS::VFSEntry& entry) {
                    if (entry.extension == "cpp" || entry.extension == "h" || entry.extension == "hpp") {
                        m_cppScriptsFound = true;
                    }
                },
                true
            );
        }
    }

    bool GameBuildExporter::LoadProjectSettings() {
        if (!SR_UTILS_NS::VFS::Instance().IsExists(".srproject")) {
            return true;
        }

        if (m_pProjectSettings) {
            return true;
        }

        m_pProjectSettings = CoreResLoader::Load<ProjectSettings>(".srproject");
        if (!m_pProjectSettings) {
            SetStatus("Project settings were not found.", true);
            return false;
        }

        if (m_pProjectSettings->buildProfiles.empty()) {
            m_pProjectSettings->buildProfiles.emplace_back();
            m_pProjectSettings->activeBuildProfile = 0;
        }
        return true;
    }

    GameBuildProfile* GameBuildExporter::GetActiveProfile() const {
        if (!m_pProjectSettings || m_pProjectSettings->buildProfiles.empty()) {
            return nullptr;
        }
        if (m_pProjectSettings->activeBuildProfile >= m_pProjectSettings->buildProfiles.size()) {
            m_pProjectSettings->activeBuildProfile = 0;
        }
        return &m_pProjectSettings->buildProfiles[m_pProjectSettings->activeBuildProfile];
    }

    SR_UTILS_NS::String GameBuildExporter::GetReleaseTag() const {
        const SR_UTILS_NS::StringView branch = SR_ENGINE_BRANCH;
        if (branch.starts_with("release/")) {
            return "v{}"_format(SR_ENGINE_VERSION);
        }
        return "dev-latest";
    }

    SR_UTILS_NS::Path GameBuildExporter::GetBuildCachePath() const {
        return SR_PLATFORM_NS::GetUserDataDirectory()
            .Concat(SR_PLATFORM_NS::GetApplicationInfo().organization)
            .Concat(SR_PLATFORM_NS::GetApplicationInfo().name)
            .Concat("BuildCache")
            .Concat(GetReleaseTag() == "dev-latest" ? "latest" : SR_ENGINE_VERSION);
    }

    void GameBuildExporter::SetStatus(SR_UTILS_NS::String status, bool error) {
        m_status = std::move(status);
        m_statusError = error;
        if (error) {
            SR_ERROR("GameBuildExporter::SetStatus() : {}", m_status);
        }
        else {
            SR_INFO("GameBuildExporter::SetStatus() : {}", m_status);
        }
    }

    bool GameBuildExporter::CollectBuildResources(SR_UTILS_NS::SortedVector<SR_UTILS_NS::Path>& paths) const {
        SR_TRACY_ZONE;
        SR_LOG("GameBuildExporter::CollectBuildResources() : collecting resources files to build...");

        paths.clear();
        paths.reserve(2048);

        const auto resourcesPath = CoreResLoader::GetResPath();
        auto&& cachePath = CoreResLoader::GetCachePath();
        auto&& cppAPI = SR_SCRIPTING_NS::ScriptSystem::Instance().GetAPIFolder();
        auto&& packedFiles = resourcesPath.Concat("Packed");
        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> excludeEnginePaths = {
            resourcesPath.Concat("Samples"),
            resourcesPath.Concat("Engine/ModuleTests"),
            resourcesPath.Concat("Engine/Utilities")
        };
        if (!GetActiveProfile()->packEditor) {
            excludeEnginePaths.emplace_back(resourcesPath.Concat("Editor"));
        }
        for (auto&& path : excludeEnginePaths) {
            SR_UTILS_NS::VFS::Instance().ResolvePath(path, SR_UTILS_NS::FileMode::Read);
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
                if (entry.fullPath.starts_with(path)) {
                    return;
                }
            }

            if (SR_PLATFORM_NS::IsAbsolutePath(entry.relativePath)) {
                SRHalt("GameBuildExporter::CollectBuildResources() : relative path are absolute!");
                return;
            }

            paths.insert(entry.relativePath);
        }, true);

        SR_LOG("GameBuildExporter::CollectBuildResources() : collected {} files.", paths.size());

        paths.insert(".srproject");

        return paths.size() <= SR_UINT16_MAX;
    }

    bool GameBuildExporter::RepackDesktop(const SR_UTILS_NS::Path& artifactPath) {
        SR_LOG("GameBuildExporter::RepackDesktop() : repacking \"{}\"...", artifactPath);

        auto artifactFile = SR_UTILS_NS::VFS::Instance().OpenFile(artifactPath, SR_UTILS_NS::FileMode::Read);
        SR_UTILS_NS::String artifactData;
        if (!artifactFile || !artifactFile.Read(artifactData)) {
            SetStatus("Failed to read desktop artifact.", true);
            return false;
        }

        const SR_UTILS_NS::SizeType footerSize = PackedDataMagic.size() + sizeof(uint64_t) * 2;
        if (artifactData.size() < footerSize) {
            SetStatus("Desktop artifact does not contain packed data.", true);
            return false;
        }

        const SR_UTILS_NS::SizeType footerOffset = artifactData.size() - footerSize;
        if (SR_UTILS_NS::StringView(artifactData.data() + footerOffset, PackedDataMagic.size()) != PackedDataMagic) {
            SetStatus("Desktop artifact has an unknown packed data format.", true);
            return false;
        }

        SR_UTILS_NS::SizeType footerPosition = footerOffset + PackedDataMagic.size();
        uint64_t decompressedSize = 0;
        uint64_t compressedSize = 0;
        if (!ReadBinary(artifactData, footerPosition, &decompressedSize, sizeof(decompressedSize)) ||
            !ReadBinary(artifactData, footerPosition, &compressedSize, sizeof(compressedSize)) ||
            compressedSize > footerOffset) {
            SetStatus("Desktop artifact has invalid packed data sizes.", true);
            return false;
        }

        const SR_UTILS_NS::SizeType packedDataOffset = footerOffset - compressedSize;
        SR_UTILS_NS::String unpackedData;
        unpackedData.resize(decompressedSize);
        uLongf unpackedSize = decompressedSize;
        if (uncompress(
            reinterpret_cast<Bytef*>(unpackedData.data()),
            &unpackedSize,
            reinterpret_cast<const Bytef*>(artifactData.data() + packedDataOffset),
            compressedSize
        ) != Z_OK) {
            SetStatus("Failed to decompress desktop artifact.", true);
            return false;
        }
        unpackedData.resize(unpackedSize);

        SR_UTILS_NS::SizeType packedPosition = 0;
        uint16_t executableFileCount = 0;
        if (!ReadBinary(unpackedData, packedPosition, &executableFileCount, sizeof(executableFileCount))) {
            SetStatus("Desktop artifact contains invalid file entries.", true);
            return false;
        }

        SR_UTILS_NS::String newPackedData;
        const SR_UTILS_NS::SizeType executableFileCountPosition = newPackedData.size();
        uint16_t newExecutableFileCount = 0;
        AppendBinary(newPackedData, newExecutableFileCount);
        for (uint16_t i = 0; i < executableFileCount; ++i) {
            uint16_t nameSize = 0;
            uint64_t contentSize = 0;
            if (!ReadBinary(unpackedData, packedPosition, &nameSize, sizeof(nameSize)) ||
                packedPosition + nameSize > unpackedData.size()) {
                SetStatus("Desktop artifact contains an invalid file name.", true);
                return false;
            }
            SR_UTILS_NS::StringView name(unpackedData.data() + packedPosition, nameSize);
            packedPosition += nameSize;
            if (!ReadBinary(unpackedData, packedPosition, &contentSize, sizeof(contentSize)) ||
                packedPosition + contentSize > unpackedData.size()) {
                SetStatus("Desktop artifact contains invalid file data.", true);
                return false;
            }

            if (name.ends_with(".lib")) {
                packedPosition += contentSize;
                continue;
            }

            const SR_UTILS_NS::String outputName = i == 0
                ? SR_UTILS_NS::String(artifactPath.GetBaseNameAndExtView())
                : SR_UTILS_NS::String(name);
            if (outputName.size() > SR_UINT16_MAX) {
                SetStatus("Desktop artifact contains a file name that is too long.", true);
                return false;
            }
            const auto outputNameSize = static_cast<uint16_t>(outputName.size());
            AppendBinary(newPackedData, outputNameSize);
            newPackedData.append(outputName.data(), outputName.size());
            AppendBinary(newPackedData, contentSize);
            newPackedData.append(unpackedData.data() + packedPosition, contentSize);
            packedPosition += contentSize;
            ++newExecutableFileCount;
        }
        memcpy(newPackedData.data() + executableFileCountPosition, &newExecutableFileCount, sizeof(newExecutableFileCount));

        SR_MAYBE_UNUSED uint16_t oldResourceCount = 0;
        if (!ReadBinary(unpackedData, packedPosition, &oldResourceCount, sizeof(oldResourceCount))) {
            SetStatus("Desktop artifact contains invalid resource entries.", true);
            return false;
        }

        newPackedData.append(m_desktopPackedBinary.data(), m_desktopPackedBinary.size());

        uLongf newCompressedSize = compressBound(newPackedData.size());
        SR_UTILS_NS::String compressedData;
        compressedData.resize(newCompressedSize);
        if (compress2(
            reinterpret_cast<Bytef*>(compressedData.data()),
            &newCompressedSize,
            reinterpret_cast<const Bytef*>(newPackedData.data()),
            newPackedData.size(),
            Z_BEST_COMPRESSION
        ) != Z_OK) {
            SetStatus("Failed to compress desktop resources.", true);
            return false;
        }
        compressedData.resize(newCompressedSize);

        auto outputFile = SR_UTILS_NS::VFS::Instance().OpenFile(artifactPath, SR_UTILS_NS::FileMode::Write);
        if (!outputFile ||
            outputFile.Write(artifactData.data(), packedDataOffset) != packedDataOffset ||
            outputFile.Write(compressedData.data(), compressedData.size()) != compressedData.size() ||
            outputFile.Write(PackedDataMagic.data(), PackedDataMagic.size()) != PackedDataMagic.size()) {
            SetStatus("Failed to write repacked desktop artifact.", true);
            return false;
        }
        const uint64_t newDecompressedSize = newPackedData.size();
        const uint64_t finalCompressedSize = compressedData.size();
        if (outputFile.Write(&newDecompressedSize, sizeof(newDecompressedSize)) != sizeof(newDecompressedSize) ||
            outputFile.Write(&finalCompressedSize, sizeof(finalCompressedSize)) != sizeof(finalCompressedSize)) {
            SetStatus("Failed to finalize repacked desktop artifact.", true);
            return false;
        }
        outputFile.Flush();
        return true;
    }

    bool GameBuildExporter::RepackAndroid(const SR_UTILS_NS::Path& artifactPath) {
        SR_LOG("GameBuildExporter::RepackAndroid() : repacking \"{}\"...", artifactPath);

        auto apkFile = SR_UTILS_NS::VFS::Instance().OpenFile(artifactPath, SR_UTILS_NS::FileMode::Read);
        auto&& pArchive = SR_UTILS_NS::Archive::Load(apkFile);
        if (!pArchive) {
            SetStatus("Failed to open Android APK.", true);
            return false;
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::Archive::Entry> entries;
        pArchive->Enumerate([&entries](const SR_UTILS_NS::Archive::Entry& entry) {
            if (!entry.name.starts_with("assets/Resources/") && !entry.name.starts_with("META-INF/")) {
                entries.emplace_back(entry);
            }
        });

        SR_UTILS_NS::Vector<SR_UTILS_NS::String> apkNames;
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> resourceData;
        apkNames.reserve(m_resourcePaths.size());
        resourceData.reserve(m_resourcePaths.size());
        for (uint32_t i = 0; i < m_resourcePaths.size(); ++i) {
            auto file = SR_UTILS_NS::VFS::Instance().OpenFile(m_resourcePaths[i], SR_UTILS_NS::FileMode::Read);
            SR_UTILS_NS::String& data = resourceData.emplace_back();
            if (!file || !file.Read(data)) {
                SetStatus("Failed to read Android resource: {}"_format(m_resourcePaths[i]), true);
                return false;
            }
            apkNames.emplace_back("assets/Resources/{}"_format(m_resourcePaths[i]));
        }
        entries.reserve(entries.size() + resourceData.size());
        for (uint32_t i = 0; i < resourceData.size(); ++i) {
            entries.emplace_back(SR_UTILS_NS::Archive::Entry {
                .name = apkNames[i],
                .data = resourceData[i]
            });
        }

        apkFile = SR_UTILS_NS::File();
        if (!SR_UTILS_NS::Archive::SaveZip(artifactPath, entries)) {
            SetStatus("Failed to rebuild Android APK.", true);
            return false;
        }

        const auto keyStore = GetBuildCachePath().Concat("android-debug.keystore");
        if (!keyStore.IsFile()) {
            const SR_UTILS_NS::String result = SR_PLATFORM_NS::ExecuteCommand(
                "keytool -genkeypair -noprompt -keystore \"{}\" -storepass android -keypass android -alias androiddebugkey -dname \"CN=Android Debug,O=Android,C=US\" -keyalg RSA -keysize 2048 -validity 10000"_format(keyStore),
                { }
            );
            if (!keyStore.IsFile()) {
                SetStatus("Failed to create Android debug key. Install a JDK with keytool available in PATH. {}"_format(result), true);
                return false;
            }
        }

        SR_PLATFORM_NS::ExecuteCommand(
            "jarsigner -keystore \"{}\" -storepass android -keypass android -sigalg SHA256withRSA -digestalg SHA-256 \"{}\" androiddebugkey"_format(keyStore, artifactPath),
            { }
        );
        const SR_UTILS_NS::String verifyResult = SR_PLATFORM_NS::ExecuteCommand("jarsigner -verify \"{}\""_format(artifactPath), { });
        if (!verifyResult.contains("jar verified")) {
            SetStatus("Failed to sign Android APK. Install a JDK with jarsigner available in PATH. {}"_format(verifyResult), true);
            return false;
        }
        return true;
    }

    bool GameBuildExporter::RepackEmscripten(const SR_UTILS_NS::Path& artifactPath) {
        SR_LOG("GameBuildExporter::RepackEmscripten() : repacking \"{}\"...", artifactPath);

        auto zipFile = SR_UTILS_NS::VFS::Instance().OpenFile(artifactPath, SR_UTILS_NS::FileMode::Read);
        auto&& pArchive = SR_UTILS_NS::Archive::Load(zipFile);
        if (!pArchive) {
            SetStatus("Failed to open Emscripten archive.", true);
            return false;
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::String> names;
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> data;
        int32_t javascriptIndex = -1;
        int32_t dataIndex = -1;
        pArchive->Enumerate([&](const SR_UTILS_NS::Archive::Entry& entry) {
            if (entry.isDirectory || entry.name.ends_with(".zip")) {
                return;
            }
            names.emplace_back(entry.name);
            data.emplace_back(entry.data);
            const int32_t index = static_cast<int32_t>(names.size() - 1);
            if (entry.name.ends_with("SREngine.js")) {
                javascriptIndex = index;
            }
            else if (entry.name.ends_with("SREngine.data")) {
                dataIndex = index;
            }
        });
        if (javascriptIndex < 0 || dataIndex < 0) {
            SetStatus("Emscripten archive does not contain SREngine.js and SREngine.data.", true);
            return false;
        }

        SR_UTILS_NS::String webData;
        SR_UTILS_NS::String metadata = "loadPackage({files:[";
        for (uint32_t i = 0; i < m_resourcePaths.size(); ++i) {
            auto file = SR_UTILS_NS::VFS::Instance().OpenFile(m_resourcePaths[i], SR_UTILS_NS::FileMode::Read);
            SR_UTILS_NS::String resourceData;
            if (!file || !file.Read(resourceData)) {
                SetStatus("Failed to read Emscripten resource: {}"_format(m_resourcePaths[i]), true);
                return false;
            }
            const uint64_t start = webData.size();
            webData.append(resourceData.data(), resourceData.size());
            if (i != 0) {
                metadata += ',';
            }
            metadata += "{";
            metadata += "filename:\"/Resources/{}\",start:{},end:{}"_format(m_resourcePaths[i], start, webData.size());
            metadata += "}";
        }
        metadata += "],remote_package_size:{}"_format(webData.size());
        metadata += "})";

        auto&& javascript = data[javascriptIndex];
        const auto metadataBegin = javascript.find("loadPackage({files:[");
        const auto sizeBegin = javascript.find("],remote_package_size:", metadataBegin);
        const auto metadataEnd = sizeBegin == SR_UTILS_NS::String::npos ? SR_UTILS_NS::String::npos : javascript.find("})", sizeBegin);
        if (metadataBegin == SR_UTILS_NS::String::npos || sizeBegin == SR_UTILS_NS::String::npos || metadataEnd == SR_UTILS_NS::String::npos) {
            SetStatus("Emscripten JavaScript has an unknown preload metadata format.", true);
            return false;
        }
        javascript = javascript.substr(0, metadataBegin) + metadata + javascript.substr(metadataEnd + 2);

        const SR_UTILS_NS::String createFile = "Module[\"FS_createDataFile\"](name,null,data,true,true,true);";
        const auto createFilePosition = javascript.find(createFile);
        if (createFilePosition != SR_UTILS_NS::String::npos) {
            const SR_UTILS_NS::String createDirectories =
                "var fp=name.split(\"/\");var fd=\"/\";for(var fi=1;fi+1<fp.length;++fi){"
                "Module[\"FS_createPath\"](fd,fp[fi],true,true);fd+=fp[fi]+\"/\";}";
            javascript = javascript.substr(0, createFilePosition) + createDirectories + createFile +
                javascript.substr(createFilePosition + createFile.size());
        }
        data[dataIndex] = webData;

        SR_UTILS_NS::Vector<SR_UTILS_NS::Archive::Entry> entries;
        entries.reserve(names.size());
        for (uint32_t i = 0; i < names.size(); ++i) {
            entries.emplace_back(SR_UTILS_NS::Archive::Entry { .name = names[i], .data = data[i] });
        }
        zipFile = SR_UTILS_NS::File();
        if (!SR_UTILS_NS::Archive::SaveZip(artifactPath, entries)) {
            SetStatus("Failed to rebuild Emscripten archive.", true);
            return false;
        }
        return true;
    }

    bool GameBuildExporter::ExportPlatform(SR_UTILS_NS::StringView platformName, SR_UTILS_NS::StringView assetName) {
        SR_INFO("GameBuildExporter::ExportPlatform() : exporting {} platform...", platformName);
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
            if (!SR_PLATFORM_NS::DownloadFile(url.c_str(), cachedArtifact)) {
                SetStatus("Failed to download {} build."_format(platformName), true);
                return false;
            }
        }

        auto outputPath = m_outputRoot.Concat(platformName);
        if (!outputPath.CreateDirectories()) {
            SetStatus("Failed to create output directory for {}."_format(platformName), true);
            return false;
        }

        const SR_UTILS_NS::String projectFileName = SR_UTILS_NS::Path(m_pProjectSettings->projectName.ToString()).ConvertToFileName();
        SR_UTILS_NS::String outputFileName;
        if (platformName == "Windows") {
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

        return true;
    }

    bool GameBuildExporter::Build() {
        auto&& pProfile = GetActiveProfile();
        if (!pProfile) {
            SetStatus("No active build profile.", true);
            return false;
        }

        const auto version = SR_UTILS_NS::String(SR_ENGINE_VERSION);
        const bool latest = GetReleaseTag() == "dev-latest";
        const auto suffix = latest ? "-dev" : "";

        if (!m_pProjectSettings->SaveAsset()) {
            SetStatus("Failed to save project settings before build.", true);
            return false;
        }

        m_outputRoot = CoreResLoader::GetResPath();
        SR_UTILS_NS::VFS::Instance().ResolvePath(m_outputRoot, SR_UTILS_NS::FileMode::Write);
        m_outputRoot = m_outputRoot.GetPrevious().Concat(pProfile->outputPath);

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

        if (!CollectBuildResources(m_resourcePaths)) {
            SetStatus("Project contains too many resource files.", true);
            return false;
        }

        if (pProfile->windows || pProfile->linux) {
            SR_TRACY_ZONE_N("Desktop packing");
            m_desktopPackedBinary.clear();
            m_desktopPackedBinary.shrink_to_fit();
            const auto resourceCount = static_cast<uint16_t>(m_resourcePaths.size());
            AppendBinary(m_desktopPackedBinary, resourceCount);
            SR_UTILS_NS::String resourceData;
            SR_UTILS_NS::String resourceName;
            for (uint16_t i = 0; i < resourceCount; ++i) {
                auto resourceFile = SR_UTILS_NS::VFS::Instance().OpenFile(m_resourcePaths[i], SR_UTILS_NS::FileMode::Read);
                if (!resourceFile || !resourceFile.Read(resourceData)) {
                    SetStatus("Failed to read resource: {}"_format(m_resourcePaths[i]), true);
                    return false;
                }

                resourceName = m_resourcePaths[i] == ".srproject"
                    ? SR_UTILS_NS::StringView("../.srproject")
                    : SR_UTILS_NS::StringView(m_resourcePaths[i]);
                if (resourceName.starts_with("Resources/")) {
                    resourceName = resourceName.substr(10);
                }

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
            }
        }

        bool success = true;
        if (pProfile->windows) {
            success &= ExportPlatform("Windows", "SREngine_v{}{}_windows.x86_64.exe"_format(version, suffix));
        }
        if (pProfile->linux) {
            success &= ExportPlatform("Linux", "SREngine_v{}{}_linux.x86_64"_format(version, suffix));
        }
        if (pProfile->androidArm64) {
            success &= ExportPlatform("Android", "SREngine_v{}{}_android.arm64-v8a.apk"_format(version, suffix));
        }
        if (pProfile->androidX64) {
            success &= ExportPlatform("Android", "SREngine_v{}{}_android.x86_64.apk"_format(version, suffix));
        }
        if (pProfile->emscripten) {
            success &= ExportPlatform("Emscripten", "SREngine_v{}{}_emscripten.zip"_format(version, suffix));
        }

        if (success) {
            if (!m_pProjectSettings->SaveAsset()) {
                SetStatus("Builds were exported, but project settings could not be saved.", true);
                return false;
            }
            SetStatus("Build completed.");
        }
        return success;
    }

    void GameBuildExporter::Draw() {
        if (!LoadProjectSettings()) {
            SR_IMMEDIATE_GUI_NS::TextWrapped("%s", m_status.c_str());
            return;
        }

        auto&& pProfile = GetActiveProfile();
        if (!pProfile) {
            SR_IMMEDIATE_GUI_NS::Text("Is not a valid project. Please check the .srproject file.");
            return;
        }

        SR_IMMEDIATE_GUI_NS::Text("Engine branch: %s", SR_ENGINE_BRANCH);
        SR_IMMEDIATE_GUI_NS::Text("Release source: %s", GetReleaseTag().c_str());
        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::BeginCombo("Configuration", pProfile->name.c_str())) {
            for (uint32_t i = 0; i < m_pProjectSettings->buildProfiles.size(); ++i) {
                if (SR_IMMEDIATE_GUI_NS::Selectable(
                    m_pProjectSettings->buildProfiles[i].name.c_str(),
                    i == m_pProjectSettings->activeBuildProfile
                )) {
                    m_pProjectSettings->activeBuildProfile = i;
                    pProfile = GetActiveProfile();
                }
            }
            SR_IMMEDIATE_GUI_NS::EndCombo();
        }
        if (SR_IMMEDIATE_GUI_NS::Button("New configuration")) {
            auto copy = *pProfile;
            copy.name = "New configuration";
            m_pProjectSettings->buildProfiles.emplace_back(copy);
            m_pProjectSettings->activeBuildProfile = m_pProjectSettings->buildProfiles.size() - 1;
            pProfile = GetActiveProfile();
        }
        SR_IMMEDIATE_GUI_NS::SameLine();
        if (m_pProjectSettings->buildProfiles.size() > 1 && SR_IMMEDIATE_GUI_NS::Button("Delete configuration")) {
            m_pProjectSettings->buildProfiles.erase(
                m_pProjectSettings->buildProfiles.begin() + m_pProjectSettings->activeBuildProfile
            );
            m_pProjectSettings->activeBuildProfile = 0;
            pProfile = GetActiveProfile();
        }

        SR_IMMEDIATE_GUI_NS::InputText("Profile", &pProfile->name);
        SR_IMMEDIATE_GUI_NS::InputText("Organization", &pProfile->organization);
        SR_IMMEDIATE_GUI_NS::InputText("Output", &pProfile->outputPath.GetInternalUnsafeString());
        SR_IMMEDIATE_GUI_NS::InputText("Start scene", &m_pProjectSettings->mainScene.GetInternalUnsafeString());
        int32_t buildConfiguration = static_cast<int32_t>(pProfile->configuration);
        if (SR_IMMEDIATE_GUI_NS::Combo("Build type", &buildConfiguration, "Release\0Debug\0")) {
            pProfile->configuration = static_cast<GameBuildConfiguration>(buildConfiguration);
        }
        int32_t desktopPackageMode = static_cast<int32_t>(pProfile->desktopPackageMode);
        if (SR_IMMEDIATE_GUI_NS::Combo("Desktop package", &desktopPackageMode, "Monolithic\0Portable ZIP\0")) {
            pProfile->desktopPackageMode = static_cast<DesktopBuildPackageMode>(desktopPackageMode);
        }
        SR_IMMEDIATE_GUI_NS::Checkbox("Windows", &pProfile->windows);
        SR_IMMEDIATE_GUI_NS::Checkbox("Linux", &pProfile->linux);
        SR_IMMEDIATE_GUI_NS::Checkbox("Android arm64-v8a", &pProfile->androidArm64);
        SR_IMMEDIATE_GUI_NS::Checkbox("Android x86_64", &pProfile->androidX64);
        SR_IMMEDIATE_GUI_NS::Checkbox("Emscripten", &pProfile->emscripten);
        SR_IMMEDIATE_GUI_NS::InputText("Android package ID", &pProfile->androidPackageId);
        auto versionCode = static_cast<int32_t>(pProfile->androidVersionCode);
        if (SR_IMMEDIATE_GUI_NS::InputInt("Android version code", &versionCode)) {
            pProfile->androidVersionCode = static_cast<uint32_t>(versionCode > 0 ? versionCode : 1);
        }
        SR_IMMEDIATE_GUI_NS::Checkbox("Create platform archives", &pProfile->createPlatformArchives);
        SR_IMMEDIATE_GUI_NS::Checkbox("Enable web preview", &pProfile->enableWebPreview);
        SR_IMMEDIATE_GUI_NS::Checkbox("Pack editor", &pProfile->packEditor);
        SR_IMMEDIATE_GUI_NS::Separator();

        if (m_cppScriptsFound) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.7f, 0.f, 1.f), "C++ scripts are not supported and will be excluded.");
        }

        if (m_pProjectSettings->mainScene.empty()) {
            SR_IMMEDIATE_GUI_NS::WarningBox("Main scene isn't selected!");
            return;
        }

        if (SR_IMMEDIATE_GUI_NS::ButtonColored("Build", SR_MATH_NS::FColor::Green() * 0.65, SR_MATH_NS::FVector2(160.f, 36.f))) {
            Build();
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (SR_IMMEDIATE_GUI_NS::ButtonColored("Delete artifacts", SR_MATH_NS::FColor::Red() * 0.65, SR_MATH_NS::FVector2(160.f, 36.f))) {
            auto&& cachedArtifacts = GetBuildCachePath();
            SR_UTILS_NS::VFS::Instance().Delete(cachedArtifacts);
        }

        if (!m_status.empty()) {
            const auto color = m_statusError
                ? SR_MATH_NS::FColor(1.f, 0.25f, 0.25f, 1.f)
                : SR_MATH_NS::FColor(0.35f, 1.f, 0.45f, 1.f);
            SR_IMMEDIATE_GUI_NS::TextColored(color, "%s", m_status.c_str());
        }
    }
}
