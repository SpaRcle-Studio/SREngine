

# File PseudoCodeGenerator.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**PseudoCodeGenerator.h**](PseudoCodeGenerator_8h.md)

[Go to the documentation of this file](PseudoCodeGenerator_8h.md)


```C++
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
```


