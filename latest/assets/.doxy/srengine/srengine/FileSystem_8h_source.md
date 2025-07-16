

# File FileSystem.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**FileSystem**](dir_4f99f6be72c0abf8a55fac20395de74b.md) **>** [**FileSystem.h**](FileSystem_8h.md)

[Go to the documentation of this file](FileSystem_8h.md)


```C++
//
// Created by Nikita on 16.11.2020.
//

#ifndef HELPER_FILESYSTEM_H
#define HELPER_FILESYSTEM_H

#include <Utils/FileSystem/Path.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Types/Function.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API FileSystem {
    public:
        FileSystem() = delete;
        ~FileSystem() = delete;
    public:
        static uint64_t GetExecutableAndModulesHash();

        static bool CreatePath(std::string path, uint32_t offset = 0);

        static bool WriteToFile(const std::string& path, const std::string& text);
        static std::string NormalizePath(const std::string& path);

        static std::vector<std::string> ReadAllLines(const SR_UTILS_NS::Path& path);

        static uint64_t ReadHashFromFile(const SR_UTILS_NS::Path& path);
        static bool WriteHashToFile(const SR_UTILS_NS::Path& path, uint64_t hash);

        static std::string ReadBinaryAsString(const Path& path, bool checkError = true);
        static std::vector<char> ReadBinary(std::string_view path);
        static std::vector<uint8_t> ReadFileAsVector(const std::string& path);
        static std::shared_ptr<std::vector<uint8_t>> ReadFileAsBlob(const std::string& path);

        static std::string ReadAllText(const std::string& path);
        static std::vector<std::string_view> ReadAllTextAsStringViewVector(const Path& path, std::string& buffer);

        static char* Load(std::string path);

        static void ForEachFileInFolder(const Path& path, bool recursive, const SR_HTYPES_NS::Function<void(const Path&)>& func);

        static uint64_t GetFileHash(const std::string& path);
        static uint64_t GetFolderHash(const Path& path, uint64_t deep = SR_UINT64_MAX);

        static const char* FileMapView(std::string path);
        static void UnmapFile(const char* str);
    };
}


#endif //HELPER_FILESYSTEM_H
```


