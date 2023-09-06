//
// Created by Monika on 11.01.2022.
//

#ifndef SRENGINE_NODE_H
#define SRENGINE_NODE_H

#include <Utils/SRLM/DataType.h>
#include <Utils/SRLM/LogicalNode.h>
#include <Graphics/GUI/Icons.h>

namespace SR_GRAPH_GUI_NS {
    SR_ENUM_NS_CLASS(NodeType,
        None,
        Blueprint,
        Simple,
        Tree,
        Comment,
        Houdini,
        Connector
    );

    class NodeBuilder;

    class Pin;
    class Node;
    class Link;

    class Node : public SR_UTILS_NS::NonCopyable {
        using PinType = SR_SRLM_NS::DataTypeClass;
    public:
        Node();
        explicit Node(const std::string& name);
        explicit Node(SR_SRLM_NS::LogicalNode* pNode);
        Node(const std::string& name, NodeType type);
        Node(const std::string& name, ImColor color);
        Node(const std::string& name, NodeType type, ImColor color);

        ~Node() override;

    public:
        Node& AddInput(Pin* pin);
        Node& AddOutput(Pin* pin);

        Node& AddInput(PinType type);
        Node& AddOutput(PinType type);

        Node& AddInput(const std::string& name, PinType type);
        Node& AddOutput(const std::string& name, PinType type);

        Node& AddInput(const std::string& name, SR_SRLM_NS::DataType* pDataType);
        Node& AddOutput(const std::string& name, SR_SRLM_NS::DataType* pDataType);

        SR_NODISCARD Pin* GetInputPin(uint32_t index);
        SR_NODISCARD Pin* GetOutputPin(uint32_t index);

        SR_NODISCARD uintptr_t GetId() const;
        SR_NODISCARD std::string GetName() const;
        SR_NODISCARD uint64_t GetHashName() const;
        SR_NODISCARD bool IsConnector() const { return m_type == NodeType::Connector; }
        SR_NODISCARD const std::vector<Pin*>& GetInputs() const noexcept { return m_inputs; }
        SR_NODISCARD const std::vector<Pin*>& GetOutputs() const noexcept { return m_outputs; }
        SR_NODISCARD int32_t GetPinIndex(const Pin* pPin) const;
        SR_NODISCARD SR_MATH_NS::FVector2 GetPosition() const;

        SR_NODISCARD Node* Copy() const;

        Node& SetName(std::string name);
        Node& SetPosition(const SR_MATH_NS::FVector2& pos);
        Node& SetType(NodeType type);

        void Draw(NodeBuilder* pBuilder, Pin* pNewLinkPin);

    private:
        SR_SRLM_NS::LogicalNode* m_logicalNode = nullptr;
        std::string m_name;
        std::vector<Pin*> m_inputs;
        std::vector<Pin*> m_outputs;
        ImColor m_color = ImColor(255, 255, 255, 255);
        NodeType m_type = NodeType::None;
        float_t m_maxOutputWidth;
        bool m_hasOutputDelegates = false;

    };
}

namespace std {
    template<> struct hash<Framework::Graphics::GUI::Node> {
        size_t operator()(Framework::Graphics::GUI::Node const& node) const {
            std::hash<uintptr_t> h;
            return h(node.GetId()) + 0x9e3779b9 + (0 << 6) + (0 >> 2);
        }
    };

    template<> struct hash<Framework::Graphics::GUI::Link> {
        size_t operator()(Framework::Graphics::GUI::Node const& link) const {
            std::hash<uintptr_t> h;
            return h(link.GetId()) + 0x9e3779b9 + (0 << 6) + (0 >> 2);
        }
    };
}

#endif //SRENGINE_NODE_H
