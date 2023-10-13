//
// Created by Monika on 18.01.2022.
//

#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/Utils.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/Platform/Platform.h>

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
    { }

    Pin::~Pin() {
        /// Будет удалено в управляющей ноде
        /// SR_SAFE_DELETE_PTR(m_dataType);

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
            else if (GetType() == PinType::Flow && GetKind() == PinKind::Input) {
                auto&& pSynchronize = dynamic_cast<SR_SRLM_NS::SynchronizeNode*>(GetNode()->GetLogicalNode());
                if (pSynchronize) {
                    return false;
                }
            }
        }

        if (GetNode()->IsConnector() && IsLinked() && GetType() != SR_SRLM_NS::DataTypeClass::Flow) {
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
            default:
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

    void Pin::PostDrawOption() {
        if (m_editEnum) {
            ImGui::OpenPopup(SR_FORMAT_C("pin_enum_popup%p", (void*)this));
            m_editEnum = false;
        }

        switch (GetType()) {
            case PinType::Enum: {
                auto&& pEnum = dynamic_cast<SR_SRLM_NS::DataTypeEnum*>(m_dataType);
                if (!pEnum) {
                    break;
                }

                auto&& pReflector = pEnum->GetReflector();
                if (!pReflector) {
                    break;
                }

                auto&& enumValue = pReflector->ToStringInternal(*pEnum->GetEnum());

                if (ImGui::BeginPopup(SR_FORMAT_C("pin_enum_popup%p", (void*)this))) {
                    ImGui::TextDisabled("Select:");
                    ImGui::BeginChild("pin_enum_popup_scrollbar", ImVec2(100, 300), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
                    for (auto&& selectable : pReflector->GetNamesInternal()) {
                        if (ImGui::Button(selectable.c_str(), ImVec2(100, 20))) {
                            if (auto&& enumNewValue = pReflector->FromStringInternal(selectable)) {
                                pEnum->SetValue(enumNewValue.value());
                            }
                            ImGui::CloseCurrentPopup();
                        }
                    }
                    ImGui::PopStyleVar();
                    ImGui::EndChild();
                    ImGui::EndPopup();
                }

                break;
            }
            default:
                break;
        }
    }

    void Pin::DrawOption() {
        SR_GRAPH_GUI_NS::DrawDataType(m_dataType, &m_editEnum, (void*)this);
    }

    Pin::PinType Pin::GetType() const {
        return m_dataType ? m_dataType->GetClass() : PinType::None;
    }

    uint32_t Pin::GetIndex() const {
        if (auto&& index = m_node->GetPinIndex(this); index >= 0) {
            return index;
        }

        SRHalt("Invalid pin!");
        return SR_UINT32_MAX;
    }
}