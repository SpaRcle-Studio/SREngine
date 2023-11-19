//
// Created by Monika on 30.08.2023.
//

#ifndef SRENGINE_LOGICALNODE_H
#define SRENGINE_LOGICALNODE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Common/ToString.h>
#include <Utils/Xml.h>

namespace SR_SRLM_NS {
    class DataType;
    class LogicalMachine;

    SR_ENUM_NS_STRUCT_T(LogicalNodeStatus, uint64_t,
        None             = 1 << 0,  /// NOLINT
        Success          = 1 << 1,  /// NOLINT
        Warning          = 1 << 2,  /// NOLINT
        Incomplete       = 1 << 3,  /// NOLINT
        InputNullPtr     = 1 << 4,  /// NOLINT
        InputRangeError  = 1 << 5,  /// NOLINT
        InputTypeError   = 1 << 6,  /// NOLINT
        OutputRangeError = 1 << 7,  /// NOLINT
        ExecutionError   = 1 << 8,  /// NOLINT
        ComputeError     = 1 << 9,  /// NOLINT
        NotExecuted      = 1 << 10, /// NOLINT

        ErrorStatus =
                Incomplete | InputNullPtr | InputNullPtr | InputRangeError |
                InputTypeError | OutputRangeError | ExecutionError | ComputeError | NotExecuted
    );

    SR_ENUM_NS_CLASS_T(LogicalNodeType, uint8_t,
        Compute, Executable, Connector, StartReset, EndReset
    );

    class LogicalNode : public SR_UTILS_NS::NonCopyable {
    public:
        using Hash = uint64_t;
        struct NodeConnect {
            LogicalNode* pNode = nullptr;
            uint32_t pinIndex = 0;
        };
        struct NodePin {
            SR_NODISCARD LogicalNode* GetFirstNode() const { return connections.empty() ? nullptr : connections.front().pNode; }
            SR_NODISCARD uint32_t GetFirstNodePin() const { return connections.empty() ? SR_UINT32_MAX : connections.front().pinIndex; }
            std::vector<NodeConnect> connections;
            DataType* pData = nullptr;
            Hash hashName = SR_UINT64_MAX;
        };
        using Pins = std::vector<NodePin>;
    public:
        ~LogicalNode() override;

    public:
        SR_NODISCARD static LogicalNode* LoadXml(const SR_XML_NS::Node& xmlNode);

        void ClearLogicalNode();

        void ResetInputFlows();
        void ResetOutputFlows();
        void ResetStatus();

        void SetMachine(LogicalMachine* pMachine) { m_machine = pMachine; }
        void SetNodeIndex(uint32_t index) { m_nodeIndex = index; }

        virtual void SaveXml(SR_XML_NS::Node& xmlNode);
        virtual void SetInput(const DataType* pInput, uint32_t index);

        SR_NODISCARD const DataType* CalcInput(uint32_t index);

        SR_NODISCARD virtual const DataType* GetOutput(uint32_t index);
        SR_NODISCARD Pins& GetInputs() { return m_inputs; }
        SR_NODISCARD Pins& GetOutputs() { return m_outputs; }
        SR_NODISCARD LogicalNode* GetBaseLogicalNode() noexcept { return this; }
        SR_NODISCARD virtual uint64_t GetNodeHashName() const noexcept = 0;
        SR_NODISCARD virtual std::string GetNodeName() const noexcept = 0;

        virtual void Reset();
        virtual void MarkDirty();
        virtual void InitValues() { }
        virtual void InitNode() { }

        virtual void Execute(float_t dt) {
            m_status |= LogicalNodeStatus::Success;
        }

        SR_NODISCARD virtual bool IsNeedRepeat() const { return false; }
        SR_NODISCARD virtual bool IsNeedPostRepeat() const { return false; }
        SR_NODISCARD virtual bool IsEntryPoint() const noexcept { return false; }
        SR_NODISCARD virtual bool IsDirty() const noexcept { return false; }
        SR_NODISCARD virtual LogicalNodeType GetType() const noexcept = 0;
        SR_NODISCARD bool HasErrors() const { return m_status & LogicalNodeStatus::ErrorStatus; }
        SR_NODISCARD bool IsSuccessfullyCompleted() const noexcept;
        SR_NODISCARD uint32_t GetNodeIndex() const noexcept { return m_nodeIndex; }
        SR_NODISCARD LogicalNodeStatusFlag GetStatus() const noexcept { return m_status; }

    public:
        void RemoveInput(uint32_t index);
        void RemoveOutput(uint32_t index);

        NodePin& AddInputData(DataType* pData, uint64_t hashName = SR_UINT64_MAX);
        NodePin& AddOutputData(DataType* pData, uint64_t hashName = SR_UINT64_MAX);

        void RemoveInputConnection(LogicalNode* pNode, uint32_t pinIndex);
        void RemoveOutputConnection(LogicalNode* pNode, uint32_t pinIndex);

        void AddInputConnection(LogicalNode* pNode, uint32_t nodePinIndex, uint32_t pinIndex);
        void AddOutputConnection(LogicalNode* pNode, uint32_t nodePinIndex, uint32_t pinIndex);

        template<typename T> NodePin& AddInputData(uint64_t hashName = SR_UINT64_MAX) { return AddInputData(new T(), hashName); }
        template<typename T> NodePin& AddOutputData(uint64_t hashName = SR_UINT64_MAX) { return AddOutputData(new T(), hashName); }

    protected:
        mutable LogicalNodeStatusFlag m_status = LogicalNodeStatus::None;

        uint32_t m_nodeIndex = SR_UINT32_MAX;

        Pins m_inputs;
        Pins m_outputs;

        LogicalMachine* m_machine = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class IExecutableNode : public LogicalNode {
        using Super = LogicalNode;
    protected:
        using Base = IExecutableNode;

    protected:
        IExecutableNode() = default;

    public:
        SR_NODISCARD LogicalNodeType GetType() const noexcept final { return LogicalNodeType::Executable; }

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class IComputeNode : public LogicalNode {
    protected:
        using Base = IExecutableNode;

    public:
        void MarkDirty() override;

        SR_NODISCARD const DataType* GetOutput(uint32_t index) override;

    protected:
        SR_NODISCARD bool IsDirty() const noexcept override { return m_dirty; }
        SR_NODISCARD LogicalNodeType GetType() const noexcept final { return LogicalNodeType::Compute; }

    protected:
        bool m_dirty = true;

    };
}

#endif //SRENGINE_LOGICALNODE_H
