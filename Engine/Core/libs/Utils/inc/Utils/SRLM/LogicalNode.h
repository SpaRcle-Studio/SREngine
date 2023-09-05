//
// Created by Monika on 30.08.2023.
//

#ifndef SRENGINE_LOGICALNODE_H
#define SRENGINE_LOGICALNODE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>

namespace SR_SRLM_NS {
    class DataType;

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
        Compute, Executable, Connector
    );

    class LogicalNode : public SR_UTILS_NS::NonCopyable {
    public:
        using Hash = uint64_t;
        struct NodePin {
            LogicalNode* pNode = nullptr;
            DataType* pData = nullptr;
            Hash hashName = SR_UINT64_MAX;
        };
        using Pins = std::vector<NodePin>;
    public:
        ~LogicalNode() override;

    public:
        virtual void SetInput(const DataType* pInput, uint8_t index);

        SR_NODISCARD virtual const DataType* GetOutput(uint8_t index);
        SR_NODISCARD virtual LogicalNode* GetOutputNode(uint8_t index);
        SR_NODISCARD const Pins& GetInputs() const { return m_inputs; }
        SR_NODISCARD const Pins& GetOutputs() const { return m_outputs; }
        SR_NODISCARD virtual uint64_t GetHashName() const noexcept = 0;
        SR_NODISCARD virtual std::string GetName() const noexcept = 0;

        virtual void Reset();
        virtual void MarkDirty();
        virtual void InitDefault() { }

        SR_NODISCARD virtual bool IsNeedRepeat() const { return false; }
        SR_NODISCARD virtual bool IsNeedPostRepeat() const { return false; }
        SR_NODISCARD virtual bool IsEntryPoint() const noexcept { return false; }
        SR_NODISCARD virtual LogicalNodeType GetType() const noexcept = 0;
        SR_NODISCARD bool HasErrors() const { return m_status & LogicalNodeStatus::ErrorStatus; }
        SR_NODISCARD LogicalNodeStatusFlag GetStatus() const { return m_status; }

    public:
        void AddInputData(DataType* pData, uint64_t hashName = SR_UINT64_MAX);
        void AddOutputData(DataType* pData, uint64_t hashName = SR_UINT64_MAX);

        template<typename T> void AddInputData(uint64_t hashName = SR_UINT64_MAX) { AddInputData(new T(), hashName); }
        template<typename T> void AddOutputData(uint64_t hashName = SR_UINT64_MAX) { AddOutputData(new T(), hashName); }

    protected:
        LogicalNodeStatusFlag m_status = LogicalNodeStatus::None;
        
        Pins m_inputs;
        Pins m_outputs;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class IExecutableNode : public LogicalNode {
    protected:
        using Super = LogicalNode;
        using Base = IExecutableNode;

    protected:
        IExecutableNode() = default;

    public:
        virtual void Execute(float_t dt) = 0;
        SR_NODISCARD LogicalNodeType GetType() const noexcept final { return LogicalNodeType::Executable; }

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class IComputeNode : public LogicalNode {
    protected:
        using Base = IExecutableNode;

    public:
        void MarkDirty() override;

        SR_NODISCARD const DataType* GetOutput(uint8_t index) override;

    protected:
        virtual void Compute() = 0;
        SR_NODISCARD LogicalNodeType GetType() const noexcept final { return LogicalNodeType::Compute; }

    protected:
        bool m_dirty = true;

    };
}

#endif //SRENGINE_LOGICALNODE_H
