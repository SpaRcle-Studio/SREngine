//
// Created by Monika on 26.07.2021.
//

#ifndef FBXLOADER_UTILS_H
#define FBXLOADER_UTILS_H

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <string>
#include <vector>
#include <fstream>

#ifdef __MINGW64__
    #include <dirent.h>
#else
    #include <direct.h>
#endif

#include <sys/stat.h>
#include <sstream>
#include <FbxLoader/MD5Hash.h>

namespace FbxLoader::Tools {
    class NonCopyable {
    protected:
        constexpr NonCopyable() = default;
        virtual ~NonCopyable() = default;

        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

    template<typename T> static void SaveValue(std::ofstream& file, const T& value) {
        file.write((const char*)&value, sizeof(T));
    }

    template<typename T> static T LoadValue(std::ifstream& file) {
        T value;
        file.read((char*)&value, sizeof(T));
        return value;
    }

    static void SaveString(std::ofstream& file, const std::string& str) {
        const int32_t size = str.size();
        file.write((const char*)&size, sizeof(int32_t));
        file.write((const char*)&str[0], size * sizeof(char));
    }

    template<typename T, typename U> void SavePair(std::ofstream& file, const std::pair<T, U>& pair) {
        SaveValue(file, pair.first);
        SaveValue(file, pair.second);
    }

    template<typename T, typename U> std::pair<T, U> LoadPair(std::ifstream& file) {
        std::pair<T, U> pair;
        pair.first = LoadValue<T>(file);
        pair.second = LoadValue<U>(file);
        return pair;
    }

    static std::string LoadStr(std::ifstream& file) {
        std::string str;
        int size;
        file.read((char*)&size, sizeof(int32_t));
        str.resize(size);
        file.read((char*)&str[0], size * sizeof(char));
        return str;
    }

    template<typename T> static void SaveComplexVector(std::ofstream& file, const std::vector<T>& vec) {
        SaveValue(file, static_cast<uint32_t>(vec.size()));
        for (const auto& value : vec)
            value.Save(file);
    }

    template<typename T> static std::vector<T> LoadComplexVector(std::ifstream& file) {
        const auto size = LoadValue<uint32_t>(file);
        std::vector<T> result;
        result.resize(size);
        for (uint32_t i = 0; i < size; ++i)
            result[i].Load(file);
        return result;
    }

    template<typename T, typename U> static std::vector<std::pair<T, U>> LoadVectorOfPairs(std::ifstream& file) {
        const auto size = LoadValue<uint32_t>(file);
        std::vector<std::pair<T, U>> result;
        result.resize(size);
        for (uint32_t i = 0; i < size; ++i)
            result[i] = LoadPair<T, U>(file);
        return result;
    }

    template<typename T> static void SaveVector(std::ofstream& file, const std::vector<T>& vec) {
        SaveValue(file, static_cast<uint32_t>(vec.size()));

        if (vec.size() > 0)
            file.write((const char*)&vec[0], vec.size() * sizeof(T));
    }

    template<typename T, typename U> static void SaveVectorOfPairs(std::ofstream& file, const std::vector<std::pair<T, U>>& vec) {
        SaveValue(file, static_cast<uint32_t>(vec.size()));
        for (const auto& value : vec)
            SavePair<T, U>(file, value);
    }

    template<typename T> static std::vector<T> LoadVector(std::ifstream& file) {
        std::vector<T> result;

        auto size = LoadValue<uint32_t>(file);
        result.resize(size);

        if (size > 0)
            file.read((char*)&result[0], size * sizeof(T));

        return result;
    }

    static std::string GetHash(const std::string& path) {
        MD5 md5;
        return md5.digestFile(const_cast<char*>(path.c_str()));
    }

    static std::string LoadHash(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open())
            return std::string();

        std::stringstream buffer;
        buffer << file.rdbuf();

        file.close();
        return buffer.str();
    }

    static bool SaveHash(const std::string& path, const std::string& hash) {
        std::ofstream file(path);
        if (!file.is_open())
            return false;

        file << hash;

        file.close();
        return true;
    }

    static std::string Replace(std::string str, const std::string& from, const std::string& to) {
        ret:
        size_t start_pos = str.find(from);
        if(start_pos == std::string::npos)
            return str;
        str.replace(start_pos, from.length(), to);
        goto ret;
    }

    static std::string FixPath(const std::string& path) {
        return Tools::Replace(Tools::Replace(path, "\\", "/"), "//", "/");
    }

    static bool Contains(const std::string& str, const std::string& sub) {
        return str.find(sub) != std::string::npos;
    }

