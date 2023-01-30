//
// Created by Monika on 30.01.2023.
//

#include <Graphics/SRSL/PseudoCodeGenerator.h>

namespace SR_SRSL_NS {
    std::set<SRSLShaderStage> SRSLPseudoCodeGenerator::GenerateStages() {
        std::set<SRSLShaderStage> stages;

        if (!m_analyzedTree->pLexicalTree) {
            return stages;
        }

        SRSLShaderStage stage;
        stage.stage = ShaderStage::Unknown;
        stage.code = GenerateLexicalTree(m_analyzedTree->pLexicalTree, 0);

        stages.insert(std::move(stage));

        return stages;
    }

    std::string SRSLPseudoCodeGenerator::GenerateVariable(SRSLVariable* pVariable, int32_t deep) const {
        std::string code = GenerateTab(deep);

        if (pVariable->pDecorators) {
            code += GenerateDecorators(pVariable->pDecorators, 0) + " ";
        }

        if (pVariable->pType) {
            code += GenerateType(pVariable->pType, 0) + " ";
        }

        if (pVariable->pName) {
            code += GenerateName(pVariable->pName, 0);
        }

        if (pVariable->pExpr) {
            code += " = " + GenerateExpression(pVariable->pExpr, 0);
        }

        return code;
    }

    std::string SRSLPseudoCodeGenerator::GenerateFunction(SRSLFunction* pFunction, int32_t deep) const {
        std::string code = GenerateTab(deep);

        if (pFunction->pDecorators) {
            code += GenerateDecorators(pFunction->pDecorators, 0) + " ";
        }

        if (pFunction->pType) {
            code += GenerateType(pFunction->pType, 0) + " ";
        }

        if (pFunction->pName) {
            code += GenerateType(pFunction->pName, 0);
        }

        code += "(";

        for (uint32_t i = 0; i <pFunction-> args.size(); ++i) {
            code += GenerateVariable(pFunction->args[i], 0);

            if (i + 1 < pFunction->args.size()) {
                code += ", ";
            }
        }

        code += ") ";

        if (pFunction->pLexicalTree) {
            code += GenerateLexicalTree(pFunction->pLexicalTree, deep + 1);
        }

        return code;
    }

    std::string SRSLPseudoCodeGenerator::GenerateDecorators(SRSLDecorators* pDecorators, int32_t deep) const {
        std::string code = "[";

        for (uint32_t i = 0; i < pDecorators->decorators.size(); ++i) {
            code += "[" + pDecorators->decorators[i].name;

            if (!pDecorators->decorators[i].args.empty()) {
                code += "(";

                for (uint32_t j = 0; j < pDecorators->decorators[i].args.size(); ++j) {
                    code += GenerateExpression(pDecorators->decorators[i].args[j], 0);
                    if (j + 1 < pDecorators->decorators[i].args.size()) {
                        code += ", ";
                    }
                }

                code += ")";
            }

            code += "]";

            if (i + 1 < pDecorators->decorators.size()) {
                code += ", ";
            }
        }

        return code + "]";
    }

    std::string SRSLPseudoCodeGenerator::GenerateType(SRSLExpr* pExpr, int32_t deep) const {
        return GenerateExpression(pExpr, deep);
    }

    std::string SRSLPseudoCodeGenerator::GenerateName(SRSLExpr* pExpr, int32_t deep) const {
        return GenerateExpression(pExpr, deep);
    }

    std::string SRSLPseudoCodeGenerator::GenerateExpression(SRSLExpr* pExpr, int32_t deep) const {
        if ((pExpr->token == "++" || pExpr->token == "--") && !pExpr->args.empty()) {
            SRHalt0();
            return std::string();
        }

        std::string code = GenerateTab(deep);

        if (pExpr->isArray) {
            code += GenerateExpression(pExpr->args[0], 0) + "[" + GenerateExpression(pExpr->args[1], 0) + "]";
        }
        else if (pExpr->args.empty()) {
            code += pExpr->token;
        }
        else if (pExpr->args.size() == 1) {
            code += "(" + pExpr->token + GenerateExpression(pExpr->args[0], 0) + ")";
        }
        else if (pExpr->args.size() == 2) {
            code += "(" + GenerateExpression(pExpr->args[0], 0) + pExpr->token + GenerateExpression(pExpr->args[1], 0) + ")";
        }

        return code;
    }

    std::string SRSLPseudoCodeGenerator::GenerateLexicalTree(SRSLLexicalTree* pLexicalTree, int32_t deep) const {
        std::string code;

        if (deep > 0) {
            code += "{\n";
        }

        for (uint32_t i = 0; i < pLexicalTree->lexicalTree.size(); ++i) {
            auto&& pUnit = pLexicalTree->lexicalTree[i];

            if (auto&& pVariable = dynamic_cast<SRSLVariable*>(pUnit)) {
                code += GenerateVariable(pVariable, deep + 1) + ";";
            }
            else if (auto&& pFunction = dynamic_cast<SRSLFunction*>(pUnit)) {
                code += GenerateFunction(pFunction, deep + 1);
            }
            else if (auto&& pTree = dynamic_cast<SRSLLexicalTree*>(pUnit)) {
                code += GenerateLexicalTree(pTree, deep + 1);
            }
            else if (auto&& pExpression = dynamic_cast<SRSLExpr*>(pUnit)) {
                code += GenerateExpression(pExpression, deep + 1) + ";";
            }

            if (i + 1 < pLexicalTree->lexicalTree.size()) {
                code += "\n";
            }
        }

        if (deep > 0) {
            code += "\n" + GenerateTab(deep - 1);
            code += "}";
        }

        return code;
    }

    std::string SRSLPseudoCodeGenerator::GenerateTab(int32_t deep) const {
        if (deep <= 0) {
            return std::string();
        }
        return std::string(deep * 3, ' ');
    }
}
