//
// Created by Monika on 18.01.2022.
//

#ifndef SR_ENGINE_PIN_H
#define SR_ENGINE_PIN_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Math/Vector2.h>
#include <Graphics/GUI/Icons.h>

namespace ax::NodeEditor {
    enum class PinKind;
}

namespace SR_SRLM_NS {
    class DataType;
    enum class DataTypeClass : uint8_t;
}

namespace SR_GRAPH_NS::GUI {
    class Node;
    class Link;

    SR_ENUM_NS_CLASS(PinKind,
          None,
          Output,
          Input
    );

    class Pin : private SR_UTILS_NS::NonCopyable {
        friend class Node;
        friend class Link;
        using PinType = SR_SRLM_NS::DataTypeClass;
        using DataTypePtr = SR_SRLM_NS::DataType*;
    public:
        Pin();
        explicit Pin(const std::string& name);
        Pin(const std::string& name, DataTypePtr pData);
        Pin(const std::string& name, PinKind kind);
        Pin(std::string  name, PinKind kind, DataTypePtr pData);
        ~Pin() override;

    public:
        static ImColor GetIconColor(const PinType& type);
        static IconType GetIconType(const PinType& type);

        void DrawPinIcon(bool connected, uint32_t alpha);

        void DrawOption();
        void PostDrawOption();

        void SetNode(Node* node);

        void AddLink(Link* link);
        void RemoveLink(Link* link);

        SR_NODISCARD uintptr_t GetId() const {
            return reinterpret_cast<const uintptr_t>(this);
        }

        SR_NODISCARD bool IsLinked(Pin* pin) const;
        SR_NODISCARD bool IsLinked() const;
        SR_NODISCARD bool CanLink() const;
        SR_NODISCARD float_t GetWidth() const;
        SR_NODISCARD PinType GetType() const;
        SR_NODISCARD PinKind GetKind() const { return m_kind; }
        SR_NODISCARD Node* GetNode() const { return m_node; }
        SR_NODISCARD DataTypePtr GetDataType() const { return m_dataType; }
        SR_NODISCARD uint32_t GetIndex() const;
        SR_NODISCARD const std::string& GetName() const { return m_name; }

        void Begin(PinKind kind) const;
        void End() const;

    private:
        bool m_editEnum = false;
        DataTypePtr m_dataType = nullptr;

        std::unordered_set<Link*> m_links;
        Node* m_node = nullptr;
        std::string m_name;
        PinKind m_kind;

    };
}

#endif //SR_ENGINE_PIN_H
