

# File PreProcessor.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**PreProcessor.h**](PreProcessor_8h.md)

[Go to the documentation of this file](PreProcessor_8h.md)


```C++
//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_SRSL_PREPROCESSOR_H
#define SR_ENGINE_SRSL_PREPROCESSOR_H

#include <Utils/Common/Singleton.h>
#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    class SRSLPreProcessor : public SR_UTILS_NS::Singleton<SRSLPreProcessor> {
        SR_REGISTER_SINGLETON(SRSLPreProcessor)
        enum class PPState : uint8_t {
            Idle, Macro, MacroName, IncludeOpen, IncludePath
        };
    public:
        using Include = SR_UTILS_NS::StringAtom;
        using Includes = std::vector<Include>;
        using OutResult = std::pair<std::vector<Lexem>, SRSLResult>;

    public:
        SR_NODISCARD OutResult Process(std::vector<Lexem>&& lexems, Includes& includes);

    private:
        void Clear();

        void ProcessMain();

        SR_NODISCARD bool InBounds() const noexcept;
        SR_NODISCARD bool IsHasErrors() const noexcept;
        SR_NODISCARD const Lexem* GetLexem(int64_t offset) const;
        SR_NODISCARD const Lexem* GetCurrentLexem() const;

    private:
        SRSLResult m_result;

        std::vector<Lexem> m_lexems;
        int64_t m_currentLexem = 0;

        std::string m_include;
        Includes m_includes;

        PPState m_state = PPState::Idle;

    };
}

#endif //SR_ENGINE_SRSL_PREPROCESSOR_H
```


