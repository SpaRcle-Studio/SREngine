//
// Created by Monika on 10.12.2021.
//

#include <Utils/FileSystem/Path.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Platform/Platform.h>

namespace SR_UTILS_NS {
    Path::Path()
        : m_path()
        , m_name()
        , m_ext()
        , m_hash(SR_UINT64_MAX)
        , m_type(Type::Undefined)
    { }

    Path::Path(std::string_view path, bool fast)
        : Path(path.data(), fast)
    { }

    Path::Path(std::wstring path, bool fast)
        : m_path(SR_WS2S(path))
        , m_name()
        , m_ext()
        , m_hash(SR_UINT64_MAX)
        , m_type(Type::Undefined)
    {
        if (!fast) {
            Update();
        }
    }

    Path::Path(std::string path, bool fast)
        : m_path(std::move(path))
        , m_name()
        , m_ext()
        , m_hash(SR_UINT64_MAX)
        , m_type(Type::Undefined)
    {
        if (!fast) {
            Update();
        }
    }

    Path::Path(const char *path, bool fast)
        : m_path(path)
        , m_name("")
        , m_ext("")
        , m_hash(SR_UINT64_MAX)
        , m_type(Type::Undefined)
    {
        if (!fast) {
            Update();
        }
    }

    Path Path::Normalize() {
        NormalizeSelf();
        return *this;
    }

    std::string Path::ToString() const {
        return m_path;
    }

    std::string_view Path::ToStringView() const {
        return m_path;
    }

    bool Path::IsDir() const {
        return m_type == Type::Folder;
    }

    bool Path::IsFile() const {
        return m_type == Type::File;
    }

    std::list<Path> Path::GetFiles() const {
        return SR_PLATFORM_NS::GetInDirectory(*this, Path::Type::File);
    }

    std::list<Path> Path::GetAll() const {
        return SR_PLATFORM_NS::GetInDirectory(*this, Path::Type::Undefined);
    }

    std::list<Path> Path::GetFolders() const {
        return SR_PLATFORM_NS::GetInDirectory(*this, Path::Type::Folder);
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

        if (auto&& index = m_path.find_last_of("/\\"); index == std::string::npos) {
            if (index = m_path.find_last_of("."); index != std::string::npos) {
                m_name = m_path.substr(0, (m_path.size() - index) - 1);
                m_ext  = m_path.substr(index + 1, m_path.size() - index);
            }
            else {
                m_name = m_path;
                m_ext = std::string();
            }
        }
        else {
            ++index;

            if (auto dot = m_path.find_last_of('.'); dot != std::string::npos && dot > index) {
                m_name = m_path.substr(index, dot - index);
                m_ext  = m_path.substr(dot + 1, m_path.size() - dot);
            }
            else {
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
        return Exists(m_type);
    }

    bool Path::Exists(Type type) const {
        switch (type) {
            case Type::File:
            case Type::Folder:
                return Platform::IsExists(m_path);
            default:
                SRAssert(false);
                SR_FALLTHROUGH;
            case Type::Undefined:
                return false;
        }
    }

    void Path::NormalizeSelf() {
        m_path = FileSystem::NormalizePath(m_path);
        m_type = GetType();
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
                return FileSystem::CreatePath(m_path.substr(0, m_path.size() - (m_name.size() + m_ext.size() + 1)));
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

    Path Path::GetFolder() const {
        switch (GetType()) {
            case Type::File:
                return SR_UTILS_NS::StringUtils::GetDirToFileFromFullPath(m_path);
            default:
                SRHalt0();
                SR_FALLTHROUGH;
            case Type::Folder:
            case Type::Undefined:
                return m_path;
        }
    }

    std::string_view Path::GetExtensionView() const {
        return m_ext;
    }

    std::string_view Path::GetBaseNameView() const {
        return m_name;
    }

    uint64_t Path::GetFileHash() const {
        return FileSystem::GetFileHash(m_path);
    }

    uint64_t Path::GetFolderHash(uint64_t deep) const {
        return FileSystem::GetFolderHash(m_path, deep);
    }

    bool Path::IsAbs() const {
        return Platform::IsAbsolutePath(m_path);
    }

    bool Path::IsSubPath(const Path &subPath) const {
        return m_path.find(subPath.m_path) != std::string::npos;
    }

    Path Path::RemoveSubPath(const Path &subPath) const {
        auto&& index = m_path.find(subPath.m_path);

        if (index == std::string::npos) {
            return *this;
        }

        if (m_path.size() == subPath.m_path.size()) {
            return Path();
        }

        return StringUtils::Remove(m_path, index, subPath.m_path.size() + 1);
    }

    Path Path::SelfRemoveSubPath(const Path &subPath) {
        auto&& index = m_path.find(subPath.m_path);

        if (index == std::string::npos) {
            return std::move(*this);
        }

        if (m_path.size() == subPath.m_path.size()) {
            return Path();
        }

        return StringUtils::Remove(m_path, index, subPath.m_path.size() + 1);
    }

    bool Path::IsHidden() const {
        return Platform::FileIsHidden(m_path);
    }

    std::wstring Path::ToUnicodeString() const {
        return SR_S2WS(m_path);
    }

    std::wstring Path::ToWinApiPath() const {
        auto&& wstring = ToUnicodeString();
        return SR_UTILS_NS::StringUtils::ReplaceAll<std::wstring>(wstring, L"/", L"\\");
    }

    bool Path::IsEmpty() const {
        /// TODO: optimize
        return GetAll().empty();
    }

    bool Path::Copy(const Path &destination) const {
        return Platform::Copy(*this, destination);
    }

    std::string Path::GetBaseNameAndExt() const {
        return m_name + "." + m_ext;
    }

    std::string_view Path::View() const {
        return m_path;
    }

    std::string Path::GetWithoutExtension() const {
        if (m_ext.empty()) {
            return m_path;
        }

        std::string path = m_path;
        path.resize(path.size() - (m_ext.size() + 1));
        return path;
    }
}
