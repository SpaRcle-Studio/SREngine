//
// Created by Monika on 23.10.2022.
//

#ifndef SRENGINE_UTF_H
#define SRENGINE_UTF_H

#include <Utils/stdInclude.h>

namespace SR_UTILS_NS::Locale::Utf {
    typedef uint32_t CodePoint;

    static const CodePoint Illegal = 0xFFFFFFFFu;

    static const CodePoint Incomplete = 0xFFFFFFFEu;

    SR_INLINE_STATIC bool IsValidCodePoint(CodePoint v) {
        if (v > 0x10FFFF) {
            return false;
        }

        return !(0xD800 <= v && v <= 0xDFFF);
    }

    template<typename CharType, int size = sizeof(CharType)> struct UtfTraits;

    template<typename CharType> struct UtfTraits<CharType, 1> {
        typedef CharType char_type;

        static int TrailLength(char_type ci) {
            unsigned char c = ci;
            if (c < 128)
                return 0;
            if (SR_UNLIKELY(c < 194))
                return -1;
            if (c < 224)
                return 1;
            if (c < 240)
                return 2;
            if (SR_LIKELY(c <= 244))
                return 3;
            return -1;
        }

        static const int MAX_WIDTH = 4;

        static int Width(CodePoint value) {
            if (value <= 0x7F) {
                return 1;
            }
            else if (value <= 0x7FF) {
                return 2;
            }
            else if (SR_LIKELY(value <= 0xFFFF)) {
                return 3;
            }
            else {
                return 4;
            }
        }

        static bool IsTrail(char_type ci) {
            unsigned char c = ci;
            return (c & 0xC0) == 0x80;
        }

        static bool IsLead(char_type ci) {
            return !IsTrail(ci);
        }

        template<typename Iterator> static CodePoint Decode(Iterator &p, Iterator e) {
            if (SR_UNLIKELY(p == e))
                return Incomplete;

            unsigned char lead = *p++;

            /// First byte is fully validated here
            int trail_size = TrailLength(lead);

            if (SR_UNLIKELY(trail_size < 0))
                return Illegal;

            ///
            /// Ok as only ASCII may be of size = 0
            /// also optimize for ASCII text
            ///
            if (trail_size == 0)
                return lead;

            CodePoint c = lead & ((1 << (6 - trail_size)) - 1);

            /// Read the rest
            unsigned char tmp;
            switch (trail_size) {
                case 3:
                    if (SR_UNLIKELY(p == e))
                        return Incomplete;
                    tmp = *p++;
                    if (!IsTrail(tmp))
                        return Illegal;
                    c = (c << 6) | (tmp & 0x3F);
                case 2:
                    if (SR_UNLIKELY(p == e))
                        return Incomplete;
                    tmp = *p++;
                    if (!IsTrail(tmp))
                        return Illegal;
                    c = (c << 6) | (tmp & 0x3F);
                case 1:
                    if (SR_UNLIKELY(p == e))
                        return Incomplete;
                    tmp = *p++;
                    if (!IsTrail(tmp))
                        return Illegal;
                    c = (c << 6) | (tmp & 0x3F);
            }

            /// Check code point validity: no surrogates and
            /// valid range
            if (SR_UNLIKELY(!IsValidCodePoint(c)))
                return Illegal;

            /// make sure it is the most compact representation
            if (SR_UNLIKELY(Width(c) != trail_size + 1))
                return Illegal;

            return c;

        }

        template<typename Iterator> static CodePoint DecodeValid(Iterator &p) {
            unsigned char lead = *p++;
            if (lead < 192)
                return lead;

            int trail_size;

            if (lead < 224) {
                trail_size = 1;
            }
            else if (SR_LIKELY(lead < 240)) { /// non-BMP rare
                trail_size = 2;
            }
            else
                trail_size = 3;

            CodePoint c = lead & ((1 << (6 - trail_size)) - 1);

            switch (trail_size) {
                case 3:
                    c = (c << 6) | (static_cast<unsigned char>(*p++) & 0x3F);
                case 2:
                    c = (c << 6) | (static_cast<unsigned char>(*p++) & 0x3F);
                case 1:
                    c = (c << 6) | (static_cast<unsigned char>(*p++) & 0x3F);
            }

            return c;
        }


        template<typename Iterator> static Iterator Encode(CodePoint value, Iterator out) {
            if (value <= 0x7F) {
                *out++ = static_cast<char_type>(value);
            }
            else if (value <= 0x7FF) {
                *out++ = static_cast<char_type>((value >> 6) | 0xC0);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }
            else if (SR_LIKELY(value <= 0xFFFF)) {
                *out++ = static_cast<char_type>((value >> 12) | 0xE0);
                *out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }
            else {
                *out++ = static_cast<char_type>((value >> 18) | 0xF0);
                *out++ = static_cast<char_type>(((value >> 12) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>(((value >> 6) & 0x3F) | 0x80);
                *out++ = static_cast<char_type>((value & 0x3F) | 0x80);
            }

            return out;
        }
    }; /// utf8

    template<typename CharType> struct UtfTraits<CharType, 2> {
        typedef CharType char_type;

        /// See RFC 2781
        static bool IsFirstSurrogate(uint16_t x) {
            return 0xD800 <= x && x <= 0xDBFF;
        }

        static bool IsSecondSurrogate(uint16_t x) {
            return 0xDC00 <= x && x <= 0xDFFF;
        }

        static CodePoint CombineSurrogate(uint16_t w1, uint16_t w2) {
            return ((CodePoint(w1 & 0x3FF) << 10) | (w2 & 0x3FF)) + 0x10000;
        }

        static int TrailLength(char_type c) {
            if (IsFirstSurrogate(c))
                return 1;

            if (IsSecondSurrogate(c))
                return -1;

            return 0;
        }

        ///
        /// Returns true if c is trail code unit, always false for UTF-32
        ///
        static bool IsTrail(char_type c) {
            return IsSecondSurrogate(c);
        }

        ///
        /// Returns true if c is lead code unit, always true of UTF-32
        ///
        static bool IsLead(char_type c) {
            return !IsSecondSurrogate(c);
        }

        template<typename It> static CodePoint Decode(It &current, It last) {
            if (SR_UNLIKELY(current == last))
                return Incomplete;

            uint16_t w1 = *current++;
            if (SR_LIKELY(w1 < 0xD800 || 0xDFFF < w1)) {
                return w1;
            }

            if (w1 > 0xDBFF)
                return Illegal;

            if (current == last)
                return Incomplete;

            uint16_t w2 = *current++;
            if (w2 < 0xDC00 || 0xDFFF < w2)
                return Illegal;

            return CombineSurrogate(w1, w2);
        }

        template<typename It> static CodePoint DecodeValid(It &current) {
            uint16_t w1 = *current++;
            if (SR_LIKELY(w1 < 0xD800 || 0xDFFF < w1)) {
                return w1;
            }
            uint16_t w2 = *current++;
            return CombineSurrogate(w1, w2);
        }

        static const int MAX_WIDTH = 2;

        static int Width(CodePoint u) {
            return u >= 0x10000 ? 2 : 1;
        }

        template<typename It> static It Encode(CodePoint u, It out) {
            if (SR_LIKELY(u <= 0xFFFF)) {
                *out++ = static_cast<char_type>(u);
            } else {
                u -= 0x10000;
                *out++ = static_cast<char_type>(0xD800 | (u >> 10));
                *out++ = static_cast<char_type>(0xDC00 | (u & 0x3FF));
            }
            return out;
        }
    }; /// utf16;

    template<typename CharType> struct UtfTraits<CharType, 4> {
        typedef CharType char_type;

        static int TrailLength(char_type c) {
            if (IsValidCodePoint(c))
                return 0;

            return -1;
        }

        static bool IsTrail(char_type /*c*/) {
            return false;
        }

        static bool IsLead(char_type /*c*/) {
            return true;
        }

        template<typename It> static CodePoint DecodeValid(It &current) {
            return *current++;
        }

        template<typename It> static CodePoint Decode(It &current, It last) {
            if (SR_UNLIKELY(current == last)) {
                return Incomplete;
            }

            CodePoint c = *current++;
            if (SR_UNLIKELY(!IsValidCodePoint(c))) {
                return Illegal;
            }

            return c;
        }

        static const int MAX_WIDTH = 1;

        static int Width(CodePoint /*u*/) {
            return 1;
        }

        template<typename It> static It Encode(CodePoint u, It out) {
            *out++ = static_cast<char_type>(u);
            return out;
        }
    }; // utf32
}

#endif //SRENGINE_UTF_H
