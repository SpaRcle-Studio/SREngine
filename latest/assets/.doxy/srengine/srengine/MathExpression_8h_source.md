

# File MathExpression.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**MathExpression.h**](MathExpression_8h.md)

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


