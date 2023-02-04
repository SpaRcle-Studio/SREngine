//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/Shader.h>
#include <Graphics/SRSL/Lexer.h>
#include <Graphics/SRSL/PseudoCodeGenerator.h>
#include <Graphics/SRSL/GLSLCodeGenerator.h>
#include <Graphics/SRSL/AssignExpander.h>

namespace SR_SRSL_NS {
    SRSLShader::SRSLShader(SR_UTILS_NS::Path path, SRSLAnalyzedTree::Ptr&& pAnalyzedTree)
        : Super()
        , m_path(std::move(path))
        , m_analyzedTree(SR_UTILS_NS::Exchange(pAnalyzedTree, nullptr))
    { }

    SRSLShader::Ptr SRSLShader::Load(SR_UTILS_NS::Path path) {
        auto&& lexems = SR_SRSL_NS::SRSLLexer::Instance().Parse(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path));

        if (lexems.empty()) {
            SR_ERROR("SRSLShader::Load() : failed to parse lexems!\n\tPath: " + path.ToString());
            return nullptr;
        }

        auto&& [expandedLexems, expandResult] = SR_SRSL_NS::SRSLAssignExpander::Instance().Expand(std::move(lexems));
        lexems = std::move(expandedLexems);

        auto&& [pAnalyzedTree, analyzeResult] = SR_SRSL_NS::SRSLLexicalAnalyzer::Instance().Analyze(std::move(lexems));

        if (!pAnalyzedTree || analyzeResult.code != SRSLReturnCode::Success) {
            SR_ERROR("SRSLShader::Load() : failed to analyze shader!\n\tPath: " + path.ToString()
                + "\n\tPosition: " + std::to_string(analyzeResult.position)
                + "\b\tReason: " + SR_UTILS_NS::EnumReflector::ToString(analyzeResult.code)
            );
            return nullptr;
        }

        auto&& pShader = SRSLShader::Ptr(new SRSLShader(std::move(path), std::move(pAnalyzedTree)));

        if (!pShader->Prepare()) {
            SR_ERROR("SRSLShader::Load() : failed to prepare shader!\n\tPath: " + path.ToString());
            return nullptr;
        }

        return pShader;
    }

    bool SRSLShader::IsCacheActual() const {
        return false;
    }

    std::string SRSLShader::ToString(ShaderLanguage shaderLanguage) const {
        ISRSLCodeGenerator::SRSLCodeGenRes codeGenRes;

        switch (shaderLanguage) {
            case ShaderLanguage::PseudoCode:
                codeGenRes = SRSLPseudoCodeGenerator::Instance().GenerateStages(this);
                break;
            case ShaderLanguage::GLSL:
                codeGenRes = GLSLCodeGenerator::Instance().GenerateStages(this);
                break;
            case ShaderLanguage::HLSL:
            case ShaderLanguage::Metal:
            default:
                return std::string("SRSLShader::ToString() : unknown shader language! Language: " + SR_UTILS_NS::EnumReflector::ToString(shaderLanguage));
        }

        auto&& [result, stages] = codeGenRes;

        if (result.code != SRSLReturnCode::Success) {
            return "SRSLShader::ToString() : " + SR_UTILS_NS::EnumReflector::ToString(result.code) + "\n\tPosition: " + std::to_string(result.position);
        }

        std::string code;

        for (auto&& [stage, stageCode] : stages) {
            code += "Stage[" + SR_UTILS_NS::EnumReflector::ToString(stage) + "] {\n" + stageCode + "\n}";
        }

        return code;
    }

    const SRSLAnalyzedTree::Ptr SRSLShader::GetAnalyzedTree() const {
        return m_analyzedTree;
    }

    bool SRSLShader::Prepare() {
        m_useStack = SRSLRefAnalyzer::Instance().Analyze(m_analyzedTree);
        if (!m_useStack) {
            SR_ERROR("SRSLShader::Prepare() : failed to analyze shader refs!");
            return false;
        }

        for (auto&& pUnit : m_analyzedTree->pLexicalTree->lexicalTree) {
            if (auto&& pVariable = dynamic_cast<SRSLVariable*>(pUnit)) {
                std::string& varName = pVariable->pType->token;
                std::string& varValue = pVariable->pName->token;

                if (varName == "ShaderType") {
                    m_type = SR_UTILS_NS::EnumReflector::FromString<SR_SRSL_NS::ShaderType>(varValue);
                }
                else if (varName == "PolygonMode") {
                    m_createInfo.polygonMode = SR_UTILS_NS::EnumReflector::FromString<PolygonMode>(varValue);
                }
                else if (varName == "CullMode") {
                    m_createInfo.cullMode = SR_UTILS_NS::EnumReflector::FromString<CullMode>(varValue);
                }
                else if (varName == "DepthCompare") {
                    m_createInfo.depthCompare = SR_UTILS_NS::EnumReflector::FromString<DepthCompare>(varValue);
                }
                else if (varName == "PrimitiveTopology") {
                    m_createInfo.primitiveTopology = SR_UTILS_NS::EnumReflector::FromString<PrimitiveTopology>(varValue);
                }
                else if (varName == "BlendEnabled") {
                    m_createInfo.blendEnabled = SR_UTILS_NS::LexicalCast<bool>(varValue);
                }
                else if (varName == "DepthWrite") {
                    m_createInfo.depthWrite = SR_UTILS_NS::LexicalCast<bool>(varValue);
                }
                else if (varName == "DepthTest") {
                    m_createInfo.depthTest = SR_UTILS_NS::LexicalCast<bool>(varValue);
                }
            }
        }

        return true;
    }

    SR_SRSL_NS::ShaderType SRSLShader::GetType() const {
        return m_type;
    }

    Vertices::VertexType SRSLShader::GetVertexType() const {
        switch (GetType()) {
            case ShaderType::Spatial:
            case ShaderType::SpatialCustom:
                return Vertices::VertexType::StaticMeshVertex;
            case ShaderType::Skinned:
                return Vertices::VertexType::SkinnedMeshVertex;
            case ShaderType::PostProcessing:
                return Vertices::VertexType::None;
            case ShaderType::Canvas:
                return Vertices::VertexType::UIVertex;
            case ShaderType::Skybox:
            case ShaderType::Simple:
            case ShaderType::Line:
            case ShaderType::Text:
            case ShaderType::TextUI:
                return Vertices::VertexType::SimpleVertex;
            case ShaderType::Custom:
            case ShaderType::Raygen:
            case ShaderType::AnyHit:
            case ShaderType::ClosestHit:
            case ShaderType::Miss:
            case ShaderType::Particles:
            case ShaderType::Compute:
            case ShaderType::Intersection:
            case ShaderType::Unknown:
            default:
                SRHalt0();
                return Vertices::VertexType::Unknown;
        }
    }
}