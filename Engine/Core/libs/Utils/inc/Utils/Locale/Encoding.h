//
// Created by Monika on 23.10.2022.
//

#ifndef SRENGINE_ENCODING_H
#define SRENGINE_ENCODING_H

#include <Utils/Locale/Convert.h>
#include <Utils/Locale/UTF.h>

namespace SR_UTILS_NS::Locale {
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

    ///
    /// Convert a Unicode NUL terminated string \a str other Unicode encoding
    ///
    template<typename CharOut,typename CharIn> std::basic_string<CharOut> UtfToUtf(CharIn const *str, EncMethodType how = EncMethodType::Default) {
        CharIn const *end = str;

        while (*end) {
            end++;
        }

        return UtfToUtf<CharOut, CharIn>(str, end, how);
    }

    ///
    /// Convert a Unicode string \a str other Unicode encoding
    ///
    template<typename CharOut,typename CharIn> std::basic_string<CharOut> UtfToUtf(std::basic_string<CharIn> const &str, EncMethodType how = EncMethodType::Default) {
        return UtfToUtf<CharOut,CharIn>(str.c_str(), str.c_str() + str.size(), how);
    }

    ///std::string Between(const char* begin,
    ///    const char* end,
    ///    const std::string& to_charset,
    ///    const std::string& from_charset,
    ///    EncMethodType how = EncMethodType::Default
    ///) {
    ///    return ConvertBetween(begin, end, to_charset, from_charset, how);
    ///}

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

#endif //SRENGINE_ENCODING_H
