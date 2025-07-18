

# File Path.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**FileSystem**](dir_4f99f6be72c0abf8a55fac20395de74b.md) **>** [**Path.h**](Path_8h.md)

[Go to the documentation of this file](Path_8h.md)


```C++
//
// Created by Monika on 10.12.2021.
//

#ifndef SR_ENGINE_PATH_H
#define SR_ENGINE_PATH_H

#include <Utils/stdInclude.h>
#include <Utils/Math/Mathematics.h>
#include <Utils/Types/StringAtom.h>
#include <Utils/Common/Breakpoint.h>
#include <Utils/Serialization/ObjectDataAccessor.h>

namespace SR_UTILS_NS {
    class IDeserializer;
    class ISerializer;

    class SR_COMMON_DLL_API Path {
    public:
        enum class Type {
            Undefined, File, Folder
        };

    public:
        Path();
        Path(const Path& path);
        Path(const char* path);
        Path(SR_UTILS_NS::StringAtom stringAtom);
        Path(std::string path);
        Path(std::string_view path);
        Path(const std::wstring& path);

        Path(Path&& path) noexcept;
        ~Path();

        Path& operator=(Path&& path) noexcept;
        operator const std::string&(); 
        Path& operator=(const Path& path);
        bool operator==(const Path& path) const noexcept;
        char operator[](size_t index) const noexcept;
        bool operator<(const Path& path) const noexcept;
        bool operator>(const Path& path) const noexcept;

    public:
        void Save(ISerializer& serializer, const SerializationId& id) const;
        void Load(IDeserializer& deserializer, const SerializationId& id);

        SR_DEPRECATED bool Make(Type type = Type::Undefined) const;
        bool Create() const;
        bool CreateIfNotExists() const;

        SR_NODISCARD bool Copy(const Path& destination) const;

        SR_NODISCARD std::string ToString() const;
        SR_NODISCARD std::string ConvertToFileName() const;
        SR_NODISCARD const std::string& ToStringRef() const;
        SR_NODISCARD std::string* ToStringPtr() { return &m_path; }
        SR_NODISCARD std::string_view ToStringView() const;
        SR_NODISCARD std::wstring ToWinApiPath() const;
        SR_NODISCARD std::wstring ToUnicodeString() const;
        SR_NODISCARD size_t GetHash() const;
        SR_NODISCARD uint64_t GetFileHash() const;
        SR_NODISCARD uint64_t GetFolderHash(uint64_t deep = SR_UINT64_MAX) const;
        SR_NODISCARD const char* CStr() const;
        SR_NODISCARD const char* c_str() const;

        SR_NODISCARD Path GetPrevious() const;
        SR_NODISCARD Path GetFolder() const;
        SR_NODISCARD Path Concat(const Path& path) const;
        SR_NODISCARD Path ConcatExt(const std::string& ext) const;
        SR_NODISCARD Path ConcatExt(const std::string_view& ext) const;
        SR_NODISCARD Path ConcatExt(const char* ext) const;
        SR_NODISCARD Path ConcatExt(SR_UTILS_NS::StringAtom ext) const;
        SR_NODISCARD Path RemoveSubPath(const Path& subPath) const;

        SR_NODISCARD bool empty() const;
        SR_NODISCARD bool IsSubPath(const Path& subPath) const;
        SR_NODISCARD bool Contains(const std::string_view& str) const;
        SR_NODISCARD bool IsHidden() const;
        SR_NODISCARD bool Exists() const;
        SR_NODISCARD bool Exists(Type type) const;

        SR_NODISCARD Type GetType() const;
        SR_NODISCARD bool IsDir() const;
        SR_NODISCARD bool IsFile() const;
        SR_NODISCARD bool IsAbs() const;
        SR_NODISCARD bool IsEmpty() const;
        SR_NODISCARD bool IsDirEmpty() const;

        SR_NODISCARD std::list<Path> GetFiles() const;
        SR_NODISCARD std::list<Path> GetFolders() const;
        SR_NODISCARD std::list<Path> GetAll() const;

        SR_NODISCARD std::string_view GetExtensionView() const;
        SR_NODISCARD std::string_view GetBaseNameView() const;
        SR_NODISCARD std::string_view View() const;
        SR_NODISCARD std::string GetExtension() const;
        SR_NODISCARD std::string GetBaseName() const;
        SR_NODISCARD std::string GetBaseNameAndExt() const;
        SR_NODISCARD std::string_view GetBaseNameAndExtView() const;
        SR_NODISCARD std::string_view GetWithoutExtensionView() const;
        SR_NODISCARD std::string GetWithoutExtension() const;

    private:
        const std::string& GetNormalized() const;

    private:
        mutable std::string m_path;
        mutable uint64_t m_hash = SR_UINT64_MAX;
        mutable bool m_isNormalized = false;

    };
}

namespace SR_UTILS_NS {
    template<> struct ObjectDataAccessor<SR_UTILS_NS::Path> {
        static void Save(ISerializer& serializer, const SR_UTILS_NS::Path& value, const SerializationId& id) {
            value.Save(serializer, id);
        }

        static void Load(IDeserializer& deserializer, SR_UTILS_NS::Path& value, const SerializationId& id) {
            value.Load(deserializer, id);
        }
    };
}

template<> struct fmt::formatter<SR_UTILS_NS::Path>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(SR_UTILS_NS::Path const& str, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "{}", str.ToStringView());
    }
};

#endif //SR_ENGINE_PATH_H
```


