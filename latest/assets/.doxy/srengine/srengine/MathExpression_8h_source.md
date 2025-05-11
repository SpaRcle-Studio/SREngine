

# File MathExpression.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**MathExpression.h**](MathExpression_8h.md)

[Go to the documentation of this file](MathExpression_8h.md)


```C++
//
// Created by Monika on 23.01.2023.
//

#ifndef SR_ENGINE_SRSL_MATHEXPRESSION_H
#define SR_ENGINE_SRSL_MATHEXPRESSION_H

#include <Utils/Common/Singleton.h>
#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    class SRSLMathExpression : public SR_UTILS_NS::Singleton<SRSLMathExpression> {
        SR_REGISTER_SINGLETON(SRSLMathExpression)
    public:
        SR_NODISCARD std::pair<SRSLExpr*, SRSLResult> Analyze(std::vector<Lexem>&& lexems);

    private:
        void Clear();

        SR_NODISCARD int32_t GetPriority(const std::string& operation, bool prefix) const;
        SR_NODISCARD bool IsIncrementOrDecrement(const std::string& operation) const;

        SR_NODISCARD SRSLExpr* ParseBinaryExpression(int32_t minPriority);
        SR_NODISCARD SRSLExpr* ParseSimpleExpression();
        SR_NODISCARD SRSLExpr* TryParseString();

        SR_NODISCARD std::string ParseToken();

        SR_NODISCARD bool IsPrefix() const noexcept;

        SR_NODISCARD bool InBounds() const noexcept;
        SR_NODISCARD bool IsHasErrors() const noexcept;
        SR_NODISCARD const Lexem* GetLexem(int64_t offset) const;
        SR_NODISCARD const Lexem* GetCurrentLexem() const;

    private:
        SRSLResult m_result;

        std::vector<Lexem> m_lexems;
        int64_t m_currentLexem = 0;

    };
}

#endif //SR_ENGINE_SRSL_MATHEXPRESSION_H
```


