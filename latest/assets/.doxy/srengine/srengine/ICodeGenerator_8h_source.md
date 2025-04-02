

# File ICodeGenerator.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**ICodeGenerator.h**](ICodeGenerator_8h.md)

[Go to the documentation of this file](ICodeGenerator_8h.md)


```C++
//
// Created by Monika on 30.01.2023.
//

#ifndef SR_ENGINE_ICODEGENERATOR_H
#define SR_ENGINE_ICODEGENERATOR_H

#include <Graphics/SRSL/LexicalTree.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_SRSL_NS {
    class SRSLShader;

    class ISRSLCodeGenerator {
    public:
        using SRSLCodeGenRes = std::pair<SRSLResult, std::map<ShaderStage, std::string>>;

    protected:
        ISRSLCodeGenerator() = default;
        virtual ~ISRSLCodeGenerator() = default;

    protected:
        SR_NODISCARD virtual SRSLCodeGenRes GenerateStages(const SRSLShader* pShader) = 0;

    protected:
        void Clear();

    protected:
        SRSLResult m_result = SRSLResult();

    };
}

#endif //SR_ENGINE_ICODEGENERATOR_H
```


