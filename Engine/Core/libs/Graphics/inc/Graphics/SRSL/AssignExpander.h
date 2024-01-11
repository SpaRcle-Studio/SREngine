//
// Created by Monika on 24.01.2023.
//

#ifndef SR_ENGINE_SRSL_ASSIGNEXPANDER_H
#define SR_ENGINE_SRSL_ASSIGNEXPANDER_H

#include <Utils/Common/Singleton.h>
#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    class SRSLAssignExpander : public SR_UTILS_NS::Singleton<SRSLAssignExpander> {
        SR_REGISTER_SINGLETON(SRSLAssignExpander)
    public:
        SR_NODISCARD std::pair<std::vector<Lexem>, SRSLResult> Expand(std::vector<Lexem>&& lexems);

    private:
        void Clear();

        SR_NODISCARD std::vector<Lexem> GetLeftSide();
        SR_NODISCARD uint64_t FindSemicolon();

        void ProcessMain();
        void ExpandDouble();
        void ExpandTriple();

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

#endif //SR_ENGINE_SRSL_ASSIGNEXPANDER_H
