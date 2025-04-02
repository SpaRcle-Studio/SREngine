

# File PseudoCodeGenerator.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**PseudoCodeGenerator.h**](PseudoCodeGenerator_8h.md)

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


