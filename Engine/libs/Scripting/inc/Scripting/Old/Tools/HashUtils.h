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
