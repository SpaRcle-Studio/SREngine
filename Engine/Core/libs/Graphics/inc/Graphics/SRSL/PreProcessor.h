//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_PREPROCESSOR_H
#define SRENGINE_SRSL_PREPROCESSOR_H

#include <Utils/Common/Singleton.h>
#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    class SRSLPreProcessor : public SR_UTILS_NS::Singleton<SRSLPreProcessor> {
        friend class SR_UTILS_NS::Singleton<SRSLPreProcessor>;
        enum class PPState : uint8_t {
            Idle, Macro, MacroName, IncludeOpen, IncludePath
        };
    public:
        using Include = std::string;
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

#endif //SRENGINE_SRSL_PREPROCESSOR_H
