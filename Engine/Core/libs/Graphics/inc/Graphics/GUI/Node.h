//
// Created by Monika on 11.01.2022.
//

#ifndef SRENGINE_NODE_H
#define SRENGINE_NODE_H

#include <Utils/Common/Enumerations.h>
#include <Graphics/GUI/Icons.h>

namespace SR_GRAPH_NS::GUI {
    SR_ENUM_NS_CLASS(NodeType,
        None,
        Blueprint,
        Simple,
        Tree,
        Comment,
        Houdini
    );

    enum class PinType : int32_t;

    class NodeBuilder;

    class Pin;
    class Node;
    class Link;

    class Node : public SR_UTILS_NS::NonCopyable {
    public:
        Node();
        explicit Node(const std::string& name);
        Node(const std::string& name, NodeType type);
        Node(const std::string& name, ImColor color);
        Node(const std::string& name, NodeType type, ImColor color);

        ~Node() override;

    public:
        Node& AddInput(Pin* pin);
        Node& AddOutput(Pin* pin);

        Node& AddInput(const std::string& name, PinType type);
        Node& AddOutput(const std::string& name, PinType type);

        SR_NODISCARD Pin* GetInputPin(uint32_t index);
        SR_NODISCARD Pin* GetOutputPin(uint32_t index);

        SR_NODISCARD uintptr_t GetId() const;
        SR_NODISCARD std::string GetName() const;

        SR_NODISCARD Node* Copy() const;

        void Draw(NodeBuilder* pBuilder, Pin* pNewLinkPin) const;

    private:
        std::string m_name;
        std::vector<Pin*> m_inputs;
        std::vector<Pin*> m_outputs;
        ImColor m_color;
        NodeType m_type;
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
