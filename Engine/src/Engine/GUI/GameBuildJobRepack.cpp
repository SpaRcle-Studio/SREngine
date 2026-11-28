//
// Created by OpenAI Codex on 12.11.2026.
//

#include <Engine/GUI/GameBuildJob.h>
#include <Engine/GUI/GameBuildRuntime.h>

#include <Graphics/Loaders/TextureLoader.h>

#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Platform/AndroidResources.h>
#include <Utils/FileSystem/Archive.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Platform/AndroidManifest.h>
#include <Utils/Common/Hashes.h>
#include <zlib/zlib.h>

namespace SR_CORE_GUI_NS {
    bool GameBuildJob::ReadBinary(SR_UTILS_NS::StringView data, SR_UTILS_NS::SizeType& position, void* pValue, SR_UTILS_NS::SizeType size) {
        if (position > data.size() || size > data.size() - position) {
            return false;
        }
        memcpy(pValue, data.data() + position, size);
        position += size;
        return true;
    }

    bool GameBuildJob::RepackDesktop(const SR_UTILS_NS::Path& artifactPath) {
        SR_LOG("GameBuildJob::RepackDesktop() : repacking \"{}\"...", artifactPath);

        auto artifactFile = SR_UTILS_NS::VFS::Instance().OpenFile(artifactPath, SR_UTILS_NS::FileMode::Read);
        SR_UTILS_NS::String artifactData;
        if (!artifactFile || !artifactFile.Read(artifactData)) {
            SetStatus("Failed to read desktop artifact.", true);
            return false;
        }

        if (GetActiveProfile()->desktopPackageMode == DesktopBuildPackageMode::Monolithic) {
            const auto footerSize = ResourceDataMagic.size() + sizeof(uint64_t) * 2;
            if (artifactData.size() < footerSize ||
                SR_UTILS_NS::StringView(artifactData.data() + artifactData.size() - footerSize, ResourceDataMagic.size()) != ResourceDataMagic) {
                SetStatus("Monolithic engine artifact has an unknown resource format.", true);
                return false;
            }
            SR_UTILS_NS::SizeType position = artifactData.size() - sizeof(uint64_t);
            uint64_t oldCompressedSize = 0;
            if (!ReadBinary(artifactData, position, &oldCompressedSize, sizeof(oldCompressedSize)) ||
                oldCompressedSize > artifactData.size() - footerSize) {
                SetStatus("Monolithic engine artifact has invalid resource sizes.", true);
                return false;
            }
            artifactData.resize(artifactData.size() - footerSize - oldCompressedSize);
            if (artifactPath.GetExtensionView() == "exe" &&
                !ApplyExecutableIcon(artifactPath.GetPrevious().Concat("IconPatch.exe"), artifactData))
            {
                return false;
            }
            if (m_desktopPackedBinary.size() > SR_UINT32_MAX) {
                SetStatus("Monolithic resources exceed the supported archive size.", true);
                return false;
            }
            SR_UTILS_NS::String compressed;
            compressed.reserve(compressBound(m_desktopPackedBinary.size()));
            z_stream stream{};
            if (deflateInit(&stream, Z_BEST_COMPRESSION) != Z_OK) {
                SetStatus("Failed to compress monolithic resources.", true);
                return false;
            }
            uint8_t buffer[65536];
            uint64_t inputOffset = 0;
            int32_t result = Z_OK;
            auto lastProgress = std::chrono::steady_clock::now();
            while (result != Z_STREAM_END) {
                if (isCancelled && isCancelled()) {
                    deflateEnd(&stream);
                    return false;
                }
                if (stream.avail_in == 0 && inputOffset < m_desktopPackedBinary.size()) {
                    const auto count = static_cast<uInt>(std::min(uint64_t(1048576), static_cast<uint64_t>(m_desktopPackedBinary.size()) - inputOffset));
                    stream.next_in = reinterpret_cast<Bytef*>(m_desktopPackedBinary.data() + inputOffset);
                    stream.avail_in = count;
                    inputOffset += count;
                }
                stream.next_out = buffer;
                stream.avail_out = sizeof(buffer);
                result = deflate(&stream, inputOffset == m_desktopPackedBinary.size() ? Z_FINISH : Z_NO_FLUSH);
                if (result != Z_OK && result != Z_STREAM_END) {
                    deflateEnd(&stream);
                    SetStatus("Failed to compress monolithic resources.", true);
                    return false;
                }
                compressed.append(reinterpret_cast<const char*>(buffer), sizeof(buffer) - stream.avail_out);
                const auto now = std::chrono::steady_clock::now();
                if (result == Z_STREAM_END || now - lastProgress >= std::chrono::milliseconds(100)) {
                    SetProgress(std::min(0.99f, static_cast<float_t>(stream.total_in) / static_cast<float_t>(m_desktopPackedBinary.size())));
                    lastProgress = now;
                }
            }
            deflateEnd(&stream);
            artifactFile = SR_UTILS_NS::File();
            auto output = SR_UTILS_NS::VFS::Instance().OpenFile(artifactPath, SR_UTILS_NS::FileMode::Write);
            const uint64_t dataSize = m_desktopPackedBinary.size();
            const uint64_t packedSize = compressed.size();
            if (!output || output.Write(artifactData.data(), artifactData.size()) != artifactData.size() ||
                output.Write(compressed.data(), compressed.size()) != compressed.size() ||
                output.Write(ResourceDataMagic.data(), ResourceDataMagic.size()) != ResourceDataMagic.size() ||
                output.Write(&dataSize, sizeof(dataSize)) != sizeof(dataSize) ||
                output.Write(&packedSize, sizeof(packedSize)) != sizeof(packedSize)) {
                SetStatus("Failed to write monolithic executable.", true);
                return false;
            }
            output.Flush();
            return true;
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
            compressedSize > footerOffset || compressedSize > SR_UINT32_MAX ||
            decompressedSize == 0 || decompressedSize > SR_UINT32_MAX) {
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
        if (!ReadBinary(unpackedData, packedPosition, &executableFileCount, sizeof(executableFileCount)) || executableFileCount == 0) {
            SetStatus("Desktop artifact contains invalid file entries.", true);
            return false;
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::String> zipNames;
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> zipData;
        for (uint16_t i = 0; i < executableFileCount; ++i) {
            uint16_t nameSize = 0;
            uint64_t contentSize = 0;
            if (!ReadBinary(unpackedData, packedPosition, &nameSize, sizeof(nameSize)) ||
                nameSize > unpackedData.size() - packedPosition) {
                SetStatus("Desktop artifact contains an invalid file name.", true);
                return false;
            }
            SR_UTILS_NS::StringView name(unpackedData.data() + packedPosition, nameSize);
            packedPosition += nameSize;
            if (!ReadBinary(unpackedData, packedPosition, &contentSize, sizeof(contentSize)) ||
                contentSize > unpackedData.size() - packedPosition) {
                SetStatus("Desktop artifact contains invalid file data.", true);
                return false;
            }

            if (name.ends_with(".lib")) {
                packedPosition += contentSize;
                continue;
            }

            const SR_UTILS_NS::String outputName = i == 0
                ? "{}{}"_format(artifactPath.GetBaseNameView(), name.ends_with(".exe") ? ".exe" : "")
                : SR_UTILS_NS::String(name);
            zipNames.emplace_back(outputName);
            zipData.emplace_back(SR_UTILS_NS::StringView(unpackedData.data() + packedPosition, contentSize));
            if (outputName.size() > SR_UINT16_MAX) {
                SetStatus("Desktop artifact contains a file name that is too long.", true);
                return false;
            }
            packedPosition += contentSize;
        }

        SR_MAYBE_UNUSED uint16_t oldResourceCount = 0;
        if (!ReadBinary(unpackedData, packedPosition, &oldResourceCount, sizeof(oldResourceCount))) {
            SetStatus("Desktop artifact contains invalid resource entries.", true);
            return false;
        }

        for (auto&& path : m_resourcePaths) {
            SR_UTILS_NS::String data;
            if (!ReadBuildResource(path, data)) {
                SetStatus("Failed to read portable resource: {}"_format(path), true);
                return false;
            }
            zipNames.emplace_back(path == ".srproject" ? SR_UTILS_NS::String(".srproject") :
                "Resources/{}"_format(path.ToStringView().starts_with("Resources/") ? path.ToStringView().substr(10) : path.ToStringView()));
            zipData.emplace_back(std::move(data));
        }

        if (!zipNames.empty() && zipNames.front().ends_with(".exe")) {
            if (!ApplyExecutableIcon(artifactPath.GetPrevious().Concat("IconPatch.exe"), zipData.front())) {
                return false;
            }
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::Archive::Entry> zipEntries;
        for (uint32_t i = 0; i < zipNames.size(); ++i) {
            zipEntries.emplace_back(SR_UTILS_NS::Archive::Entry{
                .name = zipNames[i], .data = zipData[i], .isExecutable = i == 0
            });
        }
        artifactFile = SR_UTILS_NS::File();
        return SR_UTILS_NS::Archive::SaveZip(artifactPath, zipEntries);
    }

    bool GameBuildJob::RepackAndroid(const SR_UTILS_NS::Path& artifactPath) {
        SR_LOG("GameBuildJob::RepackAndroid() : repacking \"{}\"...", artifactPath);

        auto apkFile = SR_UTILS_NS::VFS::Instance().OpenFile(artifactPath, SR_UTILS_NS::FileMode::Read);
        auto&& pArchive = SR_UTILS_NS::Archive::Load(apkFile);
        if (!pArchive) {
            SetStatus("Failed to open Android APK.", true);
            return false;
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::Archive::Entry> entries;
        pArchive->Enumerate([&entries](const SR_UTILS_NS::Archive::Entry& entry) {
            if (!entry.name.starts_with("assets/Resources/") && entry.name != "assets/.srproject" && !entry.name.starts_with("META-INF/")) {
                entries.emplace_back(entry);
                if (entry.name == "resources.arsc" || (entry.name.starts_with("lib/") && entry.name.ends_with(".so"))) {
                    entries.back().compress = false;
                }
            }
        });

        SR_UTILS_NS::String manifest;
        bool manifestFound = false;
        for (auto&& entry : entries) {
            if (entry.name != "AndroidManifest.xml") {
                continue;
            }
            SR_UTILS_NS::String error;
            if (!SR_UTILS_NS::RewriteAndroidManifestPackage(entry.data, GetActiveProfile()->androidPackageId, manifest, error)) {
                SetStatus(std::move(error), true);
                return false;
            }
            entry.data = manifest;
            manifestFound = true;
            break;
        }
        if (!manifestFound) {
            SetStatus("Android APK has no AndroidManifest.xml.", true);
            return false;
        }

        SR_UTILS_NS::String resourceTable;
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> iconImages;
        if (!ApplyAndroidIcon(entries, resourceTable, iconImages)) {
            return false;
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::String> apkNames;
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> resourceData;
        apkNames.reserve(m_resourcePaths.size());
        resourceData.reserve(m_resourcePaths.size());
        for (uint32_t i = 0; i < m_resourcePaths.size(); ++i) {
            auto&& data = resourceData.emplace_back();
            if (!ReadBuildResource(m_resourcePaths[i], data)) {
                SetStatus("Failed to read Android resource: {}"_format(m_resourcePaths[i]), true);
                return false;
            }
            const auto path = m_resourcePaths[i].ToStringView();
            apkNames.emplace_back(path == ".srproject" ? SR_UTILS_NS::String("assets/.srproject") :
                "assets/Resources/{}"_format(path.starts_with("Resources/") ? path.substr(10) : path));
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

        const auto keyStore = GameBuildRuntime::GetToolsPath().Concat("Android/android-debug.keystore");
        const auto legacyKeyStore = GetBuildCachePath().Concat("android-debug.keystore");
        if (!keyStore.IsFile() && legacyKeyStore.IsFile() && !legacyKeyStore.Copy(keyStore)) {
            SetStatus("Failed to migrate Android signing key.", true);
            return false;
        }
        SR_PLATFORM_NS::AndroidSDK sdk(GameBuildRuntime::GetToolsPath());
        sdk.isCancelled = isCancelled;
        sdk.onProgress = [this](float_t progress) {
            SetProgress(progress);
        };
        sdk.onDownloadProgress = onDownload;
        sdk.onMessage = [this](SR_UTILS_NS::String text, bool error) {
            SetStatus(std::move(text), error);
        };
        if (!sdk.Sign(artifactPath, keyStore)) {
            return false;
        }
        return sdk.CheckPackage(artifactPath, GetActiveProfile()->androidPackageId);
    }

    bool GameBuildJob::RepackEmscripten(const SR_UTILS_NS::Path& artifactPath) {
        SR_LOG("GameBuildJob::RepackEmscripten() : repacking \"{}\"...", artifactPath);

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
            SR_UTILS_NS::String resourceData;
            if (!ReadBuildResource(m_resourcePaths[i], resourceData)) {
                SetStatus("Failed to read Emscripten resource: {}"_format(m_resourcePaths[i]), true);
                return false;
            }
            const uint64_t start = webData.size();
            webData.append(resourceData.data(), resourceData.size());
            if (i != 0) {
                metadata += ',';
            }
            metadata += "{";
            const auto path = m_resourcePaths[i].ToStringView();
            const SR_UTILS_NS::String target = path == ".srproject" ? SR_UTILS_NS::String("/.srproject") :
                "/Resources/{}"_format(path.starts_with("Resources/") ? path.substr(10) : path);
            metadata += "filename:\"{}\",start:{},end:{}"_format(target, start, webData.size());
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

        // Repacking changes JS and data, so their cache keys must change with the exported project.
        SR_UTILS_NS::String manifest = "{\"files\":{";
        bool firstAsset = true;
        for (uint32_t i = 0; i < names.size(); ++i) {
            const char* asset = names[i].ends_with("SREngine.js") ? "SREngine.js"
                : names[i].ends_with("SREngine.wasm") ? "SREngine.wasm"
                : names[i].ends_with("SREngine.data") ? "SREngine.data" : nullptr;
            if (!asset) {
                continue;
            }
            if (!firstAsset) {
                manifest += ',';
            }
            firstAsset = false;
            manifest += "\"{}\":\"{:016x}\""_format(asset, SR_UTILS_NS::HashArrayRepresentation(data[i].data(), data[i].size()));
        }
        manifest += "}}";
        bool manifestFound = false;
        for (uint32_t i = 0; i < names.size(); ++i) {
            if (names[i].ends_with("SREngine.manifest.json")) {
                data[i] = manifest;
                manifestFound = true;
            }
        }
        if (!manifestFound) {
            names.emplace_back(names[javascriptIndex].substr(0, names[javascriptIndex].size() - SR_UTILS_NS::StringView("SREngine.js").size()) + "SREngine.manifest.json");
            data.emplace_back(std::move(manifest));
        }

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

    bool GameBuildJob::ApplyExecutableIcon(const SR_UTILS_NS::Path& temporaryPath, SR_UTILS_NS::String& executable) {
        if (!m_icon.IsValid()) {
            return true;
        }

        SR_TRACY_ZONE;

        if (SR_PLATFORM_NS::GetType() != SR_UTILS_NS::PlatformType::Windows) {
            SetStatus("The Windows executable icon can only be set when exporting from Windows. The default icon is kept.");
            return true;
        }

        const auto icon = m_icon.EncodeIco();
        if (icon.empty()) {
            SetStatus("Failed to encode the game icon.", true);
            return false;
        }

        if (!SR_UTILS_NS::VFS::Instance().WriteFileAtomic(temporaryPath, executable)) {
            SetStatus("Failed to stage the Windows executable for the icon.", true);
            return false;
        }

        const bool applied = SR_PLATFORM_NS::SetExecutableIcon(temporaryPath, icon) &&
            SR_UTILS_NS::FileSystem::ReadFile(temporaryPath, executable);
        SR_UTILS_NS::VFS::Instance().Delete(temporaryPath);

        if (!applied) {
            SetStatus("Failed to set the Windows executable icon.", true);
            return false;
        }

        return true;
    }

    bool GameBuildJob::ApplyAndroidIcon(SR_UTILS_NS::Vector<SR_UTILS_NS::Archive::Entry>& entries, SR_UTILS_NS::String& resourceTable,
        SR_UTILS_NS::Vector<SR_UTILS_NS::String>& images)
    {
        if (!m_icon.IsValid()) {
            return true;
        }

        SR_TRACY_ZONE;
        static constexpr std::array<SR_UTILS_NS::StringView, 2> iconNames = { "ic_launcher", "ic_launcher_round" };

        SR_UTILS_NS::Archive::Entry* pTableEntry = nullptr;
        for (auto&& entry : entries) {
            if (entry.name == "resources.arsc") {
                pTableEntry = &entry;
                break;
            }
        }

        SR_UTILS_NS::AndroidResourceTable table;
        if (!pTableEntry || !table.Load(pTableEntry->data)) {
            SetStatus("Android APK has an unsupported resources.arsc. The game icon was not applied.", true);
            return false;
        }

        /// File names in release APKs are obfuscated, so the launcher bitmaps are found through the resource table.
        /// Adaptive icons draw the template layers, they are dropped so the launcher uses the bitmaps.
        SR_UTILS_NS::Vector<SR_UTILS_NS::String> files;
        for (const auto name : iconNames) {
            table.RemoveFiles("mipmap", name, ".xml");
            for (auto&& path : table.GetFiles("mipmap", name)) {
                if (!path.ends_with(".xml")) {
                    files.emplace_back(path);
                }
            }
        }

        if (files.empty()) {
            SetStatus("Android APK has no launcher icon bitmaps. The game icon was not applied.", true);
            return false;
        }

        images.reserve(files.size());
        for (auto&& entry : entries) {
            bool isIcon = false;
            for (auto&& path : files) {
                isIcon |= entry.name == path.ToStringView();
            }
            if (!isIcon || images.size() == files.size()) {
                continue;
            }

            uint32_t width = 192;
            uint32_t height = 192;
            SR_GRAPH_NS::TextureSourceInfo info;
            if (SR_GRAPH_NS::TextureLoader::ReadSourceInfo(entry.data, info) && info.width > 0 && info.height > 0) {
                width = info.width;
                height = info.height;
            }

            auto&& image = images.emplace_back(m_icon.EncodePng(width, height));
            if (image.empty()) {
                SetStatus("Failed to encode the Android icon.", true);
                return false;
            }
            entry.data = image;
        }

        resourceTable = table.GetData();
        pTableEntry->data = resourceTable;

        return true;
    }
}
