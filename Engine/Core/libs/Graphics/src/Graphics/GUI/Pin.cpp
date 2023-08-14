//
// Created by Monika on 18.01.2022.
//

#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/Utils.h>

namespace SR_GRAPH_NS::GUI {
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
    { }

    Pin::~Pin() {
        for (auto&& pLink : m_links) {
            pLink->Broke(this);
        }
        m_node = nullptr;
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

    bool Pin::IsLinked(Pin* pPin) const {
        for (auto&& pLink : m_links) {
            if (pLink->IsLinked(pPin)) {
                return true;
            }
        }

        return false;
    }

    bool Pin::IsLinked() const {
        return !m_links.empty();
    }

    void Pin::Begin(PinKind kind) const {
        switch (kind) {
            case PinKind::None:
                break;
            case PinKind::Output:
                ax::NodeEditor::BeginPin(GetId(), ax::NodeEditor::PinKind::Output);
                break;
            case PinKind::Input:
                ax::NodeEditor::BeginPin(GetId(), ax::NodeEditor::PinKind::Input);
                break;
        }
    }

    void Pin::End() const {
        ax::NodeEditor::EndPin();
    }

    void Pin::DrawPinIcon(bool connected, uint32_t alpha) {
        IconType iconType = GetIconType(GetType());
        ImColor color = GetIconColor(GetType());
        color.Value.w = alpha / 255.0f;

        const float_t pinIconSize = 24.f;

        SR_GRAPH_NS::GUI::Icon(ImVec2(pinIconSize, pinIconSize), iconType, connected, color, ImColor(32, 32, 32, alpha));
    }

    void Pin::DrawOption() {
        switch (GetType()) {
            case PinType::Bool:
                CheckboxNoNavFocus(SR_FORMAT_C("##Pin-%p", (void*)this), &m_constValue.m_bool);
                break;
            case PinType::Int:
                ImGui::InputInt(SR_FORMAT_C("##Pin-%p", (void*)this), &m_constValue.m_int);
                break;
            case PinType::Float:
                ImGui::InputFloat(SR_FORMAT_C("##Pin-%p", (void*)this), &m_constValue.m_float);
                break;
            case PinType::String:
                ImGui::InputText(SR_FORMAT_C("##Pin-%p", (void*)this), &m_constValue.m_string);
                break;
            default:
                break;
        }
    }
}