//
// Created by Nikita on 16.11.2020.
//
#define CRT_SECURE_NO_WARNINGS

#include "../../inc/FileSystem/OldFileSystem.h"

#include <cstdio>
#include <Debug.h>
#include <Utils/StringUtils.h>

#ifdef WIN32
#include <Windows.h>
#endif

#include <Debug.h>

using namespace Framework::Helper;

bool Framework::Helper::OldFileSystem::Delete(const char *file) { return remove(file); }

bool Framework::Helper::OldFileSystem::FileExists(const char *file) {
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

std::string Framework::Helper::OldFileSystem::GetPathToExe() {
#ifdef WIN32
    const std::size_t buf_len = 260;
    LPTSTR s = new TCHAR[buf_len];
    auto path_len = GetModuleFileName(GetModuleHandle(NULL), s, buf_len);
    return GetDirToExeFromFullPath(s);
#else
    Debug::Error("FileSystem::GetPathToExe() : linux not support this function!");
    return "NoDirectory";
#endif
}

std::string Framework::Helper::OldFileSystem::GetDirToExeFromFullPath(std::string full_path) {
    size_t size = full_path.size();

    while (size > 0){
        size--;
        if (full_path[size] == '\\' || full_path[size] == '/')
            break;
    }

    full_path.resize(size);

    return full_path;
}

void OldFileSystem::UnmapFile(const char *str) {

}

const char *OldFileSystem::FileMapView(std::string path) {
    const char *data = nullptr;

#ifdef WIN32

#else

#endif

    return data;
}

char *OldFileSystem::Load(std::string path) {
    //open file
    std::ifstream infile(path);
    if (!infile.is_open()) {
        Debug::Error("OldFileSystem::Load() : failed open file!\n\tPath: "+path);
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
