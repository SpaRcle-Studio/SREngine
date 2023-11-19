//
// Created by innerviewer on 9/9/2023.
//

#ifndef SRENGINE_CONVERTORNODE_H
#define SRENGINE_CONVERTORNODE_H

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

#endif //SRENGINE_CONVERTORNODE_H
