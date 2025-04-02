

# File Regex.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Regex.h**](Regex_8h.md)

[Go to the documentation of this file](Regex_8h.md)


```C++
//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_REGEX_H
#define SR_ENGINE_REGEX_H

#include <Utils/stdInclude.h>

namespace SR_HTYPES_NS {
    class Regex {
    public:
        Regex() = default;
        Regex(const std::string& regex); 
        Regex(Regex&& other) noexcept;

        Regex& operator=(Regex&& other) noexcept;

    public:
        bool Search(const std::string& input);

        SR_NODISCARD uint64_t Size() const noexcept;
        SR_NODISCARD std::string Prefix() const noexcept;
        SR_NODISCARD std::string Suffix() const noexcept;

        SR_NODISCARD std::string operator[](int64_t index) const noexcept;

    private:
        std::regex m_regex;
        std::smatch m_match;

    };
}

#endif //SR_ENGINE_REGEX_H
```


