//
// Created by Monika on 10.12.2021.
//

#ifndef SRENGINE_PATH_H
#define SRENGINE_PATH_H

#include <string>
#include <atomic>
#include <vector>
#include <functional>

namespace Framework::Helper {
    class Path {
    public:
        Path();
        Path(const Path& path);
        Path(const char* path);
        Path(std::string  path);

        operator const std::string&() { return m_path; }
        Path& operator=(const Path& path);

    public:
        Path Normalize();
        [[nodiscard]] std::string ToString() const;
        [[nodiscard]] size_t GetHash() const;
        [[nodiscard]] const char* CStr() const;

        Path Concat(const Path& path);

        [[nodiscard]] bool Valid() const;

        [[nodiscard]] bool IsDir() const;
        [[nodiscard]] bool IsFile() const;

        [[nodiscard]] std::vector<Path> GetFiles() const;
        [[nodiscard]] std::vector<Path> GetFolders() const;

        [[nodiscard]] std::string GetExtension() const;
        [[nodiscard]] std::string GetBaseName() const;

    private:
        void Update();

    private:
        std::string m_path;
        std::string m_name;
        std::string m_ext;
        size_t      m_hash;

    };
}

#endif //SRENGINE_PATH_H
