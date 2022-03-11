//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_FILESYSTEM_H
#define HELPER_FILESYSTEM_H

#include <string>
#include <vector>
#include <fstream>
#include <FileSystem/Path.h>

namespace Framework::Helper {
class FileSystem {
public:
    FileSystem() = delete;
    ~FileSystem() = delete;
public:
    static bool Delete(const char *file);

    static bool FileExists(const std::string& path);

    static std::string SaveFileDialog(const std::string& path, const std::string& filter);

    static bool CreatePath(std::string path, uint32_t offset = 0) {
        if (path.empty())
            return false;

        if (path.back() != '/')
            path.append("/");

        auto pos = path.find('/', offset);
        if (pos != std::string::npos) {
            auto dir = path.substr(0, pos);

            CreateFolder(dir);
            CreatePath(path, pos + 1);
        }

        return true;
    }

    static bool CreateFolder(const std::string& path);
    static std::string GetExecutableFileName();
    static std::string GetPathToExe();
    static std::string GetFullPath(const std::string& path);
    static std::string NormalizePath(const std::string& path);
    static std::string GetFullPathToExe();
    static void Reload();

    static std::vector<std::string> ReadAllLines(const std::string& path) {
        std::ifstream file(path);
        std::vector<std::string> lines = { };
        while (true){
            std::string line;
            std::getline(file,line);
            if (!file.good())
                break;
            lines.push_back(line);
        }
        return lines;
    }

    static std::vector<char> ReadBinary(const std::string& path);

    static std::string ReadAllText(const std::string& path);

    static char* Load(std::string path);

    static const char* FileMapView(std::string path);
    static void UnmapFile(const char* str);

    static std::vector<Path> GetFilesInDir(const std::string& path);
    static std::vector<Path> GetDirectoriesInDir(const std::string& path);
    static std::vector<Path> GetAllInDir(const std::string& path);

    static bool FolderExists(const std::string &path);
};
}


#endif //HELPER_FILESYSTEM_H
