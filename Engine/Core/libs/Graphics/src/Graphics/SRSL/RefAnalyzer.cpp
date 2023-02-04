//
// Created by Monika on 03.02.2023.
//

#include <Graphics/SRSL/RefAnalyzer.h>

namespace SR_SRSL_NS {
    void SRSLUseStack::Concat(const SRSLUseStack::Ptr& pOther) {
        for (auto&& name : pOther->variables) {
            variables.insert(name);
        }

        for (auto&& [name, function] : pOther->functions) {
            if (functions.count(name) == 1) {
                continue;
            }

            functions[name] = function;
        }
    }

    std::string SRSLUseStack::ToString(int32_t deep) const {
        std::string str;

        for (auto&& name : variables) {
            str += std::string(SR_MAX(0, deep * 4), ' ') + "var is \"" + name + "\"\n";
        }

        for (auto&& [name, function] : functions) {
            if (function) {
                str += std::string(SR_MAX(0, deep * 4), ' ') + "call \"" + name + "\" function:\n" + function->ToString(deep + 1);
            }
            else {
                str += std::string(SR_MAX(0, deep * 4), ' ') + "call \"" + name + "\" function\n";
            }
        }

        return str;
    }

    /// ----------------------------------------------------------------------------------------------------------------

    SRSLUseStack::Ptr SRSLRefAnalyzer::Analyze(const SRSLAnalyzedTree::Ptr& pAnalyzedTree) {
        SR_GLOBAL_LOCK
        m_analyzedTree = pAnalyzedTree;
        std::list<std::string> stack;
        return AnalyzeTree(stack, pAnalyzedTree->pLexicalTree);
    }

    SRSLUseStack::Ptr SRSLRefAnalyzer::AnalyzeTree(std::list<std::string>& stack, SRSLLexicalTree* pTree) {
        auto&& pUseStack = SRSLUseStack::Ptr(new SRSLUseStack());

        for (auto&& pUnit : pTree->lexicalTree) {
            /// Выражения в декораторах не учитываем, так как они не могут использовать переменные
            /// Однако стоит на будущее подумать использование в них макросов
            if (auto&& pVariable = dynamic_cast<SRSLVariable*>(pUnit); pVariable && pVariable->pExpr) {
                AnalyzeExpression(pUseStack, stack, pVariable->pExpr);
            }
            else if (auto&& pSubTree = dynamic_cast<SRSLLexicalTree*>(pUnit)) {
                pUseStack->Concat(AnalyzeTree(stack, pSubTree));
            }
            else if (auto&& pIfStatement = dynamic_cast<SRSLIfStatement*>(pUnit)) {
                AnalyzeIfStatement(pUseStack, stack, pIfStatement);
            }
            else if (auto&& pExpr = dynamic_cast<SRSLExpr*>(pUnit)) {
                AnalyzeExpression(pUseStack, stack, pExpr);
            }
        }

        return pUseStack;
    }

    void SRSLRefAnalyzer::AnalyzeExpression(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLExpr* pExpr) {
        if (pExpr->token == "=") {
            if (pExpr->args[0]->isArray) {
                AnalyzeArrayExpression(pUseStack, stack, pExpr->args[0]);
            }
            else {
                SRAssert(!pExpr->args[0]->token.empty());
                pUseStack->variables.insert(pExpr->args[0]->token);
            }
            return AnalyzeExpression(pUseStack, stack, pExpr->args[1]);
        }

        if (pExpr->isArray) {
            AnalyzeArrayExpression(pUseStack, stack, pExpr);
            return;
        }

        if (pExpr->isCall) {
            /// проверяем наличие рекурсии
            for (auto&& stackName : stack) {
                if (stackName == pExpr->token) {
                    pUseStack->functions[pExpr->token] = nullptr;
                    goto skipRecursion;
                }
            }

            if (auto&& pFunction = FindFunction(pExpr->token)) {
                stack.emplace_back(pExpr->token);
                pUseStack->functions[pExpr->token] = AnalyzeTree(stack, pFunction->pLexicalTree);
                stack.pop_back();
            }
            else {
                pUseStack->functions[pExpr->token] = nullptr;
            }

        skipRecursion:
            for (auto&& pSubExpr : pExpr->args) {
                AnalyzeExpression(pUseStack, stack, pSubExpr);
            }

            return;
        }

        if (IsIdentifier(pExpr->token) && !pExpr->token.empty()) {
            pUseStack->variables.insert(pExpr->token);
        }

        for (auto&& pSubExpr : pExpr->args) {
            AnalyzeExpression(pUseStack, stack, pSubExpr);
        }
    }

    void SRSLRefAnalyzer::AnalyzeIfStatement(SRSLUseStack::Ptr& pUseStack, std::list<std::string>& stack, SRSLIfStatement* pIfStatement) {
        if (pIfStatement->pExpr) {
            AnalyzeExpression(pUseStack, stack, pIfStatement->pExpr);
        }

        if (pIfStatement->pLexicalTree) {
            pUseStack->Concat(AnalyzeTree(stack, pIfStatement->pLexicalTree));
        }

        if (pIfStatement->pElseStatement) {
            AnalyzeIfStatement(pUseStack, stack, pIfStatement->pElseStatement);
        }
    }

    SRSLFunction *SRSLRefAnalyzer::FindFunction(const std::string &name) const {
        return FindFunction(m_analyzedTree->pLexicalTree, name);
    }

    SRSLFunction *SRSLRefAnalyzer::FindFunction(SRSLLexicalTree* pTree, const std::string &name) const {
        for (auto&& pUnit : m_analyzedTree->pLexicalTree->lexicalTree) {
            if (auto&& pFunction = dynamic_cast<SRSLFunction*>(pUnit)) {
                if (pFunction->pName->token == name) {
                    return pFunction;
                }
            }
            else if (auto&& pSubTree = dynamic_cast<SRSLLexicalTree*>(pUnit)) {
                if (auto&& pFoundedFunction = FindFunction(pSubTree, name)) {
                    return pFoundedFunction;
                }
            }
        }

        return nullptr;
    }

    void SRSLRefAnalyzer::AnalyzeArrayExpression(SRSLUseStack::Ptr& pUseStack, std::list<std::string> &stack, SRSLExpr* pExpr) {
        AnalyzeExpression(pUseStack, stack, pExpr->args[0]);
        AnalyzeExpression(pUseStack, stack, pExpr->args[1]);
    }
}
