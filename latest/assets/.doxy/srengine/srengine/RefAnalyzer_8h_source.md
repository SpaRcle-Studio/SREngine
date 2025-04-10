

# File RefAnalyzer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**RefAnalyzer.h**](RefAnalyzer_8h.md)

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
        void AnalyzeEntryPoint(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLFunction* pFunction);

    private:
        SRSLAnalyzedTree::Ptr m_analyzedTree;

    };
}

#endif //SR_ENGINE_REFANALYZER_H
```


