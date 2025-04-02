

# File Convert.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Localization**](dir_a49f0db6b4130ce5cf0adc29f1f90718.md) **>** [**Convert.h**](Convert_8h.md)

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


