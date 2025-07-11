

# File StringAtom.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**StringAtom.h**](StringAtom_8h.md)

[Go to the documentation of this file](StringAtom_8h.md)


```C++
//
// Created by Monika on 29.09.2021.
//

#ifndef SR_ENGINE_STRING_ATOM_H
#define SR_ENGINE_STRING_ATOM_H

#include <Utils/stdInclude.h>
#include <Utils/Common/Hashes.h>

namespace SR_UTILS_NS {
    class StringHashInfo;

    class SR_COMMON_DLL_API StringAtom {
        static std::string DEFAULT;
        static StringHashInfo* DEFAULT_STRING_INFO;
    public:
        StringAtom();

        StringAtom(const StringAtom& other) = default;

        StringAtom(StringHashInfo* pInfo); 
        StringAtom(const char* str); 
        StringAtom(const std::string& str); 
        StringAtom(std::string_view str); 

    public:
        operator const std::string&() const noexcept; 
        operator std::string_view() const noexcept; 
        bool operator==(const StringAtom& rhs) const noexcept;
        bool operator==(const std::string& rhs) const noexcept;
        bool operator==(const std::string_view& rhs) const noexcept;
        bool operator==(const char* rhs) const noexcept;
        StringAtom& operator=(const std::string& str);
        StringAtom& operator=(const char* str);

        bool operator<(const StringAtom& other) const noexcept;
        bool operator<(uint64_t hash) const noexcept;

        SR_NODISCARD operator uint64_t() const noexcept;

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

        void clear();
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
    auto format(SR_UTILS_NS::StringAtom const& str, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "{}", str.ToStringView());
    }
};

#endif //SR_ENGINE_STRING_ATOM_H
```