    inline static int32_t Find(const std::string& str, const char& c) {
        if (auto id = str.find(c); id == std::string::npos)
            return -1;
        else
            return id;
    }

    static std::string ReadTo(const std::string& str, char c, int32_t offset = 0, bool* found = nullptr) {
        auto id = str.find(c);
        if (id == std::string::npos) {
            if (found)
                *found = false;
            return str;
        }
        else {
            if (found)
                *found = true;
            return str.substr(0, id + offset);
        }
    }

    static std::string BackReadTo(const std::string& str, char c, int32_t offset = 0) {
        auto id = str.rfind(c);
        if (id == std::string::npos)
            return "";
        else
            return str.substr(id + offset, str.size() - 1);
    }

    static bool FileExists(const std::string& file) {
        struct stat buffer{};
        return (stat (file.c_str(), &buffer) == 0);
    }

    static bool CreateFolder(const std::string& directory) {
#ifdef __MINGW64__
        return mkdir(directory.c_str());
#else
        return _mkdir(directory.c_str());
#endif
    }

    inline static std::string Read(const std::string& str, uint32_t count) {
        return str.substr(0, count);
    }

    //! path must be a fix
    static void CreatePath(const std::string& path, uint32_t offset = 0) {
        auto pos = path.find('/', offset);
        if (pos != std::string::npos) {
            auto dir = Tools::Read(path, pos);
            Tools::CreateFolder(dir);
            CreatePath(path, pos + 1);
        }
    }

    static std::string ReadToLast(const std::string& str, char c, int32_t offset = 0) {
        uint64_t id = str.rfind(c);
        if (id == std::string::npos)
            return str;
        else
            return str.substr(0, id + offset);
    }

    static std::string GetBetween(const std::string& str, char c) {
        if (str.size() <= 2)
            return std::string();
        else {
            int32_t begin = str.find(c);
            int32_t end = str.rfind(c);

            if (begin == std::string::npos || end == std::string::npos || ((end - begin) <= 2))
                return std::string();
            else
                return str.substr(begin + 1, (end - begin) - 1);
        }
    }

    static std::string RemoveAll(std::string str, char c) {
        ret:
        size_t start_pos = str.find(c);
        if(start_pos == std::string::npos)
            return str;
        str.erase(str.begin() + start_pos);
        goto ret;
    }

    static std::string ReadAllText(const std::string& file) {
        std::string text;

        std::ifstream stream(file);
        if (!stream.is_open())
            return {};

        std::string line;
        while (std::getline(stream, line)) {
            line = Tools::RemoveAll(line, '\t');
            line = Tools::Replace(line, "  ", " ");
            line = Tools::Replace(line, ", ", ",");
            line = Tools::Replace(line, "} ", "}");

            if (!line.empty() && line[0] != ';')
                text.append(std::string(" ").append(line));
        }

        return text;
    }

    static inline float_t CastToFloat(const std::string& str) {
        return std::stof(str);
    }

    static inline std::vector<float_t> SplitAndCastToFloat(const std::string& str, char splitter) {
        auto result = std::vector<float_t>();
        std::istringstream ss(str);
        std::string value;
        while (getline(ss, value, splitter))
            result.emplace_back(std::stof(value));
        return result;
    }

    static inline std::vector<uint32_t> SplitAndCastToUInt32(const std::string& str, char splitter) {
        auto result = std::vector<uint32_t>();
        std::istringstream ss(str);
        std::string value;
        while (getline(ss, value, splitter))
            result.emplace_back((uint32_t)std::stoi(value));
        return result;
    }

    static inline std::vector<int32_t> SplitAndCastToInt32(const std::string& str, char splitter) {
        auto result = std::vector<int32_t>();
        std::istringstream ss(str);
        std::string value;
        while (getline(ss, value, splitter))
            result.emplace_back(std::stoi(value));
        return result;
    }

    static inline std::vector<std::string> Split(const std::string& str, char splitter) {
        auto result = std::vector<std::string>();
        std::istringstream ss(str);
        std::string value;
        while (getline(ss, value, splitter))
            result.emplace_back(value);
        return result;
    }

    static std::vector<std::string> ReadAllLines(const std::string& file) {
        auto lines = std::vector<std::string>();

        std::ifstream stream(file);
        if (!stream.is_open())
            return {};

        std::string line;
        while (std::getline(stream, line)) {
            lines.emplace_back(line);
        }

        return lines;
    }
}

#endif //FBXLOADER_UTILS_H

