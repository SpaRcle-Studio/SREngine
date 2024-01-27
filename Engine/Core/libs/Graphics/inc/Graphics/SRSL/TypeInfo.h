//
// Created by Monika on 06.02.2023.
//

#ifndef SR_ENGINE_SRSL_TYPEINFO_H
#define SR_ENGINE_SRSL_TYPEINFO_H

#include <Graphics/SRSL/LexicalTree.h>
#include <Graphics/SRSL/ShaderType.h>
#include <Graphics/Loaders/ShaderProperties.h>

namespace SR_SRSL_NS {
    class SRSLTypeInfo : public SR_UTILS_NS::Singleton<SRSLTypeInfo> {
        SR_REGISTER_SINGLETON(SRSLTypeInfo)
    public:
        SR_NODISCARD std::vector<uint64_t> GetDimension(const std::string& code, const SRSLAnalyzedTree::Ptr& pAnalyzedTree);
        SR_NODISCARD std::vector<uint64_t> GetDimension(const SRSLExpr* pExpr, const SRSLAnalyzedTree::Ptr& pAnalyzedTree);

        SR_NODISCARD ShaderVarType StringToType(const std::string& str);
        SR_NODISCARD std::string GetTypeName(const std::string& code);
        SR_NODISCARD std::string GetTypeName(const SRSLExpr* pExpr);

        SR_NODISCARD uint64_t GetTypeSize(const std::string& code, const SRSLAnalyzedTree::Ptr& pAnalyzedTree);
        SR_NODISCARD uint64_t GetTypeSize(const SRSLExpr* pExpr, const SRSLAnalyzedTree::Ptr& pAnalyzedTree);

        SR_NODISCARD uint64_t GetAlignedTypeSize(const std::string& code, const SRSLAnalyzedTree::Ptr& pAnalyzedTree);
        SR_NODISCARD uint64_t GetAlignedTypeSize(const SRSLExpr* pExpr, const SRSLAnalyzedTree::Ptr& pAnalyzedTree);

        SR_NODISCARD uint64_t GetStructSize(const std::string& name, const SRSLAnalyzedTree::Ptr& pAnalyzedTree);

    private:
        SR_NODISCARD SRSLAnalyzedTree::Ptr Analyze(const std::string& code);

    };
}

#endif //SR_ENGINE_SRSL_TYPEINFO_H
