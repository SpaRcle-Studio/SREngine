//
// Created by Monika on 13.05.2025.
//

enum UNPACK_RESULT {
    UNPACK_SUCCESS,
    UNPACK_NO_PACKED_DATA,
    UNPACK_FILE_NOT_FOUND,
    UNPACK_FILE_TOO_SMALL,
    UNPACK_INVALID_DATA_SIZE,
    UNPACK_FAILED_TO_CREATE_FILE,
    UNPACK_UNKNOWN_FILE_TYPE,
    UNPACK_FAILED_TO_READ_DATA,
};

std::vector<char> DecompressData(uint64_t decompressedSize, const std::vector<char>& data) {
    if (data.empty()) {
        return {};
    }

    std::vector<char> decompressedData(decompressedSize);

    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int ret = inflateInit(&strm);
    if (ret != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib for decompression!");
    }

    strm.avail_in = data.size();
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(data.data()));
    strm.avail_out = decompressedSize;
    strm.next_out = reinterpret_cast<Bytef*>(decompressedData.data());

    ret = inflate(&strm, Z_FINISH);
    if (ret != Z_STREAM_END) {
        inflateEnd(&strm);
        throw std::runtime_error("Failed to decompress data!");
    }

    decompressedSize = strm.total_out;
    inflateEnd(&strm);
    decompressedData.resize(decompressedSize);
    return decompressedData;
}

int ParseData(const std::vector<char>& data, const std::string& executablePath) {
    std::istringstream stream(std::string(data.begin(), data.end()));
    uint16_t fileCount = 0;
    stream.read(reinterpret_cast<char*>(&fileCount), sizeof(fileCount));

    std::cout << "ParseData() : unpacking " << fileCount << " files...\n";

    for (uint32_t i = 0; i < fileCount; ++i) {
        uint16_t nameLen = 0;
        stream.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        std::string filename(nameLen, '\0');
        stream.read(filename.data(), nameLen);

        std::cout << "ParseData() : unpacking file: " << filename << "\n";

        uint64_t contentLen = 0;
        stream.read(reinterpret_cast<char*>(&contentLen), sizeof(contentLen));
        std::vector<char> fileData(contentLen);
        stream.read(fileData.data(), static_cast<std::streamsize>(contentLen));

        std::filesystem::path path(filename);
        std::string ext = path.extension().string();

        std::filesystem::path outputDir = std::filesystem::path(executablePath).parent_path();
        if (ext == ".dll" || ext == ".so" || ext == ".dylib" || ext == ".exe" || ext == ".x86_64" || ext.empty()) {
            outputDir /= SR_APPLICATION_NAME + "/Engine/Bin";
        }
        else if (ext == ".lib") {
            outputDir /= SR_APPLICATION_NAME + "/Engine/Lib";
        }
        else {
            std::cerr << "ParseData() : unknown file type: " << ext << "\n";
            return UNPACK_UNKNOWN_FILE_TYPE;
        }

        std::filesystem::create_directories(outputDir);
        std::filesystem::path outputPath = outputDir / path.filename();

        std::ofstream outFile(outputPath, std::ios::binary);
        if (!outFile) {
            std::cerr << "ParseData() : failed to open output file: " << outputPath << "\n";
            return UNPACK_FAILED_TO_CREATE_FILE;
        }
        outFile.write(fileData.data(), static_cast<std::streamsize>(fileData.size()));
        std::cout << "ParseData() : unpacked file: " << outputPath << "\n";
    }


    uint16_t resourceCount = 0;
    stream.read(reinterpret_cast<char*>(&resourceCount), sizeof(resourceCount));

    std::cout << "ParseData() : unpacking " << resourceCount << " resources...\n";

    for (uint32_t i = 0; i < resourceCount; ++i) {
        uint16_t nameLen = 0;
        stream.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        std::string filename(nameLen, '\0');
        stream.read(filename.data(), nameLen);

        std::cout << "ParseData() : unpacking resource: " << filename << "\n";

        uint64_t contentLen = 0;
        stream.read(reinterpret_cast<char*>(&contentLen), sizeof(contentLen));
        std::vector<char> fileData(contentLen);
        stream.read(fileData.data(), static_cast<std::streamsize>(contentLen));

        std::filesystem::path path(filename);

        std::filesystem::path outputDir = std::filesystem::path(executablePath).parent_path() / SR_APPLICATION_NAME / "Resources";
        std::filesystem::path outputPath = absolute(outputDir / path);
        std::filesystem::create_directories(outputPath.parent_path());

        std::ofstream outFile(outputPath, std::ios::binary);
        if (!outFile) {
            std::cerr << "ParseData() : failed to open output file: " << outputPath << "\n";
            return UNPACK_FAILED_TO_CREATE_FILE;
        }
        outFile.write(fileData.data(), static_cast<std::streamsize>(fileData.size()));
    }

    std::cout << "ParseData() : unpacking completed!\n";

    return UNPACK_SUCCESS;
}

