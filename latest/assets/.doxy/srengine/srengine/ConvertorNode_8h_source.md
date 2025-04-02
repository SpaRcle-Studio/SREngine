

# File ConvertorNode.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**SRLM**](dir_ccfa529a2c413666958bcf1b1fc32cf9.md) **>** [**ConvertorNode.h**](ConvertorNode_8h.md)

[Go to the documentation of this file](ConvertorNode_8h.md)


```C++
//
// Created by innerviewer on 9/9/2023.
//

#ifndef SR_ENGINE_CONVERTORNODE_H
#define SR_ENGINE_CONVERTORNODE_H

#include <Utils/SRLM/LogicalNode.h>

namespace SR_SRLM_NS {
    class ConvertorNode : public IComputeNode {
    public:
        void InitNode() override;

        void Execute(float_t dt) override;
    public:
        SR_NODISCARD std::string GetInputTypeName() const noexcept;
        SR_NODISCARD std::string GetOutputTypeName() const noexcept;
        SR_NODISCARD uint64_t GetInputHashName() const noexcept;
        SR_NODISCARD uint64_t GetOutputHashName() const noexcept;
        SR_NODISCARD uint64_t GetNodeHashName() const noexcept override;
        SR_NODISCARD std::string GetNodeName() const noexcept override;

        void SetInitInputTypeHashName(uint64_t hashName) { m_initInputTypeHashName = hashName; }
        void SetInitOutputTypeHashName(uint64_t hashName) { m_initOutputTypeHashName = hashName; }

    private:
        SR_NODISCARD std::string ToString(const DataType* pDataType) const;

    private:
        uint64_t m_initInputTypeHashName = SR_UINT64_MAX;
        uint64_t m_initOutputTypeHashName = SR_UINT64_MAX;
    };
}

#endif //SR_ENGINE_CONVERTORNODE_H
```


