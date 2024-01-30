//
// Created by Monika on 30.01.2023.
//

#ifndef SR_ENGINE_PSEUDOCODEGENERATOR_H
#define SR_ENGINE_PSEUDOCODEGENERATOR_H

#include <Graphics/SRSL/ICodeGenerator.h>

namespace SR_SRSL_NS {
    class SRSLPseudoCodeGenerator : public ISRSLCodeGenerator, public SR_UTILS_NS::Singleton<SRSLPseudoCodeGenerator> {
        SR_REGISTER_SINGLETON(SRSLPseudoCodeGenerator)
    protected:
        SRSLPseudoCodeGenerator() = default;
        ~SRSLPseudoCodeGenerator() override = default;

    public:
        SR_NODISCARD SRSLCodeGenRes GenerateStages(const SRSLShader* pShader) override;

    protected:
        SR_NODISCARD virtual std::string GenerateLexicalTree(SRSLLexicalTree* pLexicalTree, int32_t deep) const;
        SR_NODISCARD virtual std::string GenerateVariable(SRSLVariable* pVariable, int32_t deep) const;
        SR_NODISCARD virtual std::string GenerateFunction(SRSLFunction* pFunction, int32_t deep) const;

        SR_NODISCARD virtual std::string GenerateDecorators(SRSLDecorators* pDecorators, int32_t deep) const;

        SR_NODISCARD virtual std::string GenerateType(SRSLExpr* pExpr, int32_t deep) const;
        SR_NODISCARD virtual std::string GenerateName(SRSLExpr* pExpr, int32_t deep) const;

        SR_NODISCARD virtual std::string GenerateExpression(SRSLExpr* pExpr, int32_t deep) const;

        SR_NODISCARD virtual std::string GenerateTab(int32_t deep) const;

    };
}

#endif //SR_ENGINE_PSEUDOCODEGENERATOR_H
