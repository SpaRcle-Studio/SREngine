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
        , m_type(Type::Undefined)
    {
        Update();
    }

    Path::Path(const char *path)
        : m_path(path)
        , m_name("")
        , m_ext("")
        , m_hash(SIZE_MAX)
        , m_type(Type::Undefined)
    {
        Update();
    }

    Path Path::Normalize() {
        NormalizeSelf();
        return *this;
    }

    std::string Path::ToString() const {
        return m_path;
    }

    bool Path::IsDir() const {
        return m_type == Type::Folder;
    }

    bool Path::IsFile() const {
        return m_type == Type::File;
    }

    std::vector<Path> Path::GetFiles() const {
        return FileSystem::GetFilesInDir(m_path);
    }

    std::vector<Path> Path::GetAll() const {
        return FileSystem::GetAllInDir(m_path);
    }

    std::vector<Path> Path::GetFolders() const {
        return FileSystem::GetDirectoriesInDir(m_path);
    }

    bool Path::Valid() const {
        return m_type != Type::Undefined;
    }

    const char* Path::CStr() const {
        return m_path.c_str();
    }

    void Path::Update() {
        NormalizeSelf();

        m_type = GetType();

        if (auto index = m_path.find_last_of("/\\"); index == std::string::npos) {
            m_name = std::string();
            m_ext = std::string();
        } else {
            ++index;

            if (auto dot = m_path.find_last_of('.'); dot != std::string::npos && m_type == Type::File) {
                m_name = m_path.substr(index, dot - index);
                m_ext  = m_path.substr(dot + 1, m_path.size() - dot);
            } else {
                m_name = m_path.substr(index);
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
        m_type = path.m_type;
    }

    size_t Path::GetHash() const {
        return m_hash;
    }

    Path::Type Path::GetType() const {
#if defined(SR_MSVC)
        struct stat s{};
        if(stat(m_path.c_str(), &s) == 0) {
            if (s.st_mode & S_IFDIR) {
                return Type::Folder;
            } else if (s.st_mode & S_IFREG) {
                return Type::File;
            }
        }

        return Type::Undefined;
#elif defined(SR_WIN32)
        DWORD attrib = GetFileAttributes(m_path.c_str());

        if ((attrib & FILE_ATTRIBUTE_DIRECTORY) != 0)
            return Type::Folder;

        return Type::File;
#else
        return Type::Undefined;
#endif
    }

    Path Path::Concat(const Path &path) const {
        if ((!m_path.empty() && m_path.back() != '/') && (!path.Empty() && path.m_path.front() != '/'))
            return m_path + "/" + path.m_path;

        return m_path + path.m_path;
    }

    bool Path::Exists() const {
        switch (m_type) {
            case Type::File:
                return Helper::FileSystem::FileExists(m_path);
            case Type::Folder:
                return Helper::FileSystem::FolderExists(m_path);
            default:
                SRAssert(false);
            case Type::Undefined:
                return false;
        }
    }

    void Path::NormalizeSelf() {
        m_path = FileSystem::NormalizePath(m_path);
    }

    bool Path::Empty() const {
        return m_path.empty();
    }

    Path Path::ConcatExt(const std::string& ext) const {
        if (ext.empty())
            return *this;

        if (ext[0] == '.')
            return m_path + ext;

        return m_path + "." + ext;
    }

    bool Path::Make(Type type) const {
        if (m_path.empty())
            return false;

        switch (type) {
            default:
                SRAssert(false);
                SR_FALLTHROUGH;
            case Type::Undefined:
            case Type::File:
                return FileSystem::CreatePath(m_path.substr(0, m_path.size() - (m_name.size() + m_ext.size())));
            case Type::Folder:
                return FileSystem::CreatePath(m_path);
        }
    }

    Path Path::GetPrevious() const {
        if (m_path.empty())
            return m_path;

        if (const auto&& pos = m_path.rfind('/'); pos != std::string::npos) {
            if (pos <= 1)
                return m_path;

            return m_path.substr(0, pos);
        }

        return m_path;
    }

    std::string_view Path::GetExtensionView() const {
        return m_ext;
    }

    std::string_view Path::GetBaseNameView() const {
        return m_name;
    }

    Path& Path::operator=(const Path& path) = default;
}
