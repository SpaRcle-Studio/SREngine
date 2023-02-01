//
// Created by Monika on 22.01.2023.
//

#ifndef SRENGINE_SRSL_SHADER_H
#define SRENGINE_SRSL_SHADER_H

#include <Graphics/SRSL/LexicalTree.h>

namespace SR_SRSL_NS {
    SR_ENUM_NS_CLASS_T(ShaderLanguage, uint8_t,
        PseudoCode, GLSL, HLSL, Metal
    );

    /** Это не шейдер в привычном понимании, это набор всех данных для генерирования любого
     * шейдерного кода и для последующей его экспортации. */
    class SRSLShader : public SR_UTILS_NS::NonCopyable {
        using Ptr = std::shared_ptr<SRSLShader>;
        using Super = SR_UTILS_NS::NonCopyable;
    private:
        explicit SRSLShader(SR_UTILS_NS::Path path, SRSLAnalyzedTree::Ptr&& pAnalyzedTree);

    public:
        SR_NODISCARD static SRSLShader::Ptr Load(SR_UTILS_NS::Path path);

    public:
        SR_NODISCARD bool IsCacheActual() const;
        SR_NODISCARD std::string ToString(ShaderLanguage shaderLanguage) const;
        SR_NODISCARD const SRSLAnalyzedTree::Ptr GetAnalyzedTree() const;

    private:
        SR_UTILS_NS::Path m_path;
        SRSLAnalyzedTree::Ptr m_analyzedTree;

    };
}

#endif //SRENGINE_SRSL_SHADER_H
