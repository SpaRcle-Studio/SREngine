//
// Created by Monika on 10.12.2021.
//

#ifndef SRENGINE_PATH_H
#define SRENGINE_PATH_H

#include <Utils/stdInclude.h>
#include <Utils/Math/Mathematics.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Common/Breakpoint.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT Path {
    public:
        enum class Type {
            Undefined, File, Folder
        };

    public:
        Path();
        Path(const Path& path);
        Path(const char* path, bool fast = false);
        Path(SR_UTILS_NS::StringAtom stringAtom, bool fast = false);
        Path(std::string path, bool fast = false);
        Path(std::string_view path, bool fast = false);
        Path(std::wstring path, bool fast = false);

        Path(Path&& path) noexcept
            : m_path(SR_UTILS_NS::Exchange(path.m_path, {}))
            , m_name(std::exchange(path.m_name, {}))
            , m_ext(std::exchange(path.m_ext, {}))
            , m_hash(std::exchange(path.m_hash, {}))
            , m_type(std::exchange(path.m_type, {}))
        { }

        Path& operator=(Path&& path) noexcept {
            m_path = std::exchange(path.m_path, {});
            m_name = std::exchange(path.m_name, {});
            m_ext = std::exchange(path.m_ext, {});
            m_hash = std::exchange(path.m_hash, {});
            m_type = std::exchange(path.m_type, {});
            return *this;
        }

        operator const std::string&() { return m_path; } /** NOLINT */
        Path& operator=(const Path& path) = default;

        bool operator==(const Path& path) const noexcept {
            return m_path == path.ToStringRef();
        }

        char operator[](size_t index) const noexcept {
            if (index >= m_path.size()) {
                 std::cerr << "Path::operator[] : index is out of range!\n";
                 SR_MAKE_BREAKPOINT;
                 return char();
            }
            return m_path[index];
        }

        char& operator[](size_t index) noexcept {
            if (index >= m_path.size()) {
                std::cerr << "Path::operator[] : index is out of range!\n";
                SR_MAKE_BREAKPOINT;
                static char def = char();
                return def;
            }
            return m_path[index];
        }

    public:
        SR_DEPRECATED bool Make(Type type = Type::Undefined) const;
        bool Create() const;

        SR_NODISCARD bool Copy(const Path& destination) const;

        SR_NODISCARD std::string ToString() const;
        SR_NODISCARD const std::string& ToStringRef() const;
        SR_NODISCARD std::string* ToStringPtr() { return &m_path; }
        SR_NODISCARD std::string_view ToStringView() const;
        SR_NODISCARD std::wstring ToWinApiPath() const;
        SR_NODISCARD std::wstring ToUnicodeString() const;
        SR_NODISCARD size_t GetHash() const;
        SR_NODISCARD uint64_t GetFileHash() const;
        SR_NODISCARD uint64_t GetFolderHash(uint64_t deep = SR_UINT64_MAX) const;
        SR_NODISCARD const char* CStr() const;
        SR_NODISCARD const char* c_str() const { return CStr(); }

        SR_NODISCARD Path GetPrevious() const;
        SR_NODISCARD Path GetFolder() const;
        SR_NODISCARD Path Concat(const Path& path) const;
        SR_NODISCARD Path EmplaceFront(const std::string& str) const;
        SR_NODISCARD Path ConcatExt(const std::string& ext) const;
        SR_NODISCARD Path RemoveSubPath(const Path& subPath) const;
        SR_NODISCARD Path SelfRemoveSubPath(const Path& subPath) const;

        SR_NODISCARD bool Valid() const;
        SR_NODISCARD bool Empty() const;
        SR_NODISCARD bool empty() const { return Empty(); }
        SR_NODISCARD bool IsSubPath(const Path& subPath) const;
        SR_NODISCARD bool Contains(const std::string& str) const;
        SR_NODISCARD bool IsHidden() const;
        SR_NODISCARD bool Exists() const;
        SR_NODISCARD bool Exists(Type type) const;

        SR_NODISCARD Type GetType() const;
        SR_NODISCARD bool IsDir() const;
        SR_NODISCARD bool IsFile() const;
        SR_NODISCARD bool IsAbs() const;
        SR_NODISCARD bool IsEmpty() const;

        SR_NODISCARD std::list<Path> GetFiles() const;
        SR_NODISCARD std::list<Path> GetFolders() const;
        SR_NODISCARD std::list<Path> GetAll() const;

        SR_NODISCARD std::string GetWithoutExtension() const;
        SR_NODISCARD std::string_view GetExtensionView() const;
        SR_NODISCARD std::string_view GetBaseNameView() const;
        SR_NODISCARD std::string_view View() const;
        SR_NODISCARD std::string GetExtension() const;
        SR_NODISCARD std::string GetBaseName() const;
        SR_NODISCARD std::string GetBaseNameAndExt() const;

    private:
        void Update();

        Path Normalize();
        void NormalizeSelf();

    private:
        std::string m_path;
        std::string m_name;
        std::string m_ext;
        uint64_t    m_hash;
        Type        m_type;

    };
}

#endif //SRENGINE_PATH_H
