

# File LexerUtils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**LexerUtils.h**](LexerUtils_8h.md)

[Go to the documentation of this file](LexerUtils_8h.md)


```C++
//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_SRSL_LEXERUTILS_H
#define SR_ENGINE_SRSL_LEXERUTILS_H

#include <Graphics/macros.h>

#include <Utils/Common/Singleton.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Common/ToString.h>
#include <Utils/Types/Regex.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Debug.h>
#include <Utils/Common/StringAtomLiterals.h>

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

    SR_MAYBE_UNUSED static bool IsIdentifier(const std::string& token) noexcept {
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

    SR_MAYBE_UNUSED static bool IsOperator(const std::string& operation) noexcept {
        static const std::vector<std::string> operators = {
                "+", "-", "!", ".", "~", ">", "^", "<", ":", "?", "|", "&", "%",
        };
        return std::find(operators.begin(), operators.end(), operation) != operators.end();
    }

    SR_ENUM_NS_CLASS_T(LexemKind, uint16_t,
        Unknown,

        OpeningSquareBracket, 
        ClosingSquareBracket, 

        OpeningAngleBracket,  
        ClosingAngleBracket,  

        OpeningCurlyBracket,  
        ClosingCurlyBracket,  

        OpeningBracket,       
        ClosingBracket,       

        Plus,                 
        Minus,                
        Multiply,             
        Divide,               
        Percent,              
        Assign,               
        Semicolon,            
        Dot,                  
        Comma,                
        Negation,             
        And,                  
        Or,                   
        Question,             
        Colon,                
        Tilda,                
        Exponentiation,       

        Integer,              

        Macro,                

        String,               

        Identifier            
    );

    static std::string LexemKindToString(LexemKind lexem) {
        static std::map<LexemKind, std::string> lexemToString = {
                { LexemKind::OpeningSquareBracket, "[" },
                { LexemKind::ClosingSquareBracket, "]" },
                { LexemKind::OpeningAngleBracket, "<" },
                { LexemKind::ClosingAngleBracket, ">" },
                { LexemKind::OpeningCurlyBracket, "{" },
                { LexemKind::ClosingCurlyBracket, "}" },
                { LexemKind::OpeningBracket, "(" },
                { LexemKind::ClosingBracket, ")" },
                { LexemKind::Plus, "+" },
                { LexemKind::Minus, "-" },
                { LexemKind::Multiply, "*" },
                { LexemKind::Divide, "/" },
                { LexemKind::Percent, "%" },
                { LexemKind::Assign, "=" },
                { LexemKind::Semicolon, ";" },
                { LexemKind::Dot, "." },
                { LexemKind::Comma, "," },
                { LexemKind::Negation, "!" },
                { LexemKind::And, "&" },
                { LexemKind::Or, "|" },
                { LexemKind::Question, "?" },
                { LexemKind::Colon, ":" },
                { LexemKind::Tilda, "~" },
                { LexemKind::Exponentiation, "^" },
                { LexemKind::Macro, "#" },
        };
        if (lexemToString.find(lexem) != lexemToString.end()) {
            return lexemToString[lexem];
        }
        return std::string();
    }

    SR_ENUM_NS_CLASS_T(SRSLReturnCode, uint16_t,
        Unknown, Success, OutOfBounds, InvalidLexicalTree,
        UnknownLexem, UnexceptedLexem, UnexceptedDot, InvalidExpression, InvalidComplexExpression, InvalidDecorator,
        IncompleteExpression, EmptyExpression, InvalidScope, InvalidCall, InvalidIfStatement, UnknownShaderLanguage,
        InvalidAngleBracket, InvalidAssign, InvalidMathToken, InvalidNumericToken, EmptyToken, InvalidIncrementOrDecrement, InvalidListEnd,
        WrongMacroName, IncludeNotExists, UnexceptedError, IncludeError, InvalidFunction, InvalidString
    );

    struct LocationEntity {
        LocationEntity() = default;

        LocationEntity(uint64_t offset, uint64_t length, uint16_t fileIndex, uint64_t line, uint64_t position)
            : offset(offset)
            , length(length)
            , fileIndex(fileIndex)
            , line(line)
            , position(position)
        { }

        uint64_t offset = 0;
        uint64_t position = 0;
        uint64_t line = 0;
        uint64_t length = 0;
        uint16_t fileIndex = 0;
    };

    struct Lexem : public LocationEntity {
        Lexem() = default;

        Lexem(uint64_t offset, uint64_t length, LexemKind kind, std::string&& value, uint16_t fileIndex, uint64_t line, uint64_t position)
            : LocationEntity(offset, length, fileIndex, line, position)
            , kind(kind)
            , value(SR_UTILS_NS::Exchange(value, { }))
        { }

        Lexem(uint64_t offset, uint64_t length, LexemKind kind, uint16_t fileIndex, uint64_t line, uint64_t position)
            : LocationEntity(offset, length, fileIndex, line, position)
            , kind(kind)
        { }

        LexemKind kind = LexemKind::Unknown;
        std::string value;
    };

    struct SRSLMessage {
        SRSLMessage(SRSLReturnCode code) 
            : code(code)
        { }

        SRSLMessage(SRSLReturnCode code, const Lexem& lexem)
            : code(code)
            , position(lexem.position)
            , characterIndex(lexem.offset)
            , line(lexem.line)
            , fileIndex(lexem.fileIndex)
            , lexemKind(lexem.kind)
        { }

        SRSLMessage(SRSLReturnCode code, const Lexem* pLexem)
            : SRSLMessage(code, *pLexem)
        { }

        SR_NODISCARD std::string ToString(const std::vector<SR_UTILS_NS::StringAtom>& files, uint8_t tab) const {
            std::string message = SR_UTILS_NS::EnumReflector::ToStringAtom(code);

            if (fileIndex != SR_UINT16_MAX) {
                if (fileIndex >= files.size()) {
                    SRHalt("Invalid index!");
                }
                else {
                    auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                #ifdef SR_WIN32
                    message += "\n{}File: {}/{}:{}:{}"_format(std::string(tab, '\t'), resourcesPath, files[fileIndex].ToStringRef(), line, position);
                #else
                    message += "\n{}File: file:///{}/{}:{}:{}"_format(std::string(tab, '\t'), resourcesPath, files[fileIndex].ToStringRef(), line, position);
                #endif
                }
            }

            if (!description.empty()) {
                message += "\n" + std::string(tab, '\t') + "Description: " + description;
            }

            if (lexemKind != LexemKind::Unknown) {
                message += "\n" + std::string(tab, '\t') + "Lexem: " +
                        SR_UTILS_NS::EnumReflector::ToStringAtom(lexemKind).ToStringRef();
            }

            return message;
        }

        SRSLMessage& SetDescription(const std::string& text) { description = text; return *this; }

        SRSLReturnCode code = SRSLReturnCode::Unknown;
        uint64_t position = SR_UINT64_MAX;
        uint64_t characterIndex = SR_UINT64_MAX;
        uint64_t line = SR_UINT64_MAX;
        uint16_t fileIndex = SR_UINT16_MAX;
        LexemKind lexemKind = LexemKind::Unknown;
        std::string description;

    };

    struct SRSLResult {
        SRSLResult() = default;

        SRSLResult(SRSLReturnCode code) { 
            AddError(code);
        }

        SRSLResult(SRSLReturnCode code, const Lexem* pLexem) {
            AddError(SRSLMessage(code, pLexem));
        }

        SRSLMessage& AddError(const SRSLMessage& message) { return errors.emplace_back(message); }

        SR_NODISCARD bool HasErrors() const { return !errors.empty(); }
        SR_NODISCARD bool HasWarnings() const { return !warnings.empty(); }
        SR_NODISCARD bool HasAny() const { return HasErrors() || HasWarnings(); }

        SR_NODISCARD std::string ToString(const std::vector<SR_UTILS_NS::StringAtom>& files, uint8_t tab = 1) const {
            std::string message;

            for (auto&& msg : errors) {
                message += "\n" + std::string(tab, '\t') + "Error code: " + msg.ToString(files, tab + 1);
            }

            for (auto&& msg : warnings) {
                message += "\n" + std::string(tab, '\t') + "Warning: " + msg.ToString(files, tab + 1);
            }

            return message;
        }

        uint64_t processedLexems = 0;
        std::list<SRSLMessage> warnings;
        std::list<SRSLMessage> errors;
    };

    SR_MAYBE_UNUSED SR_INLINE_STATIC std::string LexemsToString(const std::vector<Lexem>& lexems) {
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

#endif //SR_ENGINE_SRSL_LEXERUTILS_H
```


