//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_LEXICAL_ANALYZER_H
#define SRENGINE_SRSL_LEXICAL_ANALYZER_H

#include <Graphics/SRSL/MathExpression.h>

namespace SR_SRSL_NS {
    class SRSLLexicalAnalyzer : public SR_UTILS_NS::Singleton<SRSLLexicalAnalyzer> {
        SR_REGISTER_SINGLETON(SRSLLexicalAnalyzer)
    private:
        enum class LXAState {
            Decorators, Decorator, DecoratorArgs,
            Expression, Variable, Function, FunctionArgs, FunctionBody, IfStatement, IfStatementBody,
            ForStatement, ForStatementVariable, ForStatementCondition, ForStatementExpression, ForStatementBody,
        };
    public:
        SR_NODISCARD std::pair<SRSLAnalyzedTree::Ptr, SRSLResult> Analyze(std::vector<Lexem>&& lexems);

    private:
        void Clear();

        void ProcessMain();
        void ProcessBracket();
        void ProcessDecorators();
        void ProcessExpression(bool isFunctionName = false, bool isSimpleExpr = false);

        SR_NODISCARD SRSLLexicalUnit* TryProcessIdentifier();

        SR_NODISCARD bool InBounds() const noexcept;
        SR_NODISCARD bool IsHasErrors() const noexcept;
        SR_NODISCARD const Lexem* GetLexem(int64_t offset) const;
        SR_NODISCARD const Lexem* GetCurrentLexem() const;

    private:
        std::list<SRSLLexicalTree*> m_lexicalTree;

        SRSLDecorators* m_decorators = nullptr;
        SRSLExpr* m_expr = nullptr;

        SRSLResult m_result;
        std::list<LXAState> m_states;

        std::vector<Lexem> m_lexems;
        int64_t m_currentLexem = 0;

    };
}

#endif //SRENGINE_SRSL_LEXICAL_ANALYZER_H