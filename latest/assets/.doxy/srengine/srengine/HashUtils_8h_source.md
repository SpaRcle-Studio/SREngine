

# File HashUtils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Tools**](dir_34b1643912c4d8f0022f3f30c24098db.md) **>** [**HashUtils.h**](HashUtils_8h.md)

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


