//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_LEXER_H
#define SRENGINE_SRSL_LEXER_H

#include <Graphics/SRSL/LexerUtils.h>

namespace SR_SRSL_NS {
    class SRSLLexer : public SR_UTILS_NS::Singleton<SRSLLexer> {
        SR_REGISTER_SINGLETON(SRSLLexer)
        using Lexems = std::vector<Lexem>;
        using ProcessedLexem = std::optional<Lexem>;
        using SourceCode = std::vector<std::string>;
    protected:
        ~SRSLLexer() override;

    public:
        SR_NODISCARD Lexems Parse(const SR_UTILS_NS::Path& path, uint16_t fileIndex);
        SR_NODISCARD Lexems ParseString(std::string code, uint16_t fileIndex);

    private:
        SR_NODISCARD bool InBounds() const noexcept;
        SR_NODISCARD ProcessedLexem ProcessLexem();
        SR_NODISCARD std::string ProcessIdentifier();

        SR_NODISCARD Lexems ParseInternal(std::string&& code, uint16_t fileIndex);

        void Clear();

        void SkipSpaces();
        void SkipComment();

    private:
        std::string m_source;
        uint64_t m_offset = 0;
        uint16_t m_fileIndex = 0;

        Lexems m_lexems;

    };
}

#endif //SRENGINE_SRSL_LEXER_H
