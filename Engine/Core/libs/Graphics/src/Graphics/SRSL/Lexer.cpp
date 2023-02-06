//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/Lexer.h>
#include <Utils/FileSystem/FileSystem.h>

namespace SR_SRSL_NS {
    SRSLLexer::~SRSLLexer() {
        Clear();
    }

    SRSLLexer::Lexems SRSLLexer::Parse(const SR_UTILS_NS::Path& path) {
        return ParseInternal(std::move(SR_UTILS_NS::FileSystem::ReadAllText(path.ToString())));
    }

    SRSLLexer::Lexems SRSLLexer::ParseString(std::string code) {
        return ParseInternal(std::move(code));
    }

    bool SRSLLexer::InBounds() const noexcept {
        return m_offset < m_source.size();
    }

    SRSLLexer::Lexems SRSLLexer::ParseInternal(std::string&& code) {
        Clear();

        m_source = std::move(code);

        while (InBounds())
        {
            SkipSpaces();

            if(!InBounds()) {
                break;
            }

            if (auto&& lexem = ProcessLexem()) {
                m_lexems.emplace_back(lexem.value());
            }
        }

        return SR_UTILS_NS::Exchange(m_lexems, { });
    }

    SRSLLexer::ProcessedLexem SRSLLexer::ProcessLexem() {
        switch (m_source[m_offset]) {
            case '[': return Lexem(m_offset++, 1, LexemKind::OpeningSquareBracket, "[");
            case ']': return Lexem(m_offset++, 1, LexemKind::ClosingSquareBracket, "]");

            case '<': return Lexem(m_offset++, 1, LexemKind::OpeningAngleBracket, "<");
            case '>': return Lexem(m_offset++, 1, LexemKind::ClosingAngleBracket, ">");

            case '{': return Lexem(m_offset++, 1, LexemKind::OpeningCurlyBracket, "{");
            case '}': return Lexem(m_offset++, 1, LexemKind::ClosingCurlyBracket, "}");

            case '(': return Lexem(m_offset++, 1, LexemKind::OpeningBracket, "(");
            case ')': return Lexem(m_offset++, 1, LexemKind::ClosingBracket, ")");

            case '+': return Lexem(m_offset++, 1, LexemKind::Plus, "+");
            case '-': return Lexem(m_offset++, 1, LexemKind::Minus, "-");
            case '*': return Lexem(m_offset++, 1, LexemKind::Multiply, "*");
            case '%': return Lexem(m_offset++, 1, LexemKind::Percent, "%");
            case '^': return Lexem(m_offset++, 1, LexemKind::Exponentiation, "^");
            case '?': return Lexem(m_offset++, 1, LexemKind::Question, "?");
            case ':': return Lexem(m_offset++, 1, LexemKind::Colon, ":");
            case '~': return Lexem(m_offset++, 1, LexemKind::Tilda, "~");

            case '/': {
                if (m_offset + 1 < m_source.size()) {
                    switch (m_source[m_offset + 1]) {
                        case '/':
                        case '*':
                            SkipComment();
                            return {};
                        default:
                            break;
                    }
                }

                return Lexem(m_offset++, 1, LexemKind::Divide, "/");
            }
            case '=': return Lexem(m_offset++, 1, LexemKind::Assign, "=");
            case ';': return Lexem(m_offset++, 1, LexemKind::Semicolon, ";");
            case '.': return Lexem(m_offset++, 1, LexemKind::Dot, ".");
            case ',': return Lexem(m_offset++, 1, LexemKind::Comma, ",");
            case '!': return Lexem(m_offset++, 1, LexemKind::Negation, "!");
            case '&': return Lexem(m_offset++, 1, LexemKind::And, "&");
            case '|': return Lexem(m_offset++, 1, LexemKind::Or, "|");

            case '0': return Lexem(m_offset++, 1, LexemKind::Integer, "0");
            case '1': return Lexem(m_offset++, 1, LexemKind::Integer, "1");
            case '2': return Lexem(m_offset++, 1, LexemKind::Integer, "2");
            case '3': return Lexem(m_offset++, 1, LexemKind::Integer, "3");
            case '4': return Lexem(m_offset++, 1, LexemKind::Integer, "4");
            case '5': return Lexem(m_offset++, 1, LexemKind::Integer, "5");
            case '6': return Lexem(m_offset++, 1, LexemKind::Integer, "6");
            case '7': return Lexem(m_offset++, 1, LexemKind::Integer, "7");
            case '8': return Lexem(m_offset++, 1, LexemKind::Integer, "8");
            case '9': return Lexem(m_offset++, 1, LexemKind::Integer, "9");

            case '#': return Lexem(m_offset++, 1, LexemKind::Macro, "#");

            default:
                break;
        }

        const uint64_t offset = m_offset;

        auto&& identifier = ProcessIdentifier();

        const uint64_t length = identifier.size();

        return Lexem(offset, length, LexemKind::Identifier, std::move(identifier));
    }

    std::string SRSLLexer::ProcessIdentifier() {
        std::string identifier;

    retry:
        for (auto&& identifierChar : SRSL_IDENTIFIER_CHARS) {
            if (m_source[m_offset] == identifierChar) {
                identifier += identifierChar;
                ++m_offset;
                goto retry;
            }
        }

        if (identifier.empty()) {
            SR_ERROR("SRSLLexer::ProcessIdentifier() : invalid identifier!"
                 " \n\tPosition: " + std::to_string(m_offset) +
                 " \n\tIdentifier: \"" + m_source[m_offset] + "\""
            );
            ++m_offset;
        }

        return identifier;
    }

    void SRSLLexer::SkipSpaces() {
    retry:
        while (InBounds()) {
            for (auto&& spaceChar : SRSL_SPACE_CHARS) {
                if (spaceChar == m_source[m_offset]) {
                    ++m_offset;
                    goto retry;
                }
            }

            break;
        }
    }

    void SRSLLexer::SkipComment() {
        m_offset += 1; /// skip '/'

        switch (m_source[m_offset]) {
            case '/': {
                m_offset += 1; /// skip '/'
                while (m_offset < m_source.size() && m_source[m_offset] != '\n' && m_source[m_offset] != '\r') {
                    m_offset += 1;
                }
                break;
            }
            case '*': {
                m_offset += 1; /// skip '*'
                while (m_offset + 1 < m_source.size() && !(m_source[m_offset] == '*' && m_source[m_offset + 1] == '/')) {
                    m_offset += 1;
                }
                /// skip "*/"
                if (m_offset + 1 < m_source.size() && (m_source[m_offset] == '*' && m_source[m_offset + 1] == '/')) {
                    m_offset += 2;
                }
                break;
            }
            default:
                SRHalt("SRSLLexer::SkipComment() : something went wrong!");
                return;
        }
    }

    void SRSLLexer::Clear() {
        m_source.clear();
        m_offset = 0;
        m_lexems.clear();
    }
}