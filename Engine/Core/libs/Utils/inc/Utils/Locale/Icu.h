//
// Created by Monika on 23.10.2022.
//

#ifndef SRENGINE_ICU_H
#define SRENGINE_ICU_H

#include <Utils/Debug.h>

#define U_DISABLE_RENAMING 1
#define U_COMMON_IMPLEMENTATION 0
#define U_STATIC_IMPLEMENTATION 1

#include <unicode/urename.h>
#include <unicode/uversion.h>

#include <unicode/utypes.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/utf.h>
#include <unicode/utf16.h>

namespace SR_UTILS_NS::Locale {
    enum class EncMethodType {
        Skip = 0,    ///< Skip illegal/unconvertable characters
        Stop = 1,    ///< Stop conversion and throw conversion_error
        Default = Skip  ///< Default method - skip
    };
}

#define SR_UCNV_GET_MAX_BYTES_FOR_STRING(length, maxCharSize) \
     (((int32_t)(length)+10)*(int32_t)(maxCharSize))

namespace SR_UTILS_NS::Locale::ICU {
    template<typename CharType, int char_size = sizeof(CharType)> class IcuStdConverter {
    public:
        typedef CharType char_type;
        typedef std::basic_string<char_type> string_type;
    public:
        explicit IcuStdConverter(std::string charset, EncMethodType cv = EncMethodType::Skip);
        virtual ~IcuStdConverter() = default;

    public:
        SR_NODISCARD virtual icu::UnicodeString IcuChecked(const char_type* begin, const char_type* end) const = 0;
        SR_NODISCARD virtual icu::UnicodeString Icu(const char_type* begin, const char_type* end) const = 0;
        SR_NODISCARD virtual string_type Std(const icu::UnicodeString& str) const = 0;
        SR_NODISCARD virtual size_t Cut(const icu::UnicodeString& str,
                   const char_type* begin,
                   const char_type* end,
                   size_t n,
                   size_t from_u,
                   size_t from_c) const = 0;

    };

    template<typename CharType> class IcuStdConverter<CharType, 1> {
    public:
        typedef CharType char_type;
        typedef std::basic_string<char_type> string_type;
    public:
        explicit IcuStdConverter(std::string charset, EncMethodType cvt_type = EncMethodType::Skip)
            : charset_(charset)
            , m_mode(cvt_type)
        {
            uconv cvt(charset_, cvt_type);
            max_len_ = cvt.max_char_size();
        }

    public:
        SR_NODISCARD icu::UnicodeString IcuChecked(const char_type* vb, const char_type* ve) const {
            return Icu(vb, ve); /// Already done
        }

        SR_NODISCARD icu::UnicodeString Icu(const char_type* vb, const char_type* ve) const {
            const char* begin = reinterpret_cast<const char*>(vb);
            const char* end = reinterpret_cast<const char*>(ve);
            uconv cvt(charset_, m_mode);
            UErrorCode err = U_ZERO_ERROR;
            icu::UnicodeString tmp(begin, end - begin, cvt.cvt(), err);

            if (U_FAILURE(err)) {
                SRHalt("Something went wrong!");
                return icu::UnicodeString();
            }

            return tmp;
        }

        SR_NODISCARD string_type Std(const icu::UnicodeString& str) const {
            uconv cvt(charset_, m_mode);
            return cvt.go(str.getBuffer(), str.length(), max_len_);
        }

        SR_NODISCARD size_t Cut(const icu::UnicodeString& str,
                   const char_type* begin,
                   const char_type* end,
                   size_t n,
                   size_t from_u,
                   size_t from_char) const
        {
            size_t code_points = str.countChar32(from_u, n);
            uconv cvt(charset_, m_mode);
            return cvt.cut(code_points, begin + from_char, end);
        }

        struct uconv {
        public:
            explicit uconv(const std::string& charset, EncMethodType cvt_type = EncMethodType::Skip) {
                UErrorCode err = U_ZERO_ERROR;
                cvt_ = ucnv_open(charset.c_str(), &err);
                if(!cvt_ || U_FAILURE(err)) {
                    if(cvt_) {
                        ucnv_close(cvt_);
                    }

                    if (U_FAILURE(err)) {
                        SRHalt("Invalid charset error!");
                        return;
                    }
                }

                try {
                    if(cvt_type == EncMethodType::Skip) {
                        ucnv_setFromUCallBack(cvt_, UCNV_FROM_U_CALLBACK_SKIP, 0, 0, 0, &err);

                        if (U_FAILURE(err)) {
                            SRHalt("Something went wrong!");
                            throw;
                        }

                        err = U_ZERO_ERROR;
                        ucnv_setToUCallBack(cvt_, UCNV_TO_U_CALLBACK_SKIP, 0, 0, 0, &err);

                        if (U_FAILURE(err)) {
                            SRHalt("Something went wrong!");
                            throw;
                        }
                    }
                    else {
                        ucnv_setFromUCallBack(cvt_, UCNV_FROM_U_CALLBACK_STOP, 0, 0, 0, &err);

                        if (U_FAILURE(err)) {
                            SRHalt("Something went wrong!");
                            throw;
                        }

                        err = U_ZERO_ERROR;
                        ucnv_setToUCallBack(cvt_, UCNV_TO_U_CALLBACK_STOP, 0, 0, 0, &err);

                        if (U_FAILURE(err)) {
                            SRHalt("Something went wrong!");
                            throw;
                        }
                    }
                }
                catch(...) {
                    ucnv_close(cvt_);
                    throw;
                }
            }

            int max_char_size() { return ucnv_getMaxCharSize(cvt_); }

            string_type go(const UChar* buf, int length, int max_size) {
                string_type res;
                res.resize(SR_UCNV_GET_MAX_BYTES_FOR_STRING(length, max_size));
                char* ptr = reinterpret_cast<char*>(&res[0]);
                UErrorCode err = U_ZERO_ERROR;
                int n = ucnv_fromUChars(cvt_, ptr, res.size(), buf, length, &err);

                if (U_FAILURE(err)) {
                    SRHalt("Something went wrong!");
                    return string_type();
                }

                res.resize(n);
                return res;
            }

            size_t cut(size_t n, const char_type* begin, const char_type* end)
            {
                const char_type* saved = begin;
                while(n > 0 && begin < end) {
                    UErrorCode err = U_ZERO_ERROR;
                    ucnv_getNextUChar(cvt_, &begin, end, &err);
                    if(U_FAILURE(err))
                        return 0;
                    n--;
                }
                return begin - saved;
            }

            UConverter* cvt() { return cvt_; }

            ~uconv() { ucnv_close(cvt_); }

        private:
            UConverter* cvt_ = nullptr;
        };

    private:
        int max_len_;
        std::string charset_;
        EncMethodType m_mode;

    };

