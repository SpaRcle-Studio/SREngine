//
// Created by Kiper220 on 21.11.2020.
//

#if defined (__linux__)
#   include <sys/stat.h>
#endif

#include <FileSystem/FileSystem.h>

using namespace Framework::Helper::FS;

void FileSystem::Init() {
    FileSystem::g_applicationDirectory = PlatformGetApplicationDirectory();
}

std::string FileSystem::PlatformGetApplicationDirectory() {
    return "TODO: Make this method! From PlatformGetApplicationDirectory();";
}

const std::string & FileSystem::GetApplicationDirectory() {
    return FileSystem::g_applicationDirectory;
}

bool FileSystem::FileExists(const std::string& filePath) {
#if defined (__linux__)
    struct stat st;
    return (stat(filePath.c_str(), &st) == 0);
#endif
}

bool FileSystem::DirectoryExists(const std::string& filePath) {
#if defined (__linux__)
    struct stat st;
    return (stat(filePath.c_str(), &st) == 0 && (st.st_mode & S_IFDIR) != 0);
#endif
}
