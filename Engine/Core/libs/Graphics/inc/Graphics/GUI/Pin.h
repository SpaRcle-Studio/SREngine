//
// Created by Monika on 18.01.2022.
//

#ifndef SRENGINE_PIN_H
#define SRENGINE_PIN_H

#include <Utils/Common/Enumerations.h>
#include <Graphics/GUI/Icons.h>

namespace ax::NodeEditor {
    enum class PinKind;
}

namespace SR_GRAPH_NS::GUI {
    class Node;
    class Link;

    SR_ENUM_NS_CLASS_T(PinType, int32_t,
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

    struct PinConstValue {
        bool m_bool = false;
        std::string m_string;
        float_t m_float = 0.f;
        int32_t m_int = 0;
    };

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

        void DrawPinIcon(bool connected, uint32_t alpha);

        void DrawOption();

        void SetNode(Node* node);

        void AddLink(Link* link);
        void RemoveLink(Link* link);

        SR_NODISCARD uintptr_t GetId() const {
            return reinterpret_cast<const uintptr_t>(this);
        }

        SR_NODISCARD bool IsLinked(Pin* pin) const;
        SR_NODISCARD bool IsLinked() const;
        SR_NODISCARD float_t GetWidth() const;
        SR_NODISCARD PinType GetType() const { return m_type; }
        SR_NODISCARD PinKind GetKind() const { return m_kind; }
        SR_NODISCARD Node* GetNode() const { return m_node; }

        SR_NODISCARD Pin* Copy() const;

        void Begin(PinKind kind) const;
        void End() const;

    private:
        PinConstValue m_constValue;
        std::unordered_set<Link*> m_links;
        Node* m_node = nullptr;
        std::string m_name;
        PinType m_type;
        PinKind m_kind;

    };
}

#endif //SRENGINE_PIN_H
