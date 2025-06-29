

# File GLSLCodeGenerator.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**GLSLCodeGenerator.h**](GLSLCodeGenerator_8h.md)

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

        void GenerateSSBOBlock(std::string& code, SR_UTILS_NS::StringAtom name, const SRSLUniformBlock& uniformBlock, const SRSLUseStack::Ptr& pFunction) const;

    private:
        const SRSLShader* m_shader = nullptr;

    };
}

#endif //SR_ENGINE_GLSLCODEGENERATOR_H
```


