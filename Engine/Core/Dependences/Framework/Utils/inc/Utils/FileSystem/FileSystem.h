//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_FILESYSTEM_H
#define HELPER_FILESYSTEM_H

#include <Utils/FileSystem/Path.h>
#include <Utils/Common/StringUtils.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT FileSystem {
    public:
        FileSystem() = delete;
        ~FileSystem() = delete;
    public:
        static bool CreatePath(std::string path, uint32_t offset = 0);

        static bool WriteToFile(const std::string& path, const std::string& text);
        static std::string NormalizePath(const std::string& path);

        static std::vector<std::string> ReadAllLines(const std::string& path) {
            std::ifstream file(path);
            std::vector<std::string> lines = { };
            while (file.good()) {
                std::string line;
                std::getline(file,line);
                lines.push_back(line);
            }
            return lines;
        }

        static std::string ReadBinaryAsString(const std::string& path, bool checkError = true);
        static std::vector<char> ReadBinary(const std::string& path);
        static std::vector<uint8_t> ReadFileAsVector(const std::string& path);
        static std::shared_ptr<std::vector<uint8_t>> ReadFileAsBlob(const std::string& path);

        static std::string ReadAllText(const std::string& path);

        static char* Load(std::string path);

        static uint64_t GetFileHash(const std::string& path);
        static uint64_t GetFolderHash(const Path& path, uint64_t deep = SR_UINT64_MAX);

        static const char* FileMapView(std::string path);
        static void UnmapFile(const char* str);
    };
}


#endif //HELPER_FILESYSTEM_H
