

# File ConvertorNode.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**SRLM**](dir_a6f28b551a04c8f6c9ec3f9b059c2feb.md) **>** [**ConvertorNode.h**](ConvertorNode_8h.md)

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


