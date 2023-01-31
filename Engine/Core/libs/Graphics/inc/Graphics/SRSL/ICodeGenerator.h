//
// Created by Monika on 30.01.2023.
//

#ifndef SRENGINE_ICODEGENERATOR_H
#define SRENGINE_ICODEGENERATOR_H

#include <Graphics/SRSL/LexicalTree.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_SRSL_NS {
    SR_ENUM_NS_CLASS_T(ShaderLanguage, uint8_t,
            GLSL, HLSL, Metal
    );

    struct SRSLShaderStage {
        bool operator<(const SRSLShaderStage& other) const {
            return static_cast<int32_t>(stage) < static_cast<int32_t>(other.stage);
        }

        ShaderStage stage = ShaderStage::Unknown;
        std::string code;
    };

    class ISRSLCodeGenerator {
    protected:
        ISRSLCodeGenerator() = default;
        virtual ~ISRSLCodeGenerator() = default;

    public:
        SR_NODISCARD std::pair<std::string, SRSLResult> ToString(SRSLAnalyzedTree::Ptr&& analyzedTree);

    protected:
        void Clear();

        SR_NODISCARD virtual std::set<SRSLShaderStage> GenerateStages() = 0;

    protected:
        SRSLResult m_result = SRSLResult();
        SRSLAnalyzedTree::Ptr m_analyzedTree;

    };
}

#endif //SRENGINE_ICODEGENERATOR_H
