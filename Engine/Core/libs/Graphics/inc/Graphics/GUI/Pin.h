//
// Created by Monika on 18.01.2022.
//

#ifndef SRENGINE_PIN_H
#define SRENGINE_PIN_H

#include <Utils/Common/Enumerations.h>
#include <Graphics/GUI/Icons.h>

namespace SR_GRAPH_NS::GUI {
    class Node;
    class Link;

    SR_ENUM_NS_CLASS(PinType,
          None,
          Flow,
          Bool,
          Event,
          Int,
          Float,
          String,
          Object,
          Numeric,
          Function,
          Delegate
    );

    SR_ENUM_NS_CLASS(PinKind,
          None,
          Output,
          Input
    );

    class Pin : private SR_UTILS_NS::NonCopyable {
        friend class Node;
        friend class Link;
    public:
        Pin();
        explicit Pin(const std::string& name);
        Pin(const std::string& name, PinType type);
        Pin(const std::string& name, PinKind kind);
        Pin(const std::string& name, PinType type, PinKind kind);

        ~Pin() override;

    public:
        static ImColor GetIconColor(const PinType& type);
        static IconType GetIconType(const PinType& type);

        void SetNode(Node* node);

        void AddLink(Link* link);
        void RemoveLink(Link* link);

        [[nodiscard]] bool IsLinked(Pin* pin) const;
        [[nodiscard]] bool Valid() const;
        [[nodiscard]] float_t GetWidth() const;
        [[nodiscard]] PinType GetType() const { return m_type; }
        [[nodiscard]] PinKind GetKind() const { return m_kind; }
        [[nodiscard]] Node* GetNode() const { return m_node; }

        [[nodiscard]] Pin* Copy() const;

        void Draw(float_t maxPinWidth = 0.f) const;

    private:
        std::unordered_set<Link*> m_links;
        Node* m_node = nullptr;
        //ax::NodeEditor::PinId m_id;
        std::string m_name;
        PinType m_type;
        PinKind m_kind;

    };
}

#endif //SRENGINE_PIN_H
