//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_FILESYSTEM_H
#define HELPER_FILESYSTEM_H

#include <string>

namespace Framework::Helper {
class FileSystem {
private:
    FileSystem() {};
    ~FileSystem() {};
public:
    static std::string GetDirToExeFromFullPath(std::string full_path);

    static bool Delete(const char *file);

    static bool FileExists(const char *file);

    static std::string GetPathToExe();

    static char* Load(std::string path);

    static const char* FileMapView(std::string path);
    static void UnmapFile(const char* str);
    };
}


#endif //HELPER_FILESYSTEM_H
