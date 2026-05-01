//
// Created by Monika on 13.05.2025.
//

std::vector<std::string> GetPackFiles(const std::string& executablePath) {
    std::cout << "GetPackFiles() : packing files...\n";

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::vector<std::string> files;

    files.emplace_back(executablePath);

    for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".dll" || entry.path().extension() == ".so" || entry.path().extension() == ".dylib") {
                files.emplace_back(absolute(entry.path()).string());
            }
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(currentPath / "../Lib")) {
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".lib") {
                files.emplace_back(absolute(entry.path()).string());
            }
        }
    }

    return files;
}

// Утилита: заменяет "*" и "?" на regex-подобный шаблон
std::string wildcardToRegex(const std::string& mask) {
    std::string regex;
    for (char c : mask) {
        switch (c) {
            case '*': regex += ".*"; break;
            case '?': regex += "."; break;
            case '.': regex += "\\."; break;
            case '\\': regex += "/"; break; // normalize slashes
            default: regex += c;
        }
    }
    return "^" + regex + "$";
}

bool IsExcluded(const std::filesystem::path& relPath, const std::vector<std::regex>& excludePatterns) {
    std::string pathStr = relPath.generic_string();  // always forward slashes
    for (const auto& pattern : excludePatterns) {
        if (std::regex_match(pathStr, pattern)) {
            return true;
        }
    }
    return false;
}

std::vector<std::regex> LoadExcludeMask(std::filesystem::path resourcesPath) {
    std::vector<std::regex> excludeMasks;

    auto&& filePath = resourcesPath  / "Engine/Configs/PackExcludeSettings.conf";

    if (std::filesystem::exists(filePath)) {
        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string line;
            bool isAllowedPlatform = false;
            while (std::getline(file, line)) {
                if (line == "[All]") {
                    isAllowedPlatform = true;
                    continue;
                }
                if (line == "[Windows]") {
                    isAllowedPlatform = SR_IS_WINDOWS;
                    continue;
                }
                if (line == "[Linux]") {
                    isAllowedPlatform = SR_IS_LINUX;
                    continue;
                }
                if (line == "[MacOS]") {
                    isAllowedPlatform = SR_IS_MACOS;
                    continue;
                }
                if (line == "[Emscripten]") {
                    isAllowedPlatform = SR_IS_EMSCRIPTEN;
                    continue;
                }
                if (isAllowedPlatform) {
                    excludeMasks.emplace_back(wildcardToRegex(line), std::regex::icase);
                }
            }
            file.close();
        }
    }

    return excludeMasks;
}

std::vector<std::string> GetResourcesPackFiles() {
    std::cout << "GetResourcesPackFiles() : packing resources...\n";

    namespace fs = std::filesystem;

    fs::path resourcesPath = absolute(fs::current_path() / "../../Resources");
    std::vector<std::string> files;

    const auto excludePatterns = LoadExcludeMask(resourcesPath);

    /// recursive
    for (auto pIt = fs::recursive_directory_iterator(resourcesPath); pIt != fs::recursive_directory_iterator(); ++pIt) {
        const auto& entry = *pIt;
        fs::path relPath = std::filesystem::relative(entry.path(), resourcesPath);

        if (IsExcluded(relPath, excludePatterns)) {
            if (entry.is_directory()) {
                pIt.disable_recursion_pending();
            }
            continue;
        }

        if (entry.is_regular_file()) {
            files.emplace_back(absolute(entry.path()).string());
        }
    }

    return files;
}

std::vector<char> CompressData(const std::vector<char>& data) {
    if (data.empty()) {
        return {};
    }

    uLongf compressedSize = compressBound(data.size());
    std::vector<char> compressedData(compressedSize);

    int result = compress(reinterpret_cast<Bytef*>(compressedData.data()), &compressedSize, reinterpret_cast<const Bytef*>(data.data()), data.size());

    if (result != Z_OK) {
        throw std::runtime_error("CompressData() : zlib compression failed with error code " + std::to_string(result));
    }

    compressedData.resize(compressedSize);
    return compressedData;
}

bool PackFile(std::vector<char>& archive, const std::string& path, bool isResource) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "PackFile() : failed to open file: " << path << "\n";
        return false;
    }

    const std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> fileData(size);
    if (!file.read(fileData.data(), size)) {
        std::cerr << "PackFile() : failed to read file: " << path << "\n";
        return false;
    }

    std::string name;

    if (isResource) {
        std::filesystem::path resourcesPath = absolute(std::filesystem::current_path() / "../../Resources");
        std::filesystem::path relPath = std::filesystem::relative(path, resourcesPath);
        name = relPath.generic_string();  // always forward slashes
    }
    else {
        name = std::filesystem::path(path).filename().string();
    }

    const auto nameLen = static_cast<uint16_t>(name.size());
    const uint64_t dataLen = fileData.size();

    const uint64_t newSize = archive.size() + sizeof(nameLen) + nameLen + sizeof(dataLen) + dataLen;
    if (newSize > archive.capacity()) {
        archive.reserve(newSize * 2);
    }

    archive.insert(archive.end(), reinterpret_cast<const char*>(&nameLen), reinterpret_cast<const char*>(&nameLen) + sizeof(nameLen));
    archive.insert(archive.end(), name.begin(), name.end());
    archive.insert(archive.end(), reinterpret_cast<const char*>(&dataLen), reinterpret_cast<const char*>(&dataLen) + sizeof(dataLen));
    archive.insert(archive.end(), fileData.begin(), fileData.end());

    return true;
}

