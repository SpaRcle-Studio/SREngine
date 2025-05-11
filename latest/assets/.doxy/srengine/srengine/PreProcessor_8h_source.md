

# File PreProcessor.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**PreProcessor.h**](PreProcessor_8h.md)

[Go to the documentation of this file](PreProcessor_8h.md)


```C++
//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_SRSL_PREPROCESSOR_H
#define SR_ENGINE_SRSL_PREPROCESSOR_H

#include <Utils/Common/Singleton.h>
#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    class SRSLPreProcessor : public SR_UTILS_NS::Singleton<SRSLPreProcessor> {
        SR_REGISTER_SINGLETON(SRSLPreProcessor)
        enum class PPState : uint8_t {
            Idle, Macro, MacroName, IncludeOpen, IncludePath
        };
    public:
        using Include = SR_UTILS_NS::StringAtom;
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

#endif //SR_ENGINE_SRSL_PREPROCESSOR_H
```


