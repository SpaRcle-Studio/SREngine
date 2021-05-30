//
// Created by Nikita on 16.11.2020.
//
#define CRT_SECURE_NO_WARNINGS

#include "../../inc/FileSystem/FileSystem.h"

#include <cstdio>
#include <filesystem>
#include <Debug.h>
#include <Utils/StringUtils.h>

#ifdef WIN32
#include <Windows.h>
#endif

#include <Utils/StringUtils.h>
#include <Debug.h>

using namespace Framework::Helper;

bool Framework::Helper::FileSystem::Delete(const char *file) { return remove(file); }

bool Framework::Helper::FileSystem::FileExists(const char *file) {
#ifdef WIN32
    if (FILE* f = fopen(file, "r")) {
        fclose(f);
        return true;
    }
    else
        return false;
#else
    Debug::Error("FileSystem::FileExists() : linux not support this function!");
    return false;
#endif
}

std::string Framework::Helper::FileSystem::GetPathToExe() {
#ifdef WIN32
    const std::size_t buf_len = 260;
    auto s = new TCHAR[buf_len];
    auto path_len = GetModuleFileName(GetModuleHandle(nullptr), s, buf_len);
    return StringUtils::GetDirToFileFromFullPath(s);
#else
    Debug::Error("FileSystem::GetPathToExe() : linux not support this function!");
    return "NoDirectory";
#endif
}

std::string Framework::Helper::FileSystem::GetFullPathToExe() {
#ifdef WIN32
    const std::size_t buf_len = 260;
    auto s = new TCHAR[buf_len];
    auto path_len = GetModuleFileName(GetModuleHandle(nullptr), s, buf_len);
    return s;
#else
    Debug::Error("FileSystem::GetPathToExe() : linux not support this function!");
    return "NoDirectory";
#endif
}

void FileSystem::UnmapFile(const char *str) {

}

const char *FileSystem::FileMapView(std::string path) {
    const char *data = nullptr;

#ifdef WIN32

#else

#endif

    return data;
}

char *FileSystem::Load(std::string path) {
    //open file
    std::ifstream infile(path);
    if (!infile.is_open()) {
        Debug::Error("FileSystem::Load() : failed open file!\n\tPath: "+path);
        return nullptr;
    }


    //get length of file
    infile.seekg(0, std::ios::end);
    size_t length = infile.tellg();
    infile.seekg(0, std::ios::beg);

    char* buffer = new char[length];

    //read file
    infile.read(buffer, length);

    return buffer;
}

std::string FileSystem::GetExecutableFileName() {
#ifdef WIN32
    const std::size_t buf_len = 260;
    auto s = new TCHAR[buf_len];
    auto path_len = GetModuleFileName(GetModuleHandle(nullptr), s, buf_len);
    return StringUtils::GetFileNameFromFullPath(s);
#else
    return "Unsupported function";
#endif
}

void FileSystem::Reload() {
    std::string exe = GetFullPathToExe();
    ShellExecute(NULL, "open", exe.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}

std::string FileSystem::ReadAllText(const std::string &path) {
    std::string data = std::string();
    std::ifstream stream(path, std::ios::in);
    if (stream.is_open()) {
        std::string line;
        while (getline(stream, line))
            data += "\n" + line;
        stream.close();
    }
    return data;
}

std::vector<char> FileSystem::ReadBinary(const std::string &path) {
    /*std::ifstream ifd(path,  std::ios::binary |  std::ios::ate);
    int size = ifd.tellg();
    ifd.seekg(0,  std::ios::beg);
    std::vector<char> buffer;
    buffer.resize(size); // << resize not reserve
    ifd.read(buffer.data(), size);*/

    //std::ifstream input(path, std::ios::binary);
    //std::vector<uint32_t> buffer(std::istreambuf_iterator<char>(input), {});

    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        Helper::Debug::Error("FileSystem::ReadBinary() : failed to open \""+path+"\"file!");
        return std::vector<char>();
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

bool FileSystem::CreatePath(const std::string &path) {
    return std::filesystem::create_directories(path.c_str());
}

