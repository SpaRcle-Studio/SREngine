

# File AssignExpander.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**AssignExpander.h**](AssignExpander_8h.md)

[Go to the documentation of this file](AssignExpander_8h.md)


```C++
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
```


