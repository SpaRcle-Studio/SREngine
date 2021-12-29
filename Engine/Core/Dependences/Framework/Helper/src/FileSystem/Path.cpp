//
// Created by Monika on 10.12.2021.
//

#include <FileSystem/Path.h>
#include <FileSystem/FileSystem.h>

#include <utility>

namespace Framework::Helper {
    Path::Path()
        : Path("")
    { }

    Path::Path(std::string path)
        : m_path(std::move(path))
        , m_name("")
        , m_ext("")
        , m_hash(SIZE_MAX)
    {
        Update();
    }

    Path::Path(const char *path)
        : m_path(path)
        , m_name("")
        , m_ext("")
        , m_hash(SIZE_MAX)
    {
        Update();
    }

    Path Path::Normalize() {
        m_path = FileSystem::NormalizePath(m_path);
        return *this;
    }

    std::string Path::ToString() const {
        return m_path;
    }

    bool Path::IsDir() const {
        struct stat s{};
        if(stat(m_path.c_str(), &s) == 0) {
            if (s.st_mode & S_IFDIR) {
                return true;
            }
        }

        return false;
    }

    bool Path::IsFile() const {
        struct stat s{};
        if(stat(m_path.c_str(), &s) == 0) {
            if (s.st_mode & S_IFREG) {
                return true;
            }
        }

        return false;
    }

    std::vector<Path> Path::GetFiles() const {
        return FileSystem::GetFilesInDir(m_path);
    }

    std::vector<Path> Path::GetFolders() const {
        return FileSystem::GetDirectoriesInDir(m_path);
    }

    Path Path::Concat(const Path& path) {
        m_path += path.m_path;
        Update();
        return m_path;
    }

    bool Path::Valid() const {
        return IsFile() || IsDir();
    }

    const char* Path::CStr() const {
        return m_path.c_str();
    }

    void Path::Update() {
        Normalize();

        if (auto index = m_path.find_last_of("/\\"); index == std::string::npos) {
            m_name = std::string();
            m_ext = std::string();
        } else {
            if (auto dot = m_path.find_last_of('.'); dot != std::string::npos) {
                m_name = m_path.substr(index + 1, dot);
                m_ext  = m_path.substr(dot, m_path.size() - dot);
            } else {
                m_name = m_path.substr(index + 1);
                m_ext  = std::string();
            }
        }

        m_hash = std::hash<std::string>{}(m_path);
    }

    std::string Path::GetExtension() const {
        return m_ext;
    }

    std::string Path::GetBaseName() const {
        return m_name;
    }

    Path::Path(const Path& path) {
        m_path = path.m_path;
        m_name = path.m_name;
        m_ext  = path.m_ext;
        m_hash = path.m_hash;
    }

    size_t Path::GetHash() const {
        return m_hash;
    }

    Path& Path::operator=(const Path& path) = default;
}
