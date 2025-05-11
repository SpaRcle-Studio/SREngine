

# File ICodeGenerator.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**ICodeGenerator.h**](ICodeGenerator_8h.md)

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


