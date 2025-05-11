

# File Convert.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Localization**](dir_d04d15d43c1872e420a2eb3b2dcaf10d.md) **>** [**Convert.h**](Convert_8h.md)

[Go to the documentation of this file](Convert_8h.md)


```C++
//
// Created by Monika on 23.10.2022.
//

#ifndef SR_ENGINE_CONVERT_H
#define SR_ENGINE_CONVERT_H

#include <Utils/Localization/Icu.h>

namespace SR_UTILS_NS::Localization {
    //std::string ConvertBetween(
    //     const char *begin,
    //     const char *end,
    //     const std::string& to_charset,
    //     const std::string& from_charset,
    //     EncMethodType how = EncMethodType::Default
    // ) {
    //     auto&& from = ICU::IcuStdConverter<char>(from_charset, how);
    //     auto&& to = ICU::IcuStdConverter<char>(to_charset, how);
    //     return to.Std(from.Icu(begin, end));
    // }

    template<typename CharType> std::basic_string<CharType> ConvertTo(const char *begin, const char *end, const char *charset, EncMethodType how = EncMethodType::Default) {
    #ifdef SR_ICU
        auto&& from = ICU::IcuStdConverter<char>(charset, how);
        auto&& to = ICU::IcuStdConverter<CharType>("UTF-8", how);
        return to.Std(from.IcuChecked(begin, end));
    #else
        return std::basic_string<CharType>();
    #endif
    }

    template<typename CharType> std::string ConvertFrom(const CharType *begin, const CharType *end, const char *charset, EncMethodType how = EncMethodType::Default) {
    #ifdef SR_ICU
        auto&& from = ICU::IcuStdConverter<CharType>("UTF-8", how);
        auto&& to = ICU::IcuStdConverter<char>(charset, how);
        return to.Std(from.IcuChecked(begin, end));
    #else
        return std::string();
    #endif
    }
}

#endif //SR_ENGINE_CONVERT_H
```


