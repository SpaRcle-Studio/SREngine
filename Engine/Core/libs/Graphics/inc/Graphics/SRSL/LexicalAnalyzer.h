//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_LEXICAL_ANALYZER_H
#define SRENGINE_SRSL_LEXICAL_ANALYZER_H

#include <Utils/Common/Singleton.h>
#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    class SRSLLexicalAnalyzer : public SR_UTILS_NS::Singleton<SRSLLexicalAnalyzer> {
        friend class SR_UTILS_NS::Singleton<SRSLLexicalAnalyzer>;
    private:
        enum class LXAState {
            Decorators, Decorator, DecoratorArgs,
            Integer, Float, NumericDot
        };
    public:
        SR_ENUM_CLASS_T(LXAReturnCode, uint16_t,
            Success, UnknownLexem, UnexceptedLexem
        );

        struct LXAResult {
            LXAResult() = default;

            LXAResult(LXAReturnCode code) /** NOLINT */
                : code(code)
                , position(0)
            { }

            LXAResult(LXAReturnCode code, uint64_t position)
                : code(code)
                , position(position)
            { }

            LXAReturnCode code;
            uint64_t position;
        };

    public:
        SR_NODISCARD std::pair<SRSLLexicalTree, LXAResult> Analyze(std::vector<Lexem>&& lexems);

    private:
        void Clear();

        void ProcessMain();
        void ProcessBracket();
        void ProcessDecorators();
        void ProcessExpression();

        SR_NODISCARD bool InBounds() const noexcept;
        SR_NODISCARD bool IsHasErrors() const noexcept;
        SR_NODISCARD const Lexem* GetLexem(int64_t offset) const;
        SR_NODISCARD const Lexem* GetCurrentLexem() const;

    private:
        SRSLLexicalTree m_lexicalTree;

        SRSLDecorators* m_decorators = nullptr;
        SRSLExpr* m_expr = nullptr;

        LXAResult m_result;
        std::list<LXAState> m_states;

        std::vector<Lexem> m_lexems;
        int64_t m_currentLexem = 0;

    };
}

#endif //SRENGINE_SRSL_LEXICAL_ANALYZER_H