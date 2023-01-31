//
// Created by Monika on 22.01.2023.
//

#include <Graphics/SRSL/Shader.h>
#include <Graphics/SRSL/Lexer.h>

namespace SR_SRSL_NS {
    SRSLShader::SRSLShader(SR_UTILS_NS::Path path, SRSLAnalyzedTree::Ptr&& pAnalyzedTree)
        : Super()
        , m_path(std::move(path))
        , m_analyzedTree(SR_UTILS_NS::Exchange(pAnalyzedTree, nullptr))
    { }

    SRSLShader::Ptr SRSLShader::Load(SR_UTILS_NS::Path path) {
        auto&& lexems = SR_SRSL_NS::SRSLLexer::Instance().Parse(path);

        if (lexems.empty()) {
            SR_ERROR("SRSLShader::Load() : failed to parse lexems!\n\tPath: " + path.ToString());
            return nullptr;
        }

        auto&& [pAnalyzedTree, result] = SR_SRSL_NS::SRSLLexicalAnalyzer::Instance().Analyze(std::move(lexems));

        if (!pAnalyzedTree || result.code != SRSLReturnCode::Success) {
            SR_ERROR("SRSLShader::Load() : failed to analyze shader!\n\tPath: " + path.ToString()
                + "\n\tPosition: " + std::to_string(result.position)
                + "\b\tReason: " + SR_UTILS_NS::EnumReflector::ToString(result.code)
            );
            return nullptr;
        }

        return SRSLShader::Ptr(new SRSLShader(std::move(path), std::move(pAnalyzedTree)));
    }

    bool SRSLShader::IsCacheActual() const {
        return false;
    }

    std::string SRSLShader::ToString() const {
        return std::string();
    }
}