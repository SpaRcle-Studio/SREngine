//
// Created by Monika on 30.01.2023.
//

#include <Graphics/SRSL/GLSLCodeGenerator.h>
#include <Graphics/SRSL/Shader.h>

namespace SR_SRSL_NS {
    ISRSLCodeGenerator::SRSLCodeGenRes GLSLCodeGenerator::GenerateStages(const SRSLShader* pShader) {
        SR_GLOBAL_LOCK

        Clear();

        m_shader = pShader;

        ISRSLCodeGenerator::SRSLCodeGenRes codeGenRes;

        auto&& [result, stages] = codeGenRes;

        if (!pShader->GetAnalyzedTree()) {
            result = SRSLResult(SRSLReturnCode::InvalidLexicalTree);
            return codeGenRes;
        }

        if (auto&& vertexCode = GenerateVertexStage()) {
            stages[ShaderStage::Vertex] = vertexCode.value();
        }

        if (auto&& fragmentCode = GenerateFragmentStage()) {
            stages[ShaderStage::Fragment] = fragmentCode.value();
        }

        result = SR_UTILS_NS::Exchange(m_result, { });

        return codeGenRes;
    }

    std::optional<std::string> GLSLCodeGenerator::GenerateVertexStage() {
        auto&& pStageFunction = m_shader->GetAnalyzedTree()->pLexicalTree->FindFunction("vertex");
        if (!pStageFunction) {
            return std::optional<std::string>();
        }

        std::string code;

        code += "// [WARNING: THIS FILE WAS CREATED BY SRSL CODE GENERATION]\n\n";
        code += "#version " + GetVersion(ShaderStage::Vertex) + "\n\n";

        if (auto&& vertexLocations = GenerateVertexLocations(); !vertexLocations.empty()) {
            code += vertexLocations + "\n";
        }

        code += GenerateUniforms(ShaderStage::Vertex) + "\n";

        if (auto&& pFunctionCallStack = m_shader->GetUseStack()->FindFunction(pStageFunction->pName->token)) {
            for (auto &&pUnit : m_shader->GetAnalyzedTree()->pLexicalTree->lexicalTree) {
                auto&& pFunction = dynamic_cast<SRSLFunction*>(pUnit);

                if (!pFunction) {
                    continue;
                }

                if (!pFunctionCallStack->IsFunctionUsed(pFunction->pName->token)) {
                    continue;
                }

                code += GenerateFunction(pFunction, 0) + "\n";
            }
        }

        code += GenerateFunction(pStageFunction, 0);

        return code;
    }

    std::optional<std::string> GLSLCodeGenerator::GenerateFragmentStage() {
        auto&& pFunction = m_shader->GetAnalyzedTree()->pLexicalTree->FindFunction("fragment");
        if (!pFunction) {
            return std::optional<std::string>();
        }

        return std::optional<std::string>();
    }

    std::string GLSLCodeGenerator::GetVersion(ShaderStage stage) const {
        return "450";
    }

    std::string GLSLCodeGenerator::GenerateVertexLocations() const {
        std::string code;

        auto&& vertexInfo = Vertices::GetVertexInfo(m_shader->GetVertexType());

        uint32_t location = 0;
        for (auto&& vertexAttribute : vertexInfo.m_names) {
            std::string type;

            switch (vertexInfo.m_attributes[location].first) {
                case Vertices::Attribute::FLOAT_R32G32B32A32: type = "vec4"; break;
                case Vertices::Attribute::FLOAT_R32G32B32: type = "vec3"; break;
                case Vertices::Attribute::FLOAT_R32G32: type = "vec2"; break;
                case Vertices::Attribute::INT_R32G32B32A32: type = "ivec4"; break;
                case Vertices::Attribute::INT_R32G32B32: type = "ivec3"; break;
                case Vertices::Attribute::INT_R32G32: type = "ivec2"; break;
                case Vertices::Attribute::Unknown:
                default:
                    SRHalt0();
                    return std::string();
            }

            code += SR_UTILS_NS::Format("layout (location = %i) in %s %s_INPUT;\n", location, type.c_str(), vertexAttribute.c_str());

            ++location;
        }

        return code;
    }

    std::string GLSLCodeGenerator::GenerateVariable(SRSLVariable* pVariable, int32_t deep) const {
        std::string code = GenerateTab(deep);

        if (pVariable->pType) {
            code += GenerateType(pVariable->pType, 0) + " ";
        }

        if (pVariable->pName) {
            code += GenerateName(pVariable->pName, 0);
        }

        if (pVariable->pExpr) {
            code += " = " + GenerateExpression(pVariable->pExpr, 0);
        }

        return code;
    }

    std::string GLSLCodeGenerator::GenerateFunction(SRSLFunction* pFunction, int32_t deep) const {
        std::string code;

        code += GenerateTab(deep);

        if (pFunction->pType) {
            code += GenerateType(pFunction->pType, 0) + " ";
        }

        if (pFunction->pName) {
            code += GenerateType(pFunction->pName, 0);
        }

        code += "(";

        for (uint32_t i = 0; i < pFunction-> args.size(); ++i) {
            code += GenerateVariable(pFunction->args[i], 0);

            if (i + 1 < pFunction->args.size()) {
                code += ", ";
            }
        }

        code += ") ";

        if (pFunction->pLexicalTree) {
            code += GenerateLexicalTree(pFunction->pLexicalTree, deep + 1);
        }

        return code;
    }

    std::string GLSLCodeGenerator::GenerateType(SRSLExpr* pExpr, int32_t deep) const {
        return GenerateExpression(pExpr, deep);
    }

    std::string GLSLCodeGenerator::GenerateName(SRSLExpr* pExpr, int32_t deep) const {
        return GenerateExpression(pExpr, deep);
    }

    std::string GLSLCodeGenerator::GenerateExpression(SRSLExpr* pExpr, int32_t deep) const {
        if ((pExpr->token == "++" || pExpr->token == "--") && !pExpr->args.empty()) {
            SRHalt0();
            return std::string();
        }

        std::string code = GenerateTab(deep);

        if (pExpr->isCall) {
            code += pExpr->token + "(";

            for (uint32_t i = 0; i < pExpr->args.size(); ++i) {
                code += GenerateExpression(pExpr->args[i], 0);

                if (i + 1 < pExpr->args.size()) {
                    code += ", ";
                }
            }

            code += ")";
        }
        else if (pExpr->isArray) {
            code += GenerateExpression(pExpr->args[0], 0) + "[" + GenerateExpression(pExpr->args[1], 0) + "]";
        }
        else if (pExpr->args.empty()) {
            code += pExpr->token;
        }
        else if (pExpr->args.size() == 1) {
            code += "(" + pExpr->token + GenerateExpression(pExpr->args[0], 0) + ")";
        }
        else if (pExpr->args.size() == 2 && (pExpr->token == "=" || pExpr->token == ".")) {
            code += GenerateExpression(pExpr->args[0], 0) + pExpr->token + GenerateExpression(pExpr->args[1], 0);
        }
        else if (pExpr->args.size() == 2) {
            code += "(" + GenerateExpression(pExpr->args[0], 0) + pExpr->token + GenerateExpression(pExpr->args[1], 0) + ")";
        }

        return code;
    }

    std::string GLSLCodeGenerator::GenerateLexicalTree(SRSLLexicalTree* pLexicalTree, int32_t deep) const {
        std::string code;

        if (deep > 0) {
            code += "{\n";
        }

        for (uint32_t i = 0; i < pLexicalTree->lexicalTree.size(); ++i) {
            auto&& pUnit = pLexicalTree->lexicalTree[i];

            if (auto&& pVariable = dynamic_cast<SRSLVariable*>(pUnit)) {
                code += GenerateVariable(pVariable, deep + 1) + ";";
            }
            else if (auto&& pFunction = dynamic_cast<SRSLFunction*>(pUnit)) {
                code += GenerateFunction(pFunction, deep + 1);
            }
            else if (auto&& pTree = dynamic_cast<SRSLLexicalTree*>(pUnit)) {
                code += GenerateLexicalTree(pTree, deep + 1);
            }
            else if (auto&& pExpression = dynamic_cast<SRSLExpr*>(pUnit)) {
                code += GenerateExpression(pExpression, deep + 1) + ";";
            }

            if (i + 1 < pLexicalTree->lexicalTree.size()) {
                code += "\n";
            }
        }

        if (deep > 0) {
            code += "\n" + GenerateTab(deep - 1);
            code += "}";
        }

        return code;
    }

    std::string GLSLCodeGenerator::GenerateTab(int32_t deep) const {
        if (deep <= 0) {
            return std::string();
        }

        return std::string(deep * 3, ' ');
    }

    std::string GLSLCodeGenerator::GenerateUniforms(ShaderStage stage) const {
        std::string code;

        uint32_t binding = 0;

        for (auto&& [name, uniformBlock] : m_shader->GetUniformBlocks()) {
            code += SR_UTILS_NS::Format("layout (std140, binding = %i) uniform %s {\n", binding, name.c_str());

            for (auto&& field : uniformBlock.fields) {
                code += SR_UTILS_NS::Format("\t%s %s; // %s \n", field.type.c_str(), field.name.c_str(), field.isPublic ? "public" : "private");
            }

            code += "};\n";

            ++binding;
        }

        if (!m_shader->GetSamplers().empty() && !m_shader->GetUniformBlocks().empty()) {
            code += "\n";
        }

        for (auto&& [name, sampler] : m_shader->GetSamplers()) {
            code += SR_UTILS_NS::Format("layout (binding = %i) uniform %s %s; // %s\n", binding, sampler.type.c_str(), name.c_str(), sampler.isPublic ? "public" : "private");
            ++binding;
        }

        return code;
    }
}