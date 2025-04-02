

# File StringAtom.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**StringAtom.h**](StringAtom_8h.md)

[Go to the documentation of this file](StringAtom_8h.md)


```C++
//
// Created by Monika on 29.09.2021.
//

#ifndef SR_ENGINE_STRING_ATOM_H
#define SR_ENGINE_STRING_ATOM_H

#include <Utils/stdInclude.h>
#include <Utils/Common/Hashes.h>

#include <fmt/format.h>

namespace SR_UTILS_NS {
    class StringHashInfo;

    class SR_DLL_EXPORT StringAtom {
        SR_INLINE_STATIC std::string DEFAULT = std::string();
        static StringHashInfo* DEFAULT_STRING_INFO;
    public:
        StringAtom();

        StringAtom(const StringAtom& str) = default;

        StringAtom(StringHashInfo* pInfo); 
        StringAtom(const char* str); 
        StringAtom(const std::string& str); 
        StringAtom(std::string_view str); 

    public:
        operator const std::string&() const noexcept; 
        operator std::string_view() const noexcept; 
        bool operator==(const StringAtom& rhs) const noexcept;
        bool operator==(const std::string& rhs) const noexcept;
        bool operator==(const char* rhs) const noexcept;
        StringAtom& operator=(const std::string& str);
        StringAtom& operator=(const char* str);
        void operator()(const std::string& str);
        void operator()(const char* str);

        bool operator<(const StringAtom& other) const noexcept;
        bool operator<(uint64_t hash) const noexcept;

        SR_NODISCARD SR_FORCE_INLINE operator uint64_t() const noexcept { return GetHash(); }

        SR_NODISCARD char operator[](size_t index) const noexcept;

    public:
        SR_NODISCARD uint64_t Size() const;
        SR_NODISCARD uint64_t size() const;
        SR_NODISCARD bool Contains(const char* str) const;
        SR_NODISCARD bool Empty() const;
        SR_NODISCARD bool empty() const;
        SR_NODISCARD uint64_t GetHash() const;
        SR_NODISCARD std::string ToString() const;
        SR_NODISCARD const char* ToCStr() const;
        SR_NODISCARD const char* c_str() const;
        SR_NODISCARD const char* data() const;
        SR_NODISCARD const std::string& ToStringRef() const;
        SR_NODISCARD std::string_view ToStringView() const;

        void clear() {
            Clear();
        }

        void Clear();

    private:
        StringHashInfo* m_info = nullptr;

    };

    template<typename T> constexpr bool IsString() {
        if (!IsVolatile<T>()) {
            return IsString<volatile T>();
        }

        return
            std::is_same_v<T, volatile std::string> ||
            std::is_same_v<T, volatile std::string_view> ||
            std::is_same_v<T, volatile StringAtom>;
    }
}

namespace std {
    template<> struct hash<SR_UTILS_NS::StringAtom> {
        size_t operator()(SR_UTILS_NS::StringAtom const& object) const noexcept {
            return object.GetHash();
        }
    };

    template<> struct less<SR_UTILS_NS::StringAtom> {
        bool operator()(const SR_UTILS_NS::StringAtom& lhs, const SR_UTILS_NS::StringAtom& rhs) const noexcept {
            return lhs.GetHash() < rhs.GetHash();
        }
    };
}

template<> struct fmt::formatter<SR_UTILS_NS::StringAtom>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

    template<typename FormatContext>
    auto format(SR_UTILS_NS::StringAtom const& str, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "{}", str.ToStringView());
    }
};

#endif //SR_ENGINE_STRING_ATOM_H
```


