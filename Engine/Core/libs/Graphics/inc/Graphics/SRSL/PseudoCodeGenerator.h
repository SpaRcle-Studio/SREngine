//
// Created by Monika on 30.01.2023.
//

#ifndef SRENGINE_PSEUDOCODEGENERATOR_H
#define SRENGINE_PSEUDOCODEGENERATOR_H

#include <Graphics/SRSL/ICodeGenerator.h>

namespace SR_SRSL_NS {
    class SRSLPseudoCodeGenerator : public ISRSLCodeGenerator, public SR_UTILS_NS::Singleton<SRSLPseudoCodeGenerator> {
        friend class SR_UTILS_NS::Singleton<SRSLPseudoCodeGenerator>;
    private:
        SRSLPseudoCodeGenerator() = default;
        ~SRSLPseudoCodeGenerator() override = default;

    public:
        SR_NODISCARD SRSLCodeGenRes GenerateStages(const SRSLShader* pShader) override;

    private:
        SR_NODISCARD std::string GenerateLexicalTree(SRSLLexicalTree* pLexicalTree, int32_t deep) const;
        SR_NODISCARD std::string GenerateVariable(SRSLVariable* pVariable, int32_t deep) const;
        SR_NODISCARD std::string GenerateFunction(SRSLFunction* pFunction, int32_t deep) const;

        SR_NODISCARD std::string GenerateDecorators(SRSLDecorators* pDecorators, int32_t deep) const;

        SR_NODISCARD std::string GenerateType(SRSLExpr* pExpr, int32_t deep) const;
        SR_NODISCARD std::string GenerateName(SRSLExpr* pExpr, int32_t deep) const;

        SR_NODISCARD std::string GenerateExpression(SRSLExpr* pExpr, int32_t deep) const;

        SR_NODISCARD std::string GenerateTab(int32_t deep) const;

    };
}

#endif //SRENGINE_PSEUDOCODEGENERATOR_H
