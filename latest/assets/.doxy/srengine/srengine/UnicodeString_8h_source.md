

# File UnicodeString.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**UnicodeString.h**](UnicodeString_8h.md)

[Go to the documentation of this file](UnicodeString_8h.md)


```C++
//
// Created by Monika on 23.10.2022.
//

#ifndef SR_ENGINE_UNICODESTRING_H
#define SR_ENGINE_UNICODESTRING_H

#include <Utils/stdInclude.h>

namespace SR_HTYPES_NS {
    class UnicodeString {
    public:
        using CharType = char32_t;
        using Iterator = std::u32string::iterator;
        using ConstIterator = std::u32string::const_iterator;

    public:
        UnicodeString() = default;
        UnicodeString(const UnicodeString& other);
        UnicodeString(UnicodeString&& other) noexcept;

        UnicodeString(const std::string& str); 
        UnicodeString(const std::u16string& str); 
        UnicodeString(const std::u32string& str); 

        virtual ~UnicodeString() = default;

        UnicodeString& operator=(const UnicodeString& other);
        UnicodeString& operator=(UnicodeString&& other) noexcept;

        UnicodeString& operator=(const std::u32string& other);
        UnicodeString& operator=(std::u32string&& other) noexcept;

        bool operator==(const std::u32string& str) const noexcept { return m_internal == str; }
        bool operator!=(const std::u32string& str) const noexcept { return m_internal != str; }

        bool operator==(const UnicodeString& str) const noexcept { return m_internal == str.m_internal; }
        bool operator!=(const UnicodeString& str) const noexcept { return m_internal != str.m_internal; }

        SR_NODISCARD std::u32string_view View() const noexcept { return m_internal; }

        SR_NODISCARD operator std::u32string() const noexcept { return m_internal; } 
        SR_NODISCARD operator std::u32string_view() const noexcept { return m_internal; } 

    public:
        void resize(size_t size);

        SR_NODISCARD bool empty() const noexcept { return m_internal.empty(); }
        SR_NODISCARD size_t size() const noexcept { return m_internal.size(); }

        SR_NODISCARD Iterator begin() noexcept { return m_internal.begin(); }
        SR_NODISCARD Iterator end() noexcept { return m_internal.end(); }

        SR_NODISCARD ConstIterator begin() const noexcept { return m_internal.begin(); }
        SR_NODISCARD ConstIterator end() const noexcept { return m_internal.end(); }

        SR_NODISCARD const CharType* c_str() const noexcept { return m_internal.c_str(); }
        SR_NODISCARD CharType* data() noexcept { return m_internal.data(); }

        SR_NODISCARD CharType& operator [](size_t position) noexcept;
        SR_NODISCARD const CharType& operator [](size_t position) const noexcept;

    private:
        std::u32string m_internal;

    };
}

#endif //SR_ENGINE_UNICODESTRING_H
```


