

# File TypeInfo.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**SRSL**](dir_656381c30e8ac6fd851e2621c9eff128.md) **>** [**TypeInfo.h**](Graphics_2inc_2Graphics_2SRSL_2TypeInfo_8h.md)

[Go to the documentation of this file](Graphics_2inc_2Graphics_2SRSL_2TypeInfo_8h.md)


```C++
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
```


