//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/Lexer.h>
#include <Utils/FileSystem/FileSystem.h>

namespace SR_SRSL_NS {
    SRSLLexer::~SRSLLexer() {
        Clear();
    }

    SRSLLexer::Lexems SRSLLexer::Parse(const SR_UTILS_NS::Path& path, uint16_t fileIndex) {
        auto&& text = SR_UTILS_NS::FileSystem::ReadAllText(path.ToString());

        if (text.empty()) {
            SR_ERROR("SRSLLexer::Parse() : failed to read file!\n\tPath: " + path.ToStringRef());
        }

        return ParseInternal(std::move(text), fileIndex);
    }

    SRSLLexer::Lexems SRSLLexer::ParseString(std::string code, uint16_t fileIndex) {
        return ParseInternal(std::move(code), fileIndex);
    }

    bool SRSLLexer::InBounds() const noexcept {
        return m_offset < m_source.size();
    }

    SRSLLexer::Lexems SRSLLexer::ParseInternal(std::string&& code, uint16_t fileIndex) {
        Clear();

        m_source = std::move(code);
        m_fileIndex = fileIndex;

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
            case '[': return Lexem(m_offset++, 1, LexemKind::OpeningSquareBracket, "[", m_fileIndex);
            case ']': return Lexem(m_offset++, 1, LexemKind::ClosingSquareBracket, "]", m_fileIndex);

            case '<': return Lexem(m_offset++, 1, LexemKind::OpeningAngleBracket, "<", m_fileIndex);
            case '>': return Lexem(m_offset++, 1, LexemKind::ClosingAngleBracket, ">", m_fileIndex);

            case '{': return Lexem(m_offset++, 1, LexemKind::OpeningCurlyBracket, "{", m_fileIndex);
            case '}': return Lexem(m_offset++, 1, LexemKind::ClosingCurlyBracket, "}", m_fileIndex);

            case '(': return Lexem(m_offset++, 1, LexemKind::OpeningBracket, "(", m_fileIndex);
            case ')': return Lexem(m_offset++, 1, LexemKind::ClosingBracket, ")", m_fileIndex);

            case '+': return Lexem(m_offset++, 1, LexemKind::Plus, "+", m_fileIndex);
            case '-': return Lexem(m_offset++, 1, LexemKind::Minus, "-", m_fileIndex);
            case '*': return Lexem(m_offset++, 1, LexemKind::Multiply, "*", m_fileIndex);
            case '%': return Lexem(m_offset++, 1, LexemKind::Percent, "%", m_fileIndex);
            case '^': return Lexem(m_offset++, 1, LexemKind::Exponentiation, "^", m_fileIndex);
            case '?': return Lexem(m_offset++, 1, LexemKind::Question, "?", m_fileIndex);
            case ':': return Lexem(m_offset++, 1, LexemKind::Colon, ":", m_fileIndex);
            case '~': return Lexem(m_offset++, 1, LexemKind::Tilda, "~", m_fileIndex);

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

                return Lexem(m_offset++, 1, LexemKind::Divide, "/", m_fileIndex);
            }
            case '=': return Lexem(m_offset++, 1, LexemKind::Assign, "=", m_fileIndex);
            case ';': return Lexem(m_offset++, 1, LexemKind::Semicolon, ";", m_fileIndex);
            case '.': return Lexem(m_offset++, 1, LexemKind::Dot, ".", m_fileIndex);
            case ',': return Lexem(m_offset++, 1, LexemKind::Comma, ",", m_fileIndex);
            case '!': return Lexem(m_offset++, 1, LexemKind::Negation, "!", m_fileIndex);
            case '&': return Lexem(m_offset++, 1, LexemKind::And, "&", m_fileIndex);
            case '|': return Lexem(m_offset++, 1, LexemKind::Or, "|", m_fileIndex);

            case '0': return Lexem(m_offset++, 1, LexemKind::Integer, "0", m_fileIndex);
            case '1': return Lexem(m_offset++, 1, LexemKind::Integer, "1", m_fileIndex);
            case '2': return Lexem(m_offset++, 1, LexemKind::Integer, "2", m_fileIndex);
            case '3': return Lexem(m_offset++, 1, LexemKind::Integer, "3", m_fileIndex);
            case '4': return Lexem(m_offset++, 1, LexemKind::Integer, "4", m_fileIndex);
            case '5': return Lexem(m_offset++, 1, LexemKind::Integer, "5", m_fileIndex);
            case '6': return Lexem(m_offset++, 1, LexemKind::Integer, "6", m_fileIndex);
            case '7': return Lexem(m_offset++, 1, LexemKind::Integer, "7", m_fileIndex);
            case '8': return Lexem(m_offset++, 1, LexemKind::Integer, "8", m_fileIndex);
            case '9': return Lexem(m_offset++, 1, LexemKind::Integer, "9", m_fileIndex);

            case '#': return Lexem(m_offset++, 1, LexemKind::Macro, "#", m_fileIndex);

            default:
                break;
        }

        const uint64_t offset = m_offset;

        auto&& identifier = ProcessIdentifier();

        const uint64_t length = identifier.size();

        return Lexem(offset, length, LexemKind::Identifier, std::move(identifier), m_fileIndex);
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
        m_fileIndex = 0;
        m_offset = 0;
        m_lexems.clear();
    }
}