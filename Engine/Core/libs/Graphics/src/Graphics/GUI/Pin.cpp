//
// Created by Monika on 18.01.2022.
//

#include <Graphics/GUI/Pin.h>

namespace SR_GRAPH_NS {
    Pin::Pin()
        : Pin(std::string(), PinType::None, PinKind::None)
    { }

    Pin::Pin(const std::string &name)
        : Pin(name, PinType::None, PinKind::None)
    { }

    Pin::Pin(const std::string &name, PinType type)
        : Pin(name, type, PinKind::None)
    { }

    Pin::Pin(const std::string &name, PinKind kind)
        : Pin(name, PinType::None, kind)
    { }

    Pin::Pin(const std::string &name, PinType type, PinKind kind)
        : m_name(name)
        , m_type(type)
        , m_kind(kind)
    {
        //m_id = NodeManager::Instance().AllocUniqueId(this);
    }

    Pin::~Pin() {
        if (Valid()) {
          //  NodeManager::Instance().FreeUniqueId(m_id.Get());
            SetNode(nullptr);
        }
    }

    void Pin::Draw(float_t maxPinWidth) const {
        //ax::NodeEditor::BeginPin(m_id, m_kind == PinKind::Input ? ax::NodeEditor::PinKind::Input : ax::NodeEditor::PinKind::Output);

        ImGui::SetWindowFontScale(1.5);

        const auto size = ImVec2(20, 20);
        const bool connected = false;
        const ImColor color = GetIconColor(m_type);
        const auto alpha = 255;

        //ax::NodeEditor::PinPivotSize(ImVec2(0, 0));

        switch (m_kind) {
            case PinKind::Output:
                //ax::NodeEditor::PinPivotAlignment(ImVec2(1.0f, 0.5f));

                ImGui::SetCursorPosX(
                        ImGui::GetCursorPosX()
                        + (maxPinWidth - ImGui::CalcTextSize(m_name.c_str()).x)
                        + 2 * ImGui::GetStyle().ItemSpacing.x);

                ImGui::TextUnformatted(m_name.c_str());

                ImGui::SameLine();
                Icon(size, GetIconType(m_type), connected, color, ImColor(32, 32, 32, alpha));
                break;
            case PinKind::Input:
                Icon(size, GetIconType(m_type), connected, color, ImColor(32, 32, 32, alpha));

                ImGui::SameLine();

                ImGui::TextUnformatted(m_name.c_str());

                //ax::NodeEditor::PinPivotAlignment(ImVec2(1.f / ImGui::GetItemRectSize().x, 0.5f));
                break;
            case PinKind::None:
            default:
            SRAssert(false);
        }

        //ax::NodeEditor::EndPin();
    }

    ImColor Pin::GetIconColor(const PinType &type) {
        switch (type) {
            case PinType::Flow:     return ImColor(255, 255, 255);
            case PinType::Bool:     return ImColor(220,  48,  48);
            case PinType::Int:      return ImColor( 68, 201, 156);
            case PinType::Numeric:  return ImColor( 68, 201, 156);
            case PinType::Float:    return ImColor(147, 226,  74);
            case PinType::String:   return ImColor(124,  21, 153);
            case PinType::Object:   return ImColor( 51, 150, 215);
            case PinType::Function: return ImColor(218,   0, 183);
            case PinType::Delegate: return ImColor(255,  48,  48);
            case PinType::Event:    return ImColor(255,  48,  48);
            default:
            SRAssertOnce(false);
                return ImColor(0, 0, 0);
        }
    }

    IconType Pin::GetIconType(const PinType &type) {
        switch (type) {
            case PinType::Flow:     return IconType::Flow;
            case PinType::Bool:     return IconType::Circle;
            case PinType::Int:      return IconType::Circle;
            case PinType::Numeric:  return IconType::Circle;
            case PinType::Float:    return IconType::Circle;
            case PinType::String:   return IconType::Circle;
            case PinType::Object:   return IconType::Circle;
            case PinType::Function: return IconType::Circle;
            case PinType::Delegate: return IconType::Square;
            case PinType::Event:    return IconType::Square;
            default:
            SRAssertOnce(false);
                return IconType::Square;
        }
    }

    bool Pin::Valid() const {
        //return m_id != ax::NodeEditor::PinId::Invalid;
        return false;
    }

    Pin* Pin::Copy() const {
        auto pin = new Pin();

        pin->m_name = m_name;
        pin->m_type = m_type;
        pin->m_kind = m_kind;

        return pin;
    }

    void Pin::SetNode(Node* node) {
        if (m_node == node)
            return;

        m_node = node;
    }

    float_t Pin::GetWidth() const {
        return static_cast<float_t>(m_name.size()); //TODO: crash ImGui::CalcTextSize(m_name.c_str()).x;
    }

    void Pin::AddLink(Link *link) {
    #if defined(SR_DEBUG)
        if (m_links.count(link) == 1) {
            SRAssert(false);
            return;
        }
    #endif

        m_links.insert(link);
    }

    void Pin::RemoveLink(Link *link) {
    #if defined(SR_DEBUG)
        if (m_links.count(link) == 0) {
            SRAssert(false);
            return;
        }
    #endif

        m_links.erase(link);
    }

    bool Pin::IsLinked(Pin *pin) const {
        return false;
    }
}