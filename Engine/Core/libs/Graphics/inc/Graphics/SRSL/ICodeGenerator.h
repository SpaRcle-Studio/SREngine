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
