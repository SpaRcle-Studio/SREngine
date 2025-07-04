

# File LexicalAnalyzer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**LexicalAnalyzer.h**](LexicalAnalyzer_8h.md)

[Go to the documentation of this file](LexicalAnalyzer_8h.md)


```C++
//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_SRSL_LEXICAL_ANALYZER_H
#define SR_ENGINE_SRSL_LEXICAL_ANALYZER_H

#include <Graphics/SRSL/MathExpression.h>

namespace SR_SRSL_NS {
    class SRSLLexicalAnalyzer : public SR_UTILS_NS::Singleton<SRSLLexicalAnalyzer> {
        SR_REGISTER_SINGLETON(SRSLLexicalAnalyzer)
    private:
        enum class LXAState {
            Decorators, Decorator, DecoratorArgs,
            Expression, Variable, Function, FunctionArgs, FunctionBody, IfStatement, IfStatementBody,
            ForStatement, ForStatementVariable, ForStatementCondition, ForStatementExpression, ForStatementBody,
            WhileStatement, WhileStatementCondition, WhileStatementBody,
            StructureStatement, StructureStatementBody,
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

#endif //SR_ENGINE_SRSL_LEXICAL_ANALYZER_H
```