int TryUnpackFiles(const std::string& executablePath, std::ifstream& fileStream) {
    const uint64_t fileSize = fileStream.tellg();
    if (fileSize < MAGIC_SIZE + sizeof(uint64_t) + sizeof(uint64_t)) {
        std::cerr << "TryUnpackFiles() : file is too small to contain packed data!\n";
        return UNPACK_FILE_TOO_SMALL;
    }

    fileStream.seekg(static_cast<std::streamsize>(fileSize - MAGIC_SIZE - sizeof(uint64_t) - sizeof(uint64_t)), std::ios::beg);

    char magicBuf[MAGIC_SIZE];
    fileStream.read(magicBuf, MAGIC_SIZE);
    if (std::string(magicBuf, MAGIC_SIZE) != MAGIC) {
        return UNPACK_NO_PACKED_DATA;
    }

    uint64_t decompressedSize = 0;
    fileStream.read(reinterpret_cast<char*>(&decompressedSize), sizeof(decompressedSize));
    std::cout << "TryUnpackFiles() : decompressed size: " << decompressedSize << "\n";

    uint64_t dataSize = 0;
    fileStream.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
    if (dataSize == 0 || fileSize < static_cast<std::streamoff>(dataSize + MAGIC_SIZE + sizeof(uint64_t) + sizeof(uint64_t))) {
        std::cerr << "TryUnpackFiles() : invalid data size!\n";
        return UNPACK_INVALID_DATA_SIZE;
    }

    std::cout << "TryUnpackFiles() : packed data size: " << dataSize << "\n";

    fileStream.seekg(static_cast<std::streamsize>(fileSize - dataSize - MAGIC_SIZE - sizeof(uint64_t) - sizeof(uint64_t)), std::ios::beg);

    std::vector<char> data(dataSize);
    fileStream.read(data.data(), static_cast<std::streamsize>(dataSize));
    if (fileStream.gcount() != static_cast<std::streamsize>(dataSize)) {
        std::cerr << "TryUnpackFiles() : failed to read packed data!\n";
        return UNPACK_FAILED_TO_READ_DATA;
    }

    std::cout << "TryUnpackFiles() : decompressing data...\n";
    data = DecompressData(decompressedSize, data);

    return ParseData(data, executablePath);
}

int TryUnpackFiles(const std::string& executablePath) {
    std::ifstream exeFile(executablePath, std::ios::binary | std::ios::ate);
    if (!exeFile) {
        std::cerr << "TryUnpackFiles() : failed to open file: " << executablePath << "\n";
        return UNPACK_FILE_NOT_FOUND;
    }
    return TryUnpackFiles(executablePath, exeFile);
}

void DeletePackedFile(const std::string& executablePath) {
    namespace fs = std::filesystem;

    if (!fs::exists(executablePath) || !fs::is_regular_file(executablePath)) {
        std::cerr << "DeletePackedFile() : file does not exist or is not a regular file: " << executablePath << '\n';
        return;
    }

    std::cout << "DeletePackedFile() : deleting packed file: " << executablePath << '\n';

    /// protection against “infinite loop” optimization
    const std::atomic<bool> whileLoop = true;
    while (whileLoop) {
        std::error_code ec;
        if (fs::remove(executablePath, ec)) {
            std::cout << "DeletePackedFile() : file deleted successfully: " << executablePath << '\n';
            break;
        }
    }
}

