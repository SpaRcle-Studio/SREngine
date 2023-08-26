//
// Created by Monika on 18.01.2022.
//

#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/Utils.h>
#include <Utils/SRLM/DataType.h>

namespace SR_GRAPH_GUI_NS {
    Pin::Pin()
        : Pin(std::string(), PinKind::None, nullptr)
    { }

    Pin::Pin(const std::string& name)
        : Pin(name, PinKind::None, nullptr)
    { }

    Pin::Pin(const std::string& name, PinKind kind)
        : Pin(name, kind, nullptr)
    { }


    Pin::Pin(const std::string& name, Pin::DataTypePtr pData)
        : Pin(name, PinKind::None, pData)
    { }

    Pin::Pin(const std::string& name, PinKind kind, DataTypePtr pDataType)
        : m_name(name)
        , m_kind(kind)
        , m_dataType(pDataType)
        , m_constValue(pDataType ? pDataType->Copy() : nullptr)
    { }

    Pin::~Pin() {
        SR_SAFE_DELETE_PTR(m_constValue);
        SR_SAFE_DELETE_PTR(m_dataType);

        for (auto&& pLink : m_links) {
            pLink->Broke(this);
        }

        m_node = nullptr;
    }

    ImColor Pin::GetIconColor(const PinType& type) {
        switch (type) {
            case PinType::Flow:   return ImColor(255, 255, 255);
            case PinType::Bool:   return ImColor(220,  48,  48);
            case PinType::Float:  return ImColor(147, 226,  74);
            case PinType::String: return ImColor(124,  21, 153);
            case PinType::Int8:
            case PinType::Int16:
            case PinType::Int32:
            case PinType::Int64:
            case PinType::UInt8:
            case PinType::UInt16:
            case PinType::UInt32:
            case PinType::UInt64:
                return ImColor(68, 201, 156);
            case PinType::Struct:
                return ImColor(51, 150, 215);
            case PinType::Enum:
                return ImColor(255, 48,  48);
            case PinType::Array:
                return ImColor(218, 0, 183);
                /// case PinType::Numeric:  return ImColor( 68, 101, 056);
            /// case PinType::Object:   return ImColor( 51, 150, 215);
            /// case PinType::Function: return ImColor(218,   0, 183);
            /// case PinType::Delegate: return ImColor(255,  48,  48);
            /// case PinType::Event:    return ImColor(255,  48,  48);
            default:
                SRHalt("Unknown icon type!");
                return ImColor(0, 0, 0);
        }
    }

    IconType Pin::GetIconType(const PinType &type) {
        switch (type) {
            case PinType::Flow: return IconType::Flow;
            case PinType::Bool: return IconType::Circle;
            case PinType::Int8:
            case PinType::Int16:
            case PinType::Int32:
            case PinType::Int64:
            case PinType::UInt8:
            case PinType::UInt16:
            case PinType::UInt32:
            case PinType::UInt64:
                return IconType::Circle;
            case PinType::Float:  return IconType::Circle;
            case PinType::String: return IconType::Circle;
            case PinType::Struct: return IconType::Square;
            /// case PinType::Numeric:  return IconType::Circle;
            /// case PinType::Object:   return IconType::Circle;
            /// case PinType::Function: return IconType::Circle;
            /// case PinType::Delegate: return IconType::Square;
            /// case PinType::Event:    return IconType::Square;
            case PinType::Enum: return IconType::Circle;
            case PinType::Array: return IconType::Grid;
            default:
                SRHalt("Unknown icon type!");
                return IconType::Square;
        }
    }

    Pin* Pin::Copy() const {
        auto&& pPin = new Pin();

        pPin->m_name = m_name;
        pPin->m_kind = m_kind;

        if (m_dataType) {
            pPin->m_dataType = m_dataType->Copy();
        }

        if (m_constValue) {
            pPin->m_constValue = m_constValue->Copy();
        }

        return pPin;
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

    bool Pin::CanLink() const {
        if (!GetNode()) {
            return false;
        }

        if (IsLinked()) {
            if (GetType() == PinType::Flow && GetKind() == PinKind::Output) {
                return false;
            }
            else if (GetType() != PinType::Flow && GetKind() == PinKind::Input) {
                return false;
            }
        }

        if (GetNode()->IsDot() && IsLinked()) {
            if (GetKind() == PinKind::Input) {
                return false;
            }
        }

        return true;
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
        if (!m_constValue) {
            return;
        }

        switch (GetType()) {
            case PinType::Bool:
                CheckboxNoNavFocus(SR_FORMAT_C("##Pin-%p", (void*)this), m_constValue->GetBool());
                break;
            case PinType::Int8:
            case PinType::Int16:
            case PinType::Int32:
            case PinType::Int64:
            case PinType::UInt8:
            case PinType::UInt16:
            case PinType::UInt32:
            case PinType::UInt64: {
                int32_t number = *m_constValue->GetInt32();
                ImGui::PushItemWidth(40.0f);
                ImGui::InputInt(SR_FORMAT_C("##Pin-%p", (void*)this), &number, 0);
                *m_constValue->GetInt32() = number;
                ImGui::PopItemWidth();
                break;
            }
            case PinType::Float:
                ImGui::PushItemWidth(40.0f);
                ImGui::InputFloat(SR_FORMAT_C("##Pin-%p", (void*)this), m_constValue->GetFloat());
                ImGui::PopItemWidth();
                break;
            case PinType::String:
                ImGui::InputText(SR_FORMAT_C("##Pin-%p", (void*)this), m_constValue->GetString());
                break;
            default:
                break;
        }
    }

    Pin::PinType Pin::GetType() const {
        return m_dataType ? m_dataType->GetClass() : PinType::None;
    }
}