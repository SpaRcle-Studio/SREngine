

# File Lexer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**Lexer.h**](Lexer_8h.md)

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

        Lexems m_lexems;

    };
}

#endif //SR_ENGINE_SRSL_LEXER_H
```


