//
// Created by Monika on 06.02.2023.
//

#include <Graphics/SRSL/TypeInfo.h>
#include <Graphics/SRSL/Lexer.h>
#include <Graphics/SRSL/LexicalAnalyzer.h>
#include <Graphics/SRSL/MathExpression.h>
#include <Graphics/SRSL/Evaluator.h>

namespace SR_SRSL_NS {
    std::vector<uint64_t> SRSLTypeInfo::GetDimension(const std::string &code, const SRSLAnalyzedTree::Ptr& pAnalyzedTree) {
        auto&& pTree = Analyze(code);
        if (!pTree) {
            return { };
        }

        return GetDimension(pTree->pLexicalTree->AsExpression(), pAnalyzedTree);
    }

    std::vector<uint64_t> SRSLTypeInfo::GetDimension(const SRSLExpr* pExpr, const SRSLAnalyzedTree::Ptr& pAnalyzedTree) {
        std::vector<uint64_t> dimension;

        if (pExpr->isArray) {
            dimension.emplace_back(static_cast<uint64_t>(SRSLEvaluator::Instance().Evaluate(pExpr->args[1])));

            if (pExpr->args[0]->isArray) {
                auto&& subDimension = GetDimension(pExpr->args[0], pAnalyzedTree);
                dimension.insert(dimension.begin(), subDimension.begin(), subDimension.end());
            }
        }

        return dimension;
    }

    uint64_t SRSLTypeInfo::GetTypeSize(const std::string& code, const SRSLAnalyzedTree::Ptr& pAnalyzedTree) {
        auto&& pTree = Analyze(code);
        if (!pTree) {
            return 0;
        }

        return GetTypeSize(pTree->pLexicalTree->AsExpression(), pAnalyzedTree);
    }

    uint64_t SRSLTypeInfo::GetAlignedTypeSize(const std::string& code, const SRSLAnalyzedTree::Ptr& pAnalyzedTree) {
        auto&& pTree = Analyze(code);
        if (!pTree) {
            return 0;
        }

        return GetAlignedTypeSize(pTree->pLexicalTree->AsExpression(), pAnalyzedTree);
    }

    uint64_t SRSLTypeInfo::GetTypeSize(const SRSLExpr *pExpr, const SRSLAnalyzedTree::Ptr& pAnalyzedTree) {
        if (pExpr->isCall) {
            SRHalt0();
            return 0;
        }

        uint64_t multiplier = 1;
        uint64_t typeSize = 1;

        std::string type = GetTypeName(pExpr);

        if (pExpr->isArray) {
            multiplier = static_cast<uint64_t>(SRSLEvaluator::Instance().Evaluate(pExpr->args[1]));
        }

        if (SR_SRSL_TYPE_SIZE_TABLE.count(type) == 1) {
            typeSize = SR_SRSL_TYPE_SIZE_TABLE.at(type);
        }
        else {
            typeSize = GetStructSize(type, pAnalyzedTree);
        }

        if (multiplier > 1024 * 1024 * 16) {
            SRHalt("Something went wrong...");
            return 0;
        }

        return typeSize * multiplier;
    }

    uint64_t SRSLTypeInfo::GetAlignedTypeSize(const SRSLExpr *pExpr, const SRSLAnalyzedTree::Ptr& pAnalyzedTree) {
        if (pExpr->isCall) {
            SRHalt0();
            return 0;
        }

        uint64_t multiplier = 1;
        uint64_t typeSize = 1;

        std::string type = GetTypeName(pExpr);

        if (pExpr->isArray) {
            multiplier = static_cast<uint64_t>(SRSLEvaluator::Instance().Evaluate(pExpr->args[1]));
        }

        if (SR_SRSL_TYPE_SIZE_TABLE.count(type) == 1) {
            typeSize = SR_SRSL_TYPE_SIZE_TABLE.at(type);
        }
        else {
            typeSize = GetStructSize(type, pAnalyzedTree);
        }

        if (multiplier > 1024 * 1024 * 16 || typeSize == 0) {
            SRHalt("Something went wrong...");
            return 0;
        }

        const bool powerOfTwo = (typeSize & (typeSize - 1)) == 0;
        auto&& n = static_cast<uint64_t>(std::log2(typeSize));

        if (!powerOfTwo && multiplier > 1) {
            typeSize = std::pow(2, n + 1);
        }

        return typeSize * multiplier;
    }

    uint64_t SRSLTypeInfo::GetStructSize(const std::string& name, const SRSLAnalyzedTree::Ptr &pAnalyzedTree) {
        SRHalt("TODO");
        return 0;
    }

    SRSLAnalyzedTree::Ptr SRSLTypeInfo::Analyze(const std::string &code) {
        auto&& lexems = SRSLLexer::Instance().ParseString(code);
        auto&& [pTree, result] = SRSLLexicalAnalyzer::Instance().Analyze(std::move(lexems));

        if (result.code != SRSLReturnCode::Success) {
            SR_ERROR("SRSLTypeInfo::Analyze() : failed to parse expression!");
            return nullptr;
        }

        if (pTree->pLexicalTree->lexicalTree.empty()) {
            SR_ERROR("SRSLTypeInfo::Analyze() : expression not found!");
            return nullptr;
        }

        auto&& pExpr = dynamic_cast<SRSLExpr*>(pTree->pLexicalTree->lexicalTree.back());
        if (!pExpr) {
            SR_ERROR("SRSLTypeInfo::Analyze() : expression not found!");
            return nullptr;
        }

        return pTree;
    }

    std::string SRSLTypeInfo::GetTypeName(const std::string &code) {
        auto&& pTree = Analyze(code);
        if (!pTree) {
            return { };
        }

        return GetTypeName(pTree->pLexicalTree->AsExpression());
    }

    std::string SRSLTypeInfo::GetTypeName(const SRSLExpr *pExpr) {
        if (pExpr->isArray) {
            return GetTypeName(pExpr->args[0]);
        }

        SRAssert(!pExpr->isCall);

        return pExpr->token;
    }

    ShaderVarType SRSLTypeInfo::StringToType(const std::string& str) {
        if (SR_SRSL_TYPE_STRINGS.count(str) == 1) {
            return SR_SRSL_TYPE_STRINGS.at(str);
        }

        return ShaderVarType::Unknown;
    }
}