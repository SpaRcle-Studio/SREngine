//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_SHADER_H
#define SRENGINE_SRSL_SHADER_H

#include <Graphics/SRSL/RefAnalyzer.h>
#include <Graphics/SRSL/ShaderType.h>
#include <Graphics/Types/Vertices.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_SRSL_NS {
    SR_ENUM_NS_CLASS_T(ShaderLanguage, uint8_t,
        PseudoCode, GLSL, HLSL, Metal
    );

    struct SRSLSampler {
        std::string type;
        bool isPublic = false;
    };
    typedef std::map<std::string, SRSLSampler> SRSLSamplers;

    struct SRSLUniformBlock {
        struct Field {
            std::string type;
            std::string name;
            uint64_t size = 0;
            bool isPublic = false;
        };

        std::vector<Field> fields;
    };

    /** Это не шейдер в привычном понимании, это набор всех данных для генерирования любого
     * шейдерного кода и для последующей его экспортации. */
    class SRSLShader : public SR_UTILS_NS::NonCopyable {
        using Ptr = std::shared_ptr<SRSLShader>;
        using Super = SR_UTILS_NS::NonCopyable;
        using UniformBlocks = std::map<std::string, SRSLUniformBlock>;
    private:
        explicit SRSLShader(SR_UTILS_NS::Path path, SRSLAnalyzedTree::Ptr&& pAnalyzedTree);

    public:
        SR_NODISCARD static SRSLShader::Ptr Load(SR_UTILS_NS::Path path);

    public:
        SR_NODISCARD bool IsCacheActual() const;
        SR_NODISCARD Vertices::VertexType GetVertexType() const;
        SR_NODISCARD SR_SRSL_NS::ShaderType GetType() const;
        SR_NODISCARD std::string ToString(ShaderLanguage shaderLanguage) const;
        SR_NODISCARD const SRSLAnalyzedTree::Ptr GetAnalyzedTree() const;

    private:
        bool Prepare();

    private:
        SR_UTILS_NS::Path m_path;

        ShaderType m_type = ShaderType::Unknown;
        SRShaderCreateInfo m_createInfo;
        SRSLAnalyzedTree::Ptr m_analyzedTree;
        SRSLUseStack::Ptr m_useStack;
        UniformBlocks m_uniformBlocks;
        SRSLSamplers m_samplers;

    };
}

#endif //SRENGINE_SRSL_SHADER_H
