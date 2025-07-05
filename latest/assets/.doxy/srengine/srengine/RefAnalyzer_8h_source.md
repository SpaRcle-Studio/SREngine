

# File RefAnalyzer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**RefAnalyzer.h**](RefAnalyzer_8h.md)

[Go to the documentation of this file](RefAnalyzer_8h.md)


```C++
//
// Created by Monika on 03.02.2023.
//

#ifndef SR_ENGINE_REFANALYZER_H
#define SR_ENGINE_REFANALYZER_H

#include <Graphics/SRSL/LexicalTree.h>

namespace SR_GRAPH_NS {
    enum class ShaderStage : uint8_t;
}

namespace SR_SRSL_NS {
    struct SRSLUseStack {
        using Ptr = std::shared_ptr<SRSLUseStack>;

        SR_NODISCARD std::set<SR_GRAPH_NS::ShaderStage> IsVariableUsedInEntryPointsExt(const std::string& name) const;
        SR_NODISCARD bool IsVariableUsedInEntryPoints(const std::string& name) const;
        SR_NODISCARD bool IsVariableUsed(const std::string& name) const;
        SR_NODISCARD bool IsFunctionUsed(const std::string& name) const;
        SR_NODISCARD bool IsStructUsed(const std::string &name) const;

        SR_NODISCARD SRSLUseStack::Ptr FindFunction(const std::string& name) const;

        SR_NODISCARD std::string ToString(int32_t deep) const;

        void Concat(const SRSLUseStack::Ptr& pOther);

        std::map<std::string, SRSLUseStack::Ptr> functions;
        std::set<std::string> variables;
    };

    class SRSLRefAnalyzer : public SR_UTILS_NS::Singleton<SRSLRefAnalyzer> {
        SR_REGISTER_SINGLETON(SRSLRefAnalyzer)
    public:
        SR_NODISCARD SRSLUseStack::Ptr Analyze(const SRSLAnalyzedTree::Ptr& pAnalyzedTree);

    private:
        SR_NODISCARD SRSLFunction* FindFunction(const std::string& name) const;
        SR_NODISCARD SRSLFunction* FindFunction(SRSLLexicalTree* pTree, const std::string& name) const;
        SR_NODISCARD SRSLUseStack::Ptr AnalyzeTree(std::list<std::string>& stack, SRSLLexicalTree* pTree);

        void AnalyzeVariable(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLVariable* pVariable);
        void AnalyzeExpression(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLExpr* pExpr);
        void AnalyzeArrayExpression(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLExpr* pExpr);
        void AnalyzeIfStatement(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLIfStatement* pIfStatement);
        void AnalyzeForStatement(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLForStatement* pForStatement);
        void AnalyzeWhileStatement(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLWhileStatement* pWhileStatement);
        void AnalyzeEntryPoint(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLFunction* pFunction);

    private:
        SRSLAnalyzedTree::Ptr m_analyzedTree;

    };
}

#endif //SR_ENGINE_REFANALYZER_H
```


