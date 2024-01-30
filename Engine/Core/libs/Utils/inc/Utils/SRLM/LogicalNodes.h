//
// Created by Monika on 05.09.2023.
//

#ifndef SR_ENGINE_LOGICALNODES_H
#define SR_ENGINE_LOGICALNODES_H

#include <Utils/SRLM/LogicalNode.h>
#include <Utils/SRLM/LogicalNodeManager.h>

namespace SR_SRLM_NS {
    class ConnectorNode : public LogicalNode {
        SR_REGISTER_LOGICAL_NODE(ConnectorNode, Connector, { })
    public:
        SR_NODISCARD LogicalNodeType GetType() const noexcept final { return LogicalNodeType::Connector; }

    };

    class StartResetNode : public LogicalNode {
        SR_REGISTER_LOGICAL_NODE(StartResetNode, Start Reset, { "Logic" })
        using Super = LogicalNode;
    public:
        SR_NODISCARD LogicalNodeType GetType() const noexcept override { return LogicalNodeType::StartReset; }

        void Execute(float_t dt) override;
        void InitNode() override;

    };

    class EndResetNode : public LogicalNode {
        SR_REGISTER_LOGICAL_NODE(EndResetNode, End Reset, { "Logic" })
        using Super = LogicalNode;
    public:
        SR_NODISCARD LogicalNodeType GetType() const noexcept override { return LogicalNodeType::EndReset; }

        void Execute(float_t dt) override;
        void InitNode() override;

    };

    class SynchronizeNode : public IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(SynchronizeNode, Synchronize, { "Logic" })
        using Super = IExecutableNode;
    public:
        void Execute(float_t dt) override;
        void InitNode() override;

    };

    class SequenceNode : public IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(SequenceNode, Sequence, { "Logic" })
        using Super = IExecutableNode;
    public:
        void Execute(float_t dt) override;
        void InitNode() override;

    };

    class BranchNode : public IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(BranchNode, Branch, { "Logic" })
        using Super = IExecutableNode;
    public:
        void Execute(float_t dt) override;
        void InitNode() override;

    };

    class CreateStructNode : public IComputeNode {
        SR_REGISTER_LOGICAL_NODE(CreateStructNode, Create Struct, { })
        using Super = IComputeNode;
    public:
        void Execute(float_t dt) override;
        void InitNode() override;

        void SetStructHashName(uint64_t hash) { m_structHashName = hash; }

    private:
        uint64_t m_structHashName = SR_UINT64_MAX;

    };

    class BreakStructNode : public IComputeNode {
        SR_REGISTER_LOGICAL_NODE(BreakStructNode, Break Struct, { })
        using Super = IComputeNode;
    public:
        void Execute(float_t dt) override;
        void InitNode() override;

        void SetStructHashName(uint64_t hash) { m_structHashName = hash; }

    private:
        uint64_t m_structHashName = SR_UINT64_MAX;

    };

    class DebugPrintNode : public IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(DebugPrintNode, Debug Print, { "Base" })
        using Super = IExecutableNode;
    public:
        void Execute(float_t dt) override;
        void InitValues() override;
        void InitNode() override;
    };

    class StartNode : public IExecutableNode {
        SR_REGISTER_LOGICAL_NODE(StartNode, Start, { "Base" })
        using Super = IExecutableNode;
    public:
        void Execute(float_t dt) override;
        void InitNode() override;
        SR_NODISCARD bool IsEntryPoint() const noexcept override { return true; }
    };

    class ConstructorNode : public IComputeNode {
        using Super = IComputeNode;
    public:
        SR_NODISCARD uint64_t GetNodeHashName() const noexcept override;
        SR_NODISCARD std::string GetNodeName() const noexcept override;
        void Execute(float_t dt) override;
        void InitNode() override;
        void SetInitTypeHashName(uint64_t hashName) { m_initTypeHashName = hashName; }

    private:
        uint64_t m_initTypeHashName = SR_UINT64_MAX;

    };

    class PlusNode : public IComputeNode {
        using Super = IComputeNode;
    public:
        void Execute(float_t dt) override;

    };
}

#endif //SR_ENGINE_LOGICALNODES_H
