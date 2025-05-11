

# File Encoding.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Localization**](dir_d04d15d43c1872e420a2eb3b2dcaf10d.md) **>** [**Encoding.h**](Encoding_8h.md)

[Go to the documentation of this file](Encoding_8h.md)


```C++
//
// Created by Monika on 23.10.2022.
//

#ifndef SR_ENGINE_ENCODING_H
#define SR_ENGINE_ENCODING_H

#include <Utils/Localization/Convert.h>
#include <Utils/Localization/UTF.h>

namespace SR_UTILS_NS::Localization {
    SR_MAYBE_UNUSED static void SetLocale() {
        setlocale(LC_ALL, "rus");
        setlocale(LC_NUMERIC, "C");
    }

    template<typename CharOut,typename CharIn> std::basic_string<CharOut> UtfToUtf(CharIn const *begin, CharIn const *end, EncMethodType how = EncMethodType::Default) {
        std::basic_string<CharOut> result;
        result.reserve(end - begin);

        typedef std::back_insert_iterator<std::basic_string<CharOut>> inserter_type;
        inserter_type inserter(result);

        Utf::CodePoint c;

        while (begin != end) {
            c = Utf::UtfTraits<CharIn>::template Decode<CharIn const *>(begin, end);
            if (c == Utf::Illegal || c == Utf::Incomplete) {
                if (how == EncMethodType::Stop) {
                    SRHalt("Conversion error!");
                    return std::basic_string<CharOut>();
                }
            }
            else {
                Utf::UtfTraits<CharOut>::template Encode<inserter_type>(c, inserter);
            }
        }
        return result;
    }

    template<typename CharOut,typename CharIn> std::basic_string<CharOut> UtfToUtf(CharIn const *str, EncMethodType how = EncMethodType::Default) {
        CharIn const *end = str;

        while (*end) {
            end++;
        }

        return UtfToUtf<CharOut, CharIn>(str, end, how);
    }

    template<typename CharOut,typename CharIn> std::basic_string<CharOut> UtfToUtf(std::basic_string<CharIn> const& str, EncMethodType how = EncMethodType::Default) {
        return UtfToUtf<CharOut, CharIn>(str.c_str(), str.c_str() + str.size(), how);
    }

    template<typename CharOut,typename CharIn> std::basic_string<CharOut> UtfToUtf(std::basic_string_view<CharIn> const& str, EncMethodType how = EncMethodType::Default) {
        return UtfToUtf<CharOut, CharIn>(str.data(), str.data() + str.size(), how);
    }


    template<typename CharType> std::basic_string<CharType> ToUtf(const char* begin, const char* end, const std::string& charset, EncMethodType how = EncMethodType::Default) {
        return ConvertTo<CharType>(begin, end, charset.c_str(), how);
    }

    template<typename CharType> std::string FromUtf(const CharType* begin, const CharType* end, const std::string& charset, EncMethodType how = EncMethodType::Default) {
        return ConvertFrom<CharType>(begin, end, charset.c_str(), how);
    }

    //std::string NormalizeEncoding(const char* cCharset) {
    //    std::string charset;
    //    charset.reserve(std::strlen(cCharset));
    //    while(*cCharset != 0) {
    //        char c = *cCharset++;
    //        if('0' <= c && c <= '9') {
    //            charset += c;
    //        }
    //        else if('a' <= c && c <= 'z') {
    //            charset += c;
    //        }
    //        else if('A' <= c && c <= 'Z') {
    //            charset += char(c - 'A' + 'a');
    //        }
    //    }
    //    return charset;
    //}
}

#endif //SR_ENGINE_ENCODING_H
```


