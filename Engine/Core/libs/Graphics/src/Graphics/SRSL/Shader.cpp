//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/Shader.h>
#include <Graphics/SRSL/Lexer.h>
#include <Graphics/SRSL/PseudoCodeGenerator.h>
#include <Graphics/SRSL/GLSLCodeGenerator.h>
#include <Graphics/SRSL/AssignExpander.h>
#include <Graphics/SRSL/TypeInfo.h>

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
        auto&& [result, stages] = GenerateStages(shaderLanguage);

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

    const SRSLUseStack::Ptr SRSLShader::GetUseStack() const {
        return m_useStack;
    }

    bool SRSLShader::Prepare() {
        m_useStack = SRSLRefAnalyzer::Instance().Analyze(m_analyzedTree);
        if (!m_useStack) {
            SR_ERROR("SRSLShader::Prepare() : failed to analyze shader refs!");
            return false;
        }

        if (!PrepareSettings()) {
            SR_ERROR("SRSLShader::Prepare() : failed to prepare shader settings!");
            return false;
        }

        if (!PrepareUniformBlocks()) {
            SR_ERROR("SRSLShader::Prepare() : failed to prepare shader uniform blocks!");
            return false;
        }

        if (!PrepareSamplers()) {
            SR_ERROR("SRSLShader::Prepare() : failed to prepare shader samplers!");
            return false;
        }

        if (!PrepareStages()) {
            SR_ERROR("SRSLShader::Prepare() : failed to prepare shader stages!");
            return false;
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

    bool SRSLShader::PrepareSettings() {
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

        if (GetType() == ShaderType::Unknown) {
            SR_ERROR("SRSLShader::PrepareSettings() : shader type is not set!");
            return false;
        }

        return true;
    }

    bool SRSLShader::PrepareUniformBlocks() {
        for (auto&& pUnit : m_analyzedTree->pLexicalTree->lexicalTree) {
            auto&& pVariable = dynamic_cast<SRSLVariable*>(pUnit);
            if (!pVariable || !pVariable->pDecorators) {
                continue;
            }

            if (SR_SRSL_NS::IsSampler(pVariable->GetType())) {
                continue;
            }

            if (auto&& pDecorator = pVariable->pDecorators->Find("shared")) {
                m_shared[pVariable->GetName()] = pVariable;
            }

            if (auto&& pDecorator = pVariable->pDecorators->Find("uniform")) {
                /// не добавляем в блок переменные, которые объявили и не используем
                if (!m_useStack->IsVariableUsedInEntryPoints(pVariable->GetName())) {
                    continue;
                }

                std::string blockName;

                if (pDecorator->args.empty()) {
                    blockName = "BLOCK";
                }
                else {
                    blockName = pDecorator->args[0]->token;
                }

                SRSLUniformBlock::Field field;

                field.name = pVariable->GetName();
                field.type = pVariable->GetType();
                field.isPublic = bool(pVariable->pDecorators->Find("public"));

                auto&& uniformBlock = m_uniformBlocks[blockName];
                uniformBlock.fields.emplace_back(field);
            }
        }

        /// ------------------------------------------------------------------

        for (auto&& [defaultUniform, type] : SR_SRSL_DEFAULT_UNIFORMS) {
            if (m_useStack->IsVariableUsedInEntryPoints(defaultUniform)) {
                SRSLUniformBlock::Field field;

                field.name = defaultUniform;
                field.type = type;
                field.isPublic = false;

                auto&& uniformBlock = m_uniformBlocks["BLOCK"];
                uniformBlock.fields.emplace_back(field);
            }
        }

        /// ------------------------------------------------------------------

        for (auto&& [name, block] : m_uniformBlocks) {
            for (auto&& field : block.fields) {
                field.size = SRSLTypeInfo::Instance().GetTypeSize(field.type, m_analyzedTree);
                block.size += field.size;
            }

            std::sort(block.fields.begin(), block.fields.end(), [](const SRSLUniformBlock::Field& a, const SRSLUniformBlock::Field& b) -> bool {
                return a.size > b.size;
            });
        }

        /// ------------------------------------------------------------------

        return true;
    }

    bool SRSLShader::PrepareSamplers() {
        for (auto&& pUnit : m_analyzedTree->pLexicalTree->lexicalTree) {
            auto&& pVariable = dynamic_cast<SRSLVariable*>(pUnit);
            if (!pVariable || !pVariable->pDecorators) {
                continue;
            }

            if (!SR_SRSL_NS::IsSampler(pVariable->GetType())) {
                continue;
            }

            if (auto&& pDecorator = pVariable->pDecorators->Find("uniform")) {
                SRSLSampler sampler;

                sampler.type = pVariable->GetType();
                sampler.isPublic = bool(pVariable->pDecorators->Find("public"));

                m_samplers[pVariable->GetName()] = sampler;
            }
        }

        for (auto&& [defaultSampler, type] : SR_SRSL_DEFAULT_SAMPLERS) {
            if (m_useStack->IsVariableUsedInEntryPoints(defaultSampler)) {
                SRSLSampler sampler;

                sampler.type = type;
                sampler.isPublic = false;

                m_samplers[defaultSampler] = sampler;
            }
        }

        return true;
    }

    bool SRSLShader::Export(ShaderLanguage shaderLanguage) const {
        auto&& [result, stages] = GenerateStages(shaderLanguage);

        if (result.code != SRSLReturnCode::Success) {
            SR_ERROR("SRSLShader::Export() : " + SR_UTILS_NS::EnumReflector::ToString(result.code) + "\n\tPosition: " + std::to_string(result.position));
            return false;
        }

        for (auto&& [stage, code] : stages) {
            if (m_createInfo.stages.count(stage) == 0) {
                SRHalt("Unknown stage!");
                return false;
            }

            auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Shaders").Concat(m_createInfo.stages.at(stage));

            if (!path.Create() || !SR_UTILS_NS::FileSystem::WriteToFile(path, code)) {
                SR_ERROR("SRSLShader::Export() : failed to write file!\n\tPath: " + path.ToString());
                return false;
            }
        }

        return true;
    }

    bool SRSLShader::PrepareStages() {
        for (auto&& [stage, entryPoint] : SR_SRSL_ENTRY_POINTS) {
            if (!m_analyzedTree->pLexicalTree->FindFunction(entryPoint)) {
                continue;
            }

            m_createInfo.stages[stage] = m_path.ToString() + "/shader." + SR_SRSL_STAGE_EXTENSIONS.at(stage);
        }

        auto&& vertexInfo = Vertices::GetVertexInfo(GetVertexType());
        m_createInfo.vertexAttributes = vertexInfo.m_attributes;
        m_createInfo.vertexDescriptions = vertexInfo.m_descriptions;

        uint64_t binding = 0;

        for (auto&& [name, block] : m_uniformBlocks) {
            block.binding = binding;

            for (auto&& field : block.fields) {
                m_createInfo.uniforms.emplace_back(std::make_pair(
                    binding,
                    field.size
                ));
            }

            ++binding;
        }

        for (auto&& [samplerName, sampler] : m_samplers) {
            sampler.binding = binding;
            ++binding;
        }

        return true;
    }

    ISRSLCodeGenerator::SRSLCodeGenRes SRSLShader::GenerateStages(ShaderLanguage shaderLanguage) const {
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
                SR_ERROR("SRSLShader::ToString() : unknown shader language! Language: " + SR_UTILS_NS::EnumReflector::ToString(shaderLanguage));
                codeGenRes.first = SRSLReturnCode::UnknownShaderLanguage;
                return codeGenRes;
        }

        return codeGenRes;
    }

    const SRSLUniformBlock::Field* SRSLShader::FindField(const std::string& name) const {
        for (auto&& [blockName, block] : m_uniformBlocks) {
            for (auto&& field : block.fields) {
                if (field.name == name) {
                    return &field;
                }
            }
        }

        SR_WARN("SRSLShader::FindField() : field \"" + name + "\" not found!");

        return nullptr;
    }

    const SRSLUniformBlock *SRSLShader::FindUniformBlock(const std::string &name) const {
        for (auto&& [blockName, block] : m_uniformBlocks) {
            if (name == blockName) {
                return &block;
            }
        }

        return nullptr;
    }
}