

# File LexicalAnalyzer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**LexicalAnalyzer.h**](LexicalAnalyzer_8h.md)

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