    template<typename CharType> class IcuStdConverter<CharType, 2> {
    public:
        typedef CharType char_type;
        typedef std::basic_string<char_type> string_type;
    public:
        explicit IcuStdConverter(std::string, EncMethodType mode = EncMethodType::Skip)
            : m_mode(mode)
        { }

    public:
        SR_NODISCARD icu::UnicodeString IcuChecked(const char_type* begin, const char_type* end) const {
            icu::UnicodeString tmp(end - begin, 0, 0); /// make inital capacity
            while (begin != end) {
                UChar cl = *begin++;
                if (U16_IS_SINGLE(cl)) {
                    tmp.append(static_cast<UChar32>(cl));
                }
                else if (U16_IS_LEAD(cl)) {
                    if (begin == end) {
                        SRAssert2(m_mode != EncMethodType::Stop, "Something went wrong!");
                        return icu::UnicodeString();
                    }
                    else {
                        UChar ct = *begin++;
                        if (!U16_IS_TRAIL(ct)) {
                            SRAssert2(m_mode != EncMethodType::Stop, "Something went wrong!");
                            return icu::UnicodeString();
                        }
                        else {
                            UChar32 c = U16_GET_SUPPLEMENTARY(cl, ct);
                            tmp.append(c);
                        }
                    }
                }
                else {
                    SRAssert2(m_mode != EncMethodType::Stop, "Something went wrong!");
                    return icu::UnicodeString();
                }
            }
            return tmp;
        }

        SR_NODISCARD icu::UnicodeString Icu(const char_type* vb, const char_type* ve) const {
            const UChar* begin = reinterpret_cast<const UChar*>(vb);
            const UChar* end = reinterpret_cast<const UChar*>(ve);
            icu::UnicodeString tmp(begin, end - begin);
            return tmp;
        }

        SR_NODISCARD string_type Std(const icu::UnicodeString& str) const {
            const char_type* ptr = reinterpret_cast<const char_type*>(str.getBuffer());
            return string_type(ptr, str.length());
        }

        SR_NODISCARD size_t Cut(const icu::UnicodeString&,
                   const char_type*,
                   const char_type*,
                   size_t n,
                   size_t,
                   size_t) const
        {
            return n;
        }

    private:
        EncMethodType m_mode;

    };

    template<typename CharType> class IcuStdConverter<CharType, 4> {
    public:
        typedef CharType char_type;
        typedef std::basic_string<char_type> string_type;
    public:
        explicit IcuStdConverter(std::string, EncMethodType cvt_type = EncMethodType::Skip)
            : m_mode(cvt_type)
        { }

    public:
        SR_NODISCARD icu::UnicodeString IcuChecked(const char_type* begin, const char_type* end) const {
            icu::UnicodeString tmp(end - begin, 0, 0); /// make inital capacity
            while(begin != end) {
                UChar32 c = static_cast<UChar32>(*begin++);
                if(U_IS_UNICODE_CHAR(c)) {
                    tmp.append(c);
                }
                else {
                    SRAssert2(m_mode != EncMethodType::Stop, "Something went wrong!");
                    return icu::UnicodeString();
                }
            }
            return tmp;
        }

        SR_NODISCARD icu::UnicodeString Icu(const char_type* begin, const char_type* end) const {
            icu::UnicodeString tmp(end - begin, 0, 0); /// make inital capacity
            while(begin != end) {
                UChar32 c = static_cast<UChar32>(*begin++);
                tmp.append(c);
            }
            return tmp;
        }

        SR_NODISCARD string_type Std(const icu::UnicodeString& str) const {
            string_type tmp;
            tmp.resize(str.length());
            UChar32* ptr = reinterpret_cast<UChar32*>(&tmp[0]);

#ifdef __SUNPRO_CC
            int len = 0;
#else
            ::int32_t len = 0;
#endif

            UErrorCode code = U_ZERO_ERROR;
            u_strToUTF32(ptr, tmp.size(), &len, str.getBuffer(), str.length(), &code);

            if (U_FAILURE(code)) {
                SRHalt("Something went wrong!");
                return icu::UnicodeString();
            }

            tmp.resize(len);

            return tmp;
        }

        SR_NODISCARD size_t Cut(const icu::UnicodeString& str,
                   const char_type* ,
                   const char_type*,
                   size_t n,
                   size_t from_u,
                   size_t) const
        {
            return str.countChar32(from_u, n);
        }

    private:
        EncMethodType m_mode;

    };
}

#endif //SRENGINE_ICU_H
