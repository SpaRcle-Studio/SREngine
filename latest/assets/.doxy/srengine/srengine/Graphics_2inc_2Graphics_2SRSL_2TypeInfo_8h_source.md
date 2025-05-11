

# File TypeInfo.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**SRSL**](dir_8b5756bea5e0d505138eb40b052c312a.md) **>** [**TypeInfo.h**](Graphics_2inc_2Graphics_2SRSL_2TypeInfo_8h.md)

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


