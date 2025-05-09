

# File FileSystem.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**FileSystem**](dir_7528bfd63282bb3e25ecf9b22e573ae4.md) **>** [**FileSystem.h**](FileSystem_8h.md)

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