int PackFiles(const std::string& executablePath, const std::vector<std::string>& filesToEmbed, const std::vector<std::string>& resourcesToEmbed, bool onlineData) {
    std::cout << "PackFiles() : packing files...\n";

    std::vector<char> archive;

    const uint64_t totalFiles = filesToEmbed.size() + resourcesToEmbed.size();
    uint16_t fileNumber = 0;

    const auto fileCount = static_cast<uint16_t>(filesToEmbed.size());
    archive.insert(archive.end(), reinterpret_cast<const char*>(&fileCount), reinterpret_cast<const char*>(&fileCount) + sizeof(fileCount));

    for (const auto& path : filesToEmbed) {
        ++fileNumber;
        std::cout << "PackFiles() : packing " << fileNumber << " / " << totalFiles << " file: " << path << "\n";
        if (!PackFile(archive, path, false)) {
            std::cerr << "PackFiles() : failed to pack file: " << path << "\n";
            return -1;
        }
    }

    const auto resourceCount = static_cast<uint16_t>(resourcesToEmbed.size());
    archive.insert(archive.end(), reinterpret_cast<const char*>(&resourceCount), reinterpret_cast<const char*>(&resourceCount) + sizeof(resourceCount));

    for (const auto& path : resourcesToEmbed) {
        ++fileNumber;
        std::cout << "PackFiles() : packing " << fileNumber << " / " << totalFiles << " resource: " << path << "\n";
        if (!PackFile(archive, path, true)) {
            std::cerr << "PackFiles() : failed to pack resource: " << path << "\n";
            return -1;
        }
    }

#if defined(WIN32)
    std::string packedFileName = executablePath.substr(0, executablePath.find_last_of('.')) + "-packed.exe";
#elif defined(__linux__)
    std::string packedFileName = executablePath + "-packed";
#elif defined(__APPLE__)
    std::string packedFileName = executablePath + "-packed";
#else
    std::cerr << "Unsupported platform.\n";
    return -1;
#endif

    if (onlineData) {
        packedFileName = "engine-online-data.dmp";
    }

    std::cout << "PackFiles() : compressing archive...\n";

    const uint64_t decompressedSize = archive.size();
    archive = CompressData(archive);
    const uint64_t archiveSize = archive.size();

    std::cout << "PackFiles() : archive size: " << archiveSize << "\n";
    std::cout << "PackFiles() : decompressed archive size: " << decompressedSize << "\n";
    std::cout << "PackFiles() : compression ratio: " << (static_cast<float>(decompressedSize) / archive.size()) * 100.0f << "%\n";

    archive.insert(archive.end(), MAGIC, MAGIC + MAGIC_SIZE);
    archive.insert(archive.end(), reinterpret_cast<const char*>(&decompressedSize), reinterpret_cast<const char*>(&decompressedSize) + sizeof(decompressedSize));
    archive.insert(archive.end(), reinterpret_cast<const char*>(&archiveSize), reinterpret_cast<const char*>(&archiveSize) + sizeof(archiveSize));

    std::cout << "PackFiles() : creating packed file: " << packedFileName << "\n";

    std::ofstream outFile(packedFileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "PackFiles() : failed to create packed file.\n";
        return -1;
    }

    if (!onlineData) {
        std::cout << "PackFiles() : pack executable: " << executablePath << "\n";

        std::ifstream exeFile(executablePath, std::ios::binary | std::ios::ate);
        if (!exeFile) {
            std::cerr << "PackFiles() : failed to open executable file.\n";
            return -1;
        }

        const std::streamsize size = exeFile.tellg();
        exeFile.seekg(0, std::ios::beg);

        std::vector<char> fileData(size);
        if (!exeFile.read(fileData.data(), size)) {
            std::cerr << "PackFiles() : failed to read executable file.\n";
            return -1;
        }

        outFile.write(fileData.data(), static_cast<std::streamsize>(fileData.size()));
    }

    outFile.write(archive.data(), static_cast<std::streamsize>(archive.size()));

#if defined(__linux__)
    /// add chmod +x for packed file on unix systems
    if (chmod(packedFileName.c_str(), 0755) != 0) {
        std::cerr << "PackFiles() : failed to set executable permissions for packed file.\n";
        return -1;
    }
#endif

    std::cout << "PackFiles() : packed file created successfully.\n";

    return 0;
}