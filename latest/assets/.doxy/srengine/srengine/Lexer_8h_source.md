

# File Lexer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**Lexer.h**](Lexer_8h.md)

[Go to the documentation of this file](Lexer_8h.md)


```C++
//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_SRSL_LEXER_H
#define SR_ENGINE_SRSL_LEXER_H

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
        uint64_t m_line = 0;
        uint64_t m_position = 0;

        Lexems m_lexems;

    };
}

#endif //SR_ENGINE_SRSL_LEXER_H
```


