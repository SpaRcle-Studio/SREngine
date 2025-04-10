

# File GLSLCodeGenerator.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**GLSLCodeGenerator.h**](GLSLCodeGenerator_8h.md)

[Go to the documentation of this file](GLSLCodeGenerator_8h.md)


```C++
//
// Created by Monika on 30.01.2023.
//

#ifndef SR_ENGINE_GLSLCODEGENERATOR_H
#define SR_ENGINE_GLSLCODEGENERATOR_H

#include <Graphics/SRSL/ICodeGenerator.h>
#include <Graphics/SRSL/ShaderType.h>

namespace SR_SRSL_NS {
    class GLSLCodeGenerator : public ISRSLCodeGenerator, public SR_UTILS_NS::Singleton<GLSLCodeGenerator> {
        SR_REGISTER_SINGLETON(GLSLCodeGenerator)
    private:
        GLSLCodeGenerator() = default;
        ~GLSLCodeGenerator() override = default;

    public:
        SR_NODISCARD SRSLCodeGenRes GenerateStages(const SRSLShader* pShader) override;

    private:
        SR_NODISCARD std::string GenerateStage(ShaderStage stage, const std::string& preCode = std::string());

        SR_NODISCARD std::optional<std::string> GenerateVertexStage();
        SR_NODISCARD std::optional<std::string> GenerateFragmentStage();
        SR_NODISCARD std::optional<std::string> GenerateComputeStage();

        SR_NODISCARD std::optional<std::string> GenerateRayGenStage();
        SR_NODISCARD std::optional<std::string> GenerateRayIntersectionStage();
        SR_NODISCARD std::optional<std::string> GenerateRayHitClosestStage();
        SR_NODISCARD std::optional<std::string> GenerateRayHitAnyStage();
        SR_NODISCARD std::optional<std::string> GenerateRayMissPrimaryStage();
        SR_NODISCARD std::optional<std::string> GenerateRayMissSecondaryStage();

        SR_NODISCARD std::string ReplaceToken(const std::string& token) const;
        SR_NODISCARD std::string GetVersion(ShaderStage stage) const;
        SR_NODISCARD std::string GenerateInputLocations(ShaderStage stage) const;
        SR_NODISCARD std::string GenerateOutputLocations(ShaderStage stage) const;
        SR_NODISCARD std::string GenerateUniforms(ShaderStage stage) const;

        SR_NODISCARD std::string GenerateLexicalTree(SRSLLexicalTree* pLexicalTree, int32_t deep) const;
        SR_NODISCARD std::string GenerateLexicalTree(SRSLLexicalTree* pLexicalTree, int32_t deep, const std::string& preCode, const std::string& postCode) const;

        SR_NODISCARD std::string GenerateFunction(SRSLFunction* pFunction, int32_t deep) const;
        SR_NODISCARD std::string GenerateFunction(SRSLFunction* pFunction, int32_t deep, const std::string& preCode, const std::string& postCode) const;

        SR_NODISCARD std::string GenerateStructure(SRSLStructureStatement* pStructure, int32_t deep) const;

        SR_NODISCARD std::string GenerateType(SRSLExpr* pExpr, int32_t deep) const;
        SR_NODISCARD std::string GenerateName(SRSLExpr* pExpr, int32_t deep) const;

        SR_NODISCARD std::string GenerateForStatement(SRSLForStatement* pForStatement, int32_t deep) const;
        SR_NODISCARD std::string GenerateIfStatement(SRSLIfStatement* pIfStatement, int32_t deep) const;
        SR_NODISCARD std::string GenerateExpression(SRSLExpr* pExpr, int32_t deep) const;
        SR_NODISCARD std::string GenerateVariable(SRSLVariable* pVariable, int32_t deep) const;

        SR_NODISCARD std::string GenerateTab(int32_t deep) const;

        SR_NODISCARD std::string VertexAttributeToString(Vertices::Attribute attribute) const;

    private:
        const SRSLShader* m_shader = nullptr;

    };
}

#endif //SR_ENGINE_GLSLCODEGENERATOR_H
```


