

# File HashUtils.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**Tools**](dir_04907cd073aeacf0a44a00b3a87fc81c.md) **>** [**HashUtils.h**](HashUtils_8h.md)

[Go to the documentation of this file](HashUtils_8h.md)


```C++
//
// Created by Nikita on 19.07.2021.
//

#ifndef EVOSCRIPT_HASHUTILS_H
#define EVOSCRIPT_HASHUTILS_H

#include <Scripting/Tools/MD5Hash.h>

#include <Utils/FileSystem/FileSystem.h>

namespace EvoScript::Tools {
    static bool HashEquals(const std::pair<bool, std::vector<std::string>>& a, const std::pair<bool, std::vector<std::string>>& b) {
        const auto& [a_debug, a_hashes] = a;
        const auto& [b_debug, b_hashes] = b;

        if (a_debug != b_debug)
            return false;

        if (a_hashes.size() != b_hashes.size())
            return false;

        for (uint32_t i = 0; i < a_hashes.size(); i++)
            if (a_hashes[i] != b_hashes[i])
                return false;

        return true;
    }

    static std::string GetFileHash(const std::string& file) {
        return MD5().TryDigestFile(const_cast<char*>(file.c_str()));
    }

    static std::vector<std::string> GetHashAllFilesInDir(const std::string& dir) {
        auto result = std::vector<std::string>();

        auto files = SR_UTILS_NS::Path(dir).GetFiles();
        MD5 md5;
        for (const auto& file : files) {
            result.emplace_back(md5.TryDigestFile(const_cast<char *>(file.c_str())));
        }

        return result;
    }

    static bool SaveHashInfo(const std::string& path, const std::pair<bool, std::vector<std::string>>& hashInfo) {
        std::ofstream file(path);
        if (!file.is_open()) {
            SR_ERROR("Tools::SaveHashInfo() : failed to open file! \n\tPath: " + path);
            return false;
        }

        const auto& [debug, hashes] = hashInfo;
        if (debug)
            file << "Debug\n";

        for (const auto& hash : hashes)
            file << hash << "\n";

        file.close();

        return true;
    }

    static std::pair<bool, std::vector<std::string>> LoadHashInfo(const std::string& pathToHashInfo) {
        auto result = std::pair(false, std::vector<std::string>());

        std::ifstream file(pathToHashInfo);
        if (!file.is_open()) {
            SR_ERROR("Tools::LoadHashInfo() : failed to open file! \n\tPath: " + pathToHashInfo);
            return result;
        }

        std::string line;
        while(std::getline(file, line)) {
            if (line.empty())
                continue;

            if (line == "Debug")
                result.first = true;
            else
                result.second.emplace_back(line);
        }

        file.close();

        return result;
    }
}

#endif //EVOSCRIPT_HASHUTILS_H
```


