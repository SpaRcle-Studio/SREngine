//
// Created by Monika on 23.01.2023.
//

#ifndef SRENGINE_SRSL_MATHEXPRESSION_H
#define SRENGINE_SRSL_MATHEXPRESSION_H

#include <Utils/Common/Singleton.h>
#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    class SRSLMathExpression : public SR_UTILS_NS::Singleton<SRSLMathExpression> {
        friend class SR_UTILS_NS::Singleton<SRSLMathExpression>;
    public:
        SR_NODISCARD std::pair<SRSLExpr*, SRSLResult> Analyze(std::vector<Lexem>&& lexems);

    private:
        void Clear();

        SR_NODISCARD int32_t GetPriority(const std::string& operation, bool prefix) const;
        SR_NODISCARD bool IsIncrementOrDecrement(const std::string& operation) const;

        SR_NODISCARD SRSLExpr* ParseBinaryExpression(int32_t minPriority);
        SR_NODISCARD SRSLExpr* ParseSimpleExpression();

        SR_NODISCARD std::string ParseToken();

        SR_NODISCARD bool IsPrefix() const noexcept;
        SR_NODISCARD bool IsOperator(const std::string& operation) const noexcept;
        SR_NODISCARD bool IsIdentifier(const std::string& token) const noexcept;

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

#endif //SRENGINE_SRSL_MATHEXPRESSION_H
