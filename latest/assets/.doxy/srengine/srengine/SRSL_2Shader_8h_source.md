

# File Shader.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**Shader.h**](SRSL_2Shader_8h.md)

[Go to the documentation of this file](SRSL_2Shader_8h.md)


```C++
//
// Created by Monika on 22.01.2023.
//

#ifndef SR_ENGINE_SRSL_SHADER_H
#define SR_ENGINE_SRSL_SHADER_H

#include <Graphics/SRSL/RefAnalyzer.h>
#include <Graphics/SRSL/ICodeGenerator.h>
#include <Graphics/SRSL/ShaderType.h>
#include <Graphics/Types/Vertices.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_SRSL_NS {
    SR_ENUM_NS_CLASS_T(ShaderLanguage, uint8_t,
        PseudoCode, GLSL, HLSL, Metal
    );

    struct SRSLSampler {
        SR_UTILS_NS::StringAtom type;
        bool isPublic = false;
        uint64_t binding = 0;
        int32_t attachment = -1;
        std::set<ShaderStage> stages;
        SR_UTILS_NS::StringAtom defaultValue;
    };
    typedef std::map<SR_UTILS_NS::StringAtom, SRSLSampler> SRSLSamplers;

    struct SRSLUniformBlock {
        struct Field {
            SR_UTILS_NS::StringAtom type;
            SR_UTILS_NS::StringAtom name;
            uint64_t size = 0;
            uint64_t alignedSize = 0;
            bool isPublic = false;
            std::optional<ShaderPropertyVariant> defaultValue;
        };

        void Align(const SRSLAnalyzedTree::Ptr& pAnalyzedTree);

        std::optional<bool> isReadOnly; 
        bool isVolatile = false;
        bool isCoherent = false;
        bool isRestrict = false;

        uint64_t size = 0;
        uint64_t binding = 0;

        std::vector<Field> fields;
        std::set<ShaderStage> stages;
    };

    class SRSLShader : public SR_UTILS_NS::NonCopyable {
        using Ptr = std::shared_ptr<SRSLShader>;
        using Super = SR_UTILS_NS::NonCopyable;
        using UniformBlocks = std::map<SR_UTILS_NS::StringAtom, SRSLUniformBlock>;
        uint64_t VERSION = 1000;
    private:
        explicit SRSLShader(SR_UTILS_NS::Path path);

    public:
        SR_NODISCARD static SRSLShader::Ptr Load(SR_UTILS_NS::Path path);
        static void ClearShadersCache();

    public:
        SR_NODISCARD std::string ToString(ShaderLanguage shaderLanguage) const;
        SR_NODISCARD bool Export(ShaderLanguage shaderLanguage) const;

        SR_NODISCARD bool IsCacheActual() const;
        SR_NODISCARD bool IsCacheActual(ShaderLanguage shaderLanguage) const;

        SR_NODISCARD const SRSLUniformBlock* FindUniformBlock(const SR_UTILS_NS::StringAtom& name) const;
        SR_NODISCARD const SRSLUniformBlock::Field* FindField(const SR_UTILS_NS::StringAtom& name) const;
        SR_NODISCARD Vertices::VertexType GetVertexType() const;
        SR_NODISCARD SR_SRSL_NS::ShaderType GetType() const;
        SR_NODISCARD SR_UTILS_NS::Path GetPath() const { return m_path; }
        SR_NODISCARD const SRSLAnalyzedTree::Ptr GetAnalyzedTree() const;
        SR_NODISCARD const SRSLUseStack::Ptr GetUseStack() const;
        SR_NODISCARD const UniformBlocks& GetUniformBlocks() const { return m_uniformBlocks; }
        SR_NODISCARD const UniformBlocks& GetSSBOBlocks() const { return m_ssboBlocks; }
        SR_NODISCARD const SRSLUniformBlock& GetPushConstants() const { return m_pushConstants; }
        SR_NODISCARD const SRSLSamplers& GetSamplers() const { return m_samplers; }
        SR_NODISCARD const SRShaderCreateInfo& GetCreateInfo() const { return m_createInfo; }
        SR_NODISCARD const std::vector<std::pair<SR_UTILS_NS::StringAtom, SRSLVariable*>>& GetShared() const { return m_shared; }
        SR_NODISCARD const std::map<SR_UTILS_NS::StringAtom, SRSLVariable*>& GetConstants() const { return m_constants; }
        SR_NODISCARD const std::vector<SR_UTILS_NS::StringAtom>& GetIncludes() const { return m_includes; }

    private:
        SR_NODISCARD float_t EvalExpressionFloat(SRSLExpr* pExpression) const;
        SR_NODISCARD int32_t EvalExpressionInt(SRSLExpr* pExpression) const;
        SR_NODISCARD SR_MATH_NS::FVector2 EvalExpressionVec2(SRSLExpr* pExpression) const;
        SR_NODISCARD SR_MATH_NS::FVector3 EvalExpressionVec3(SRSLExpr* pExpression) const;
        SR_NODISCARD SR_MATH_NS::FVector4 EvalExpressionVec4(SRSLExpr* pExpression) const;
        SR_NODISCARD std::optional<ShaderPropertyVariant> EvalExpressionValue(SRSLExpr* pExpression, SRSLExpr* pType) const;

        SR_NODISCARD ISRSLCodeGenerator::SRSLCodeGenRes GenerateStages(ShaderLanguage shaderLanguage) const;

        SR_NODISCARD bool SaveCache() const;
        SR_NODISCARD uint64_t GetHash() const;

        bool Prepare();
        bool PrepareSettings();
        bool PrepareUniformBlocks();
        bool PrepareSamplers();
        bool PrepareStages();

    private:
        SR_UTILS_NS::Path m_path;

        std::vector<SR_UTILS_NS::StringAtom> m_includes;
        std::vector<std::pair<SR_UTILS_NS::StringAtom, SRSLVariable*>> m_shared;
        std::map<SR_UTILS_NS::StringAtom, SRSLVariable*> m_constants;
        ShaderType m_type = ShaderType::Unknown;
        SRShaderCreateInfo m_createInfo;
        SRSLAnalyzedTree::Ptr m_analyzedTree;
        SRSLUseStack::Ptr m_useStack;
        UniformBlocks m_ssboBlocks;
        UniformBlocks m_uniformBlocks;
        SRSLUniformBlock m_pushConstants;
        SRSLSamplers m_samplers;

    };
}

#endif //SR_ENGINE_SRSL_SHADER_H
```


