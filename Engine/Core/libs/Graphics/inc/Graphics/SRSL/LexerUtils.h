//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_LEXERUTILS_H
#define SRENGINE_SRSL_LEXERUTILS_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Types/Regex.h>
#include <Utils/Debug.h>

namespace SR_SRSL_NS {
    static SR_INLINE constexpr char SRSL_SPACE_CHARS[] = { ' ', '\n', '\r', '\t' };

    static SR_INLINE constexpr char SRSL_IDENTIFIER_CHARS[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'A',
        'b', 'B',
        'c', 'C',
        'd', 'D',
        'e', 'E',
        'f', 'F',
        'g', 'G',
        'h', 'H',
        'i', 'I',
        'j', 'J',
        'k', 'K',
        'l', 'L',
        'm', 'M',
        'n', 'N',
        'o', 'O',
        'p', 'P',
        'q', 'Q',
        'r', 'R',
        's', 'S',
        't', 'T',
        'u', 'U',
        'v', 'V',
        'w', 'W',
        'x', 'X',
        'y', 'Y',
        'z', 'Z',
        '_',
    };

    static bool IsIdentifier(const std::string& token) noexcept {
        bool isFirst = true;

        for (auto&& tokenChar : token) {
            if (isFirst && SR_MATH_NS::IsNumber(std::string(1, tokenChar))) {
                return false;
            }
            isFirst = false;

            for (auto&& identifierChar : SRSL_IDENTIFIER_CHARS) {
                if (tokenChar == identifierChar) {
                    goto skip;
                }
            }

            return false;

        skip:
            SR_NOOP;
        }

        return true;
    }

    static bool IsOperator(const std::string& operation) noexcept {
        static const std::vector<std::string> operators = {
                "+", "-", "!", ".", "~", ">", "^", "<", ":", "?", "|", "&", "%",
        };
        return std::find(operators.begin(), operators.end(), operation) != operators.end();
    }

    enum class LexemKind {
        Unknown,

        OpeningSquareBracket, /// [
        ClosingSquareBracket, /// ]

        OpeningAngleBracket,  /// <
        ClosingAngleBracket,  /// >

        OpeningCurlyBracket,  /// {
        ClosingCurlyBracket,  /// }

        OpeningBracket,       /// (
        ClosingBracket,       /// )

        Plus,                 /// +
        Minus,                /// -
        Multiply,             /// *
        Divide,               /// /
        Percent,              /// %
        Assign,               /// =
        Semicolon,            /// ;
        Dot,                  /// .
        Comma,                /// ,
        Negation,             /// !
        And,                  /// &
        Or,                   /// |
        Question,             /// ?
        Colon,                /// :
        Tilda,                /// ~
        Exponentiation,       /// ^

        Integer,              /// 0-9

        Macro,                /// #

        Identifier,           /// _az_AZ_19_
    };

    SR_ENUM_NS_CLASS_T(SRSLReturnCode, uint16_t,
        Success, OutOfBounds, InvalidLexicalTree,
        UnknownLexem, UnexceptedLexem, UnexceptedDot, InvalidExpression, InvalidComplexExpression,
        IncompleteExpression, EmptyExpression, InvalidScope, InvalidCall,
        InvalidAngleBracket, InvalidAssign, InvalidMathToken, InvalidNumericToken, EmptyToken, InvalidIncrementOrDecrement
    );

    struct SRSLResult {
        SRSLResult() = default;

        SRSLResult(SRSLReturnCode code) /** NOLINT */
            : code(code)
            , position(0)
        { }

        SRSLResult(SRSLReturnCode code, uint64_t position)
            : code(code)
            , position(position)
        { }

        SRSLResult(SRSLResult&& other) noexcept
            : code(SR_UTILS_NS::Exchange(other.code, { }))
            , position(SR_UTILS_NS::Exchange(other.position, { }))
        { }

        SRSLResult& operator=(SRSLResult&& other) noexcept {
            code = SR_UTILS_NS::Exchange(other.code, { });
            position = SR_UTILS_NS::Exchange(other.position, { });
            return *this;
        }

        SRSLReturnCode code;
        uint64_t position;
    };

    struct LocationEntity {
        LocationEntity() = default;

        LocationEntity(uint64_t offset, uint64_t length)
            : offset(offset)
            , length(length)
        { }

        uint64_t offset = 0;
        uint64_t length = 0;
    };

    struct Lexem : public LocationEntity {
        Lexem() = default;

        Lexem(uint64_t offset, uint64_t length, LexemKind kind, std::string&& value)
            : LocationEntity(offset, length)
            , kind(kind)
            , value(SR_UTILS_NS::Exchange(value, { }))
        { }

        Lexem(uint64_t offset, uint64_t length, LexemKind kind)
            : LocationEntity(offset, length)
            , kind(kind)
        { }

        LexemKind kind = LexemKind::Unknown;
        std::string value;
    };

    SR_INLINE_STATIC std::string LexemsToString(const std::vector<Lexem>& lexems) {
        std::string code;

        LexemKind previously = LexemKind::Unknown;
        for (auto&& lexem : lexems) {
            if (lexem.kind == previously && previously == LexemKind::Identifier) {
                code += " ";
            }
            code += lexem.value;
            previously = lexem.kind;
        }

        return code;
    }
}

#endif //SRENGINE_SRSL_LEXERUTILS_H
