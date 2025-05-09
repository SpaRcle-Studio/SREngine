

# File Node.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**Node.h**](Graphics_2inc_2Graphics_2GUI_2Node_8h.md)

[Go to the documentation of this file](Graphics_2inc_2Graphics_2GUI_2Node_8h.md)


```C++
//
// Created by Monika on 11.01.2022.
//

#ifndef SR_ENGINE_NODE_H
#define SR_ENGINE_NODE_H

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
        //explicit Node(SR_SRLM_NS::LogicalNode* pNode);
        Node(const std::string& name, NodeType type);
        Node(const std::string& name, ImColor color);
        Node(std::string  name, NodeType type, ImColor color);

        ~Node() override;

    public:
        Node& AddInput(Pin* pin);
        Node& AddOutput(Pin* pin);

        /*Node& AddInput(PinType type);
        Node& AddOutput(PinType type);

        Node& AddInput(const std::string& name, PinType type);
        Node& AddOutput(const std::string& name, PinType type);

        Node& AddInput(const std::string& name, SR_SRLM_NS::DataType* pDataType);
        Node& AddOutput(const std::string& name, SR_SRLM_NS::DataType* pDataType);*/

        void RemoveInput(uint32_t index);
        void RemoveOutput(uint32_t index);

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
        //SR_NODISCARD SR_SRLM_NS::LogicalNode* GetLogicalNode() const { return m_logicalNode; }

        Node& SetName(std::string name);
        Node& SetPosition(const SR_MATH_NS::FVector2& pos);
        Node& SetType(NodeType type);

        void Draw(NodeBuilder* pBuilder, Pin* pNewLinkPin);
        void PostDraw();

    private:
        //SR_SRLM_NS::LogicalNode* m_logicalNode = nullptr;
        std::string m_name;
        std::vector<Pin*> m_inputs;
        std::vector<Pin*> m_outputs;
        ImColor m_color = ImColor(255, 255, 255, 255);
        NodeType m_type = NodeType::None;
        float_t m_maxOutputWidth = 0.f;
        bool m_hasOutputDelegates = false;

    };
}

namespace std {
    template<> struct hash<SR_GRAPH_GUI_NS::Node> {
        size_t operator()(SR_GRAPH_GUI_NS::Node const& node) const {
            std::hash<uintptr_t> h;
            return h(node.GetId()) + 0x9e3779b9 + (0 << 6) + (0 >> 2);
        }
    };

    template<> struct hash<SR_GRAPH_GUI_NS::Link> {
        size_t operator()(SR_GRAPH_GUI_NS::Node const& link) const {
            std::hash<uintptr_t> h;
            return h(link.GetId()) + 0x9e3779b9 + (0 << 6) + (0 >> 2);
        }
    };
}

#endif //SR_ENGINE_NODE_H
```


