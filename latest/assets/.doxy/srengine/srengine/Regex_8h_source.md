

# File Regex.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Regex.h**](Regex_8h.md)

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


