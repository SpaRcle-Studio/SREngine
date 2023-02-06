//
// Created by Monika on 03.02.2023.
//

#ifndef SRENGINE_REFANALYZER_H
#define SRENGINE_REFANALYZER_H

#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    struct SRSLUseStack {
        using Ptr = std::shared_ptr<SRSLUseStack>;

        SR_NODISCARD bool IsVariableUsedInEntryPoints(const std::string& name) const;
        SR_NODISCARD bool IsVariableUsed(const std::string& name) const;
        SR_NODISCARD bool IsFunctionUsed(const std::string& name) const;

        SR_NODISCARD SRSLUseStack::Ptr FindFunction(const std::string& name) const;

        SR_NODISCARD std::string ToString(int32_t deep) const;

        void Concat(const SRSLUseStack::Ptr& pOther);

        std::map<std::string, SRSLUseStack::Ptr> functions;
        std::set<std::string> variables;
    };

    class SRSLRefAnalyzer : public SR_UTILS_NS::Singleton<SRSLRefAnalyzer> {
        friend class SR_UTILS_NS::Singleton<SRSLRefAnalyzer>;
    public:
        SR_NODISCARD SRSLUseStack::Ptr Analyze(const SRSLAnalyzedTree::Ptr& pAnalyzedTree);

    private:
        SR_NODISCARD SRSLFunction* FindFunction(const std::string& name) const;
        SR_NODISCARD SRSLFunction* FindFunction(SRSLLexicalTree* pTree, const std::string& name) const;
        SR_NODISCARD SRSLUseStack::Ptr AnalyzeTree(std::list<std::string>& stack, SRSLLexicalTree* pTree);

        void AnalyzeExpression(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLExpr* pExpr);
        void AnalyzeArrayExpression(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLExpr* pExpr);
        void AnalyzeIfStatement(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLIfStatement* pIfStatement);
        void AnalyzeEntryPoint(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLFunction* pFunction);

    private:
        SRSLAnalyzedTree::Ptr m_analyzedTree;

    };
}

#endif //SRENGINE_REFANALYZER_H
