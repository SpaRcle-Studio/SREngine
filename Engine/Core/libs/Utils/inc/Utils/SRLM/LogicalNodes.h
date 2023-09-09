//
// Created by Monika on 05.09.2023.
//

#ifndef SRENGINE_LOGICALNODES_H
#define SRENGINE_LOGICALNODES_H

#include <Utils/SRLM/LogicalNode.h>
#include <Utils/SRLM/LogicalNodeManager.h>

namespace SR_SRLM_NS {
    class ConnectorNode : public LogicalNode {
    public:
        SR_REGISTER_LOGICAL_NODE(ConnectorNode, Connector, { })

    public:
        SR_NODISCARD LogicalNodeType GetType() const noexcept final { return LogicalNodeType::Connector; }

    };

    class DebugPrintNode : public IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(DebugPrintNode, Debug Print, { "Base" })
    public:
        void Execute(float_t dt) override;
        void InitValues() override;
        void InitNode() override;
    };

    class StartNode : public IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(StartNode, Start, { "Base" })
    public:
        void Execute(float_t dt) override;
        void InitNode() override;
        SR_NODISCARD bool IsEntryPoint() const noexcept override { return true; }
    };

    class ConstructorNode : public IComputeNode {
    public:
        SR_NODISCARD uint64_t GetHashName() const noexcept override;
        SR_NODISCARD std::string GetName() const noexcept override;
        void Compute() override;
        void InitNode() override;
        void SetInitTypeHashName(uint64_t hashName) { m_initTypeHashName = hashName; }

    private:
        uint64_t m_initTypeHashName = SR_UINT64_MAX;

    };

    class PlusNode : public IComputeNode {
    public:
        void Compute() override;

    };
}

#endif //SRENGINE_LOGICALNODES_H
