//
// Created by Monika on 03.02.2025.
//

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/PointerPropertyDrawer.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Utils/Serialization/SRASerialization.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/Platform/Platform.h>

#include <Codegen/PointerPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback PointerPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.HasExplicitSetter() ? context.GetValue().Detach() : context.GetValue();
        SR_UTILS_NS::SRClass* pClassValue = value.GetSRClass();

        auto&& editorParams = context.GetEditorParams();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().ToCStr());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        auto&& pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
        auto&& pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow);

        const auto dir = m_isOpened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;

        std::string_view typeName = value.GetSharedPtrType();
        if (size_t pos = typeName.rfind(':'); pos != std::string_view::npos) {
            typeName.remove_prefix(pos + 1);
        }

        if (!m_openedByDefault) {
            m_isOpened |= context.openedByDefault;
            m_openedByDefault = true;
        }

        m_isOpened |= context.noHeader;

        if (context.pValue && !context.noHeader) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { 30, context.fieldHeight };

            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }
        else if (!context.noHeader) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(1, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            //const float_t arrowWidth = context.lineHeight * 0.75f;
            //SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(arrowWidth, 0));

            //SR_GRAPH_GUI_NS::Immediate::SameLine();

            //const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - arrowWidth, 0), context.fieldHeight };
            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth, 0), context.fieldHeight };

            SR_UTILS_NS::StringAtom displayName = context.GetPropertyDisplayName();
            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }

        SR_HTYPES_NS::SharedPtrBase* pSharedPtrBase = value.GetSharedPtrBase();
        SRAssert(pSharedPtrBase);

        if (!context.noHeader) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();

            if (m_default.empty()) {
                m_default = "{} (nullptr)"_format(typeName);
            }

            if (m_typeNames.empty()) {
                if (!editorParams.IsNotNull()) {
                    m_typeNames.emplace_back("(nullptr)");
                }

                auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(typeName);
                if (pMeta && !pMeta->IsAbstract()) {
                    m_typeNames.emplace_back(pMeta->GetFactoryName());
                }

                for (auto&& type : SR_UTILS_NS::Factory::Instance().GetInheritances(typeName)) {
                    m_typeNames.emplace_back(type);
                }
            }

            std::vector<SR_UTILS_NS::StringAtom>::iterator pTypeNameIt = m_typeNames.end();

            if (pClassValue) {
                const SR_UTILS_NS::SRClassMeta* pMeta = pClassValue->GetMeta();
                SRAssert(pMeta);
                const SR_UTILS_NS::StringAtom factoryName = pMeta->GetFactoryName();
                pTypeNameIt = std::find(m_typeNames.begin(), m_typeNames.end(), factoryName);
            }

            std::optional<uint64_t> selectedIndex = pTypeNameIt != m_typeNames.end() ? std::make_optional(std::distance(m_typeNames.begin(), pTypeNameIt)) : std::nullopt;

            const char* pPrevValue = selectedIndex.has_value() ? m_typeNames[selectedIndex.value()].data() : m_default.c_str();

            SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

            if (m_typeNames.size() < 1) {
                SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
            }

            if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("##Combo", pPrevValue, SR_GRAPH_GUI_NS::Immediate::ComboFlags::NoArrowButton)) {
                if (!m_comboOpened) {
                    SR_GRAPH_GUI_NS::Immediate::SetKeyboardFocusHere();
                    m_comboOpened = true;
                }

                if (SR_GRAPH_GUI_NS::Immediate::InputText("##Search", &m_searchBuffer)) {
                    SR_NOOP;
                }

                for (uint64_t i = 0; i < m_typeNames.size(); ++i) {
                    if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, m_typeNames[i])) {
                        continue;
                    }

                    bool isSelected = (selectedIndex == i);
                    if (SR_GRAPH_GUI_NS::Immediate::Selectable(m_typeNames[i].data(), isSelected))
                    {
                        selectedIndex = i;
                        m_searchBuffer = m_typeNames[i];
                        SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                    }

                    if (isSelected) {
                        SR_GRAPH_GUI_NS::Immediate::SetItemDefaultFocus();
                    }
                }
                SR_GRAPH_GUI_NS::Immediate::EndCombo();
            }
            else {
                m_comboOpened = false;
                m_searchBuffer.clear();
            }

            if (m_typeNames.size() < 1) {
                SR_GRAPH_GUI_NS::Immediate::EndDisabled();
            }

            if (SR_GRAPH_GUI_NS::Immediate::BeginPopupContextItem("PointerPropertyContextMenu")) {
                auto&& pSerializable = dynamic_cast<SR_UTILS_NS::Serializable*>(pClassValue);

                static const SR_UTILS_NS::SerializationId serializeId = SR_UTILS_NS::SerializationId::Create("PointerPropertyDrawerClipboard");

                CustomContextMenu(context, pClassValue);

                if (pSerializable && SR_GRAPH_GUI_NS::Immediate::MenuItem("Copy")) {
                    SR_UTILS_NS::SRASerializer serializer;

                    serializer.BeginObject(serializeId);

                    SR_UTILS_NS::Serialization::Save(serializer, pSerializable->GetMeta()->GetFactoryName(), SR_UTILS_NS::SerializationId::Create("type"));
                    SR_UTILS_NS::Serialization::Save(serializer, *pSerializable, SR_UTILS_NS::SerializationId::Create("data"));

                    serializer.EndObject();

                    std::string encoded = SR_UTILS_NS::StringUtils::Base64Encode(serializer.ToString());
                    SR_PLATFORM_NS::TextToClipboard(serializeId.ToString() + encoded);
                }

                if (auto&& clipboard = SR_PLATFORM_NS::GetClipboardText(); clipboard.starts_with(serializeId.GetName())) {
                    if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Paste (replace)")) {
                        clipboard.erase(0, strlen(serializeId.GetName()));
                        SR_UTILS_NS::SRADeserializer deserializer;
                        if (deserializer.LoadFromString(SR_UTILS_NS::StringUtils::Base64Decode(clipboard))) {
                            if (deserializer.BeginObject(serializeId)) {
                                SR_UTILS_NS::StringAtom loadTypeName;
                                if (SR_UTILS_NS::Serialization::Load(deserializer, loadTypeName, SR_UTILS_NS::SerializationId::Create("type"))) {
                                    if (std::ranges::find(m_typeNames, loadTypeName) != m_typeNames.end()) {
                                        SR_UTILS_NS::SRClass* pNewValue = SR_UTILS_NS::Factory::Instance().CreateBase(loadTypeName);
                                        if (pNewValue && SR_UTILS_NS::Serialization::Load(deserializer, *dynamic_cast<SR_UTILS_NS::Serializable*>(pNewValue), SR_UTILS_NS::SerializationId::Create("data"))) {
                                            if (context.onBeforeChangeCallback) {
                                                context.onBeforeChangeCallback(false);
                                            }
                                            OnObjectReplaced(pClassValue, pNewValue);
                                            if (pSharedPtrBase) {
                                                pSharedPtrBase->SetPointerFromBase(dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(pNewValue));
                                            }
                                            feedback.isChanged = true;
                                            pClassValue = value.GetSRClass();
                                        }
                                    }
                                    else {
                                        SR_WARN("PointerPropertyDrawer::Draw() : type \"{}\" not compatible with current property drawer!", loadTypeName);
                                    }
                                }
                                deserializer.EndObject();
                            }
                        }
                    }
                }

                SR_GRAPH_GUI_NS::Immediate::EndPopup();
            }

            SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

            if (selectedIndex && !feedback.isChanged) {
                SRClass* pNew = nullptr;

                if (m_typeNames[selectedIndex.value()] == "(nullptr)") {
                    if (context.onBeforeChangeCallback) {
                        context.onBeforeChangeCallback(false);
                    }
                    OnObjectReplaced(pClassValue, nullptr);
                    pNew = nullptr;
                    feedback.isChanged = true;
                }
                else if (pClassValue) {
                    if (m_typeNames[selectedIndex.value()] != pClassValue->GetMeta()->GetFactoryName()) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        pNew = SR_UTILS_NS::Factory::Instance().CreateBase(m_typeNames[selectedIndex.value()]);
                        OnObjectReplaced(pClassValue, pNew);
                        feedback.isChanged = true;
                    }
                }
                else {
                    if (context.onBeforeChangeCallback) {
                        context.onBeforeChangeCallback(false);
                    }
                    pNew = SR_UTILS_NS::Factory::Instance().CreateBase(m_typeNames[selectedIndex.value()]);
                    OnObjectReplaced(pClassValue, pNew);
                    feedback.isChanged = true;
                }

                if (feedback.isChanged && pSharedPtrBase) {
                    pSharedPtrBase->SetPointerFromBase(dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(pNew));
                }

                pClassValue = value.GetSRClass();
            }
        }

        if (m_isOpened && pClassValue) {
            const SR_UTILS_NS::StringAtom factoryName = pClassValue->GetMeta()->GetFactoryName();
            if (m_lastTypeName != factoryName) {
                m_lastTypeName = factoryName;

                if (auto&& inspectorName = pClassValue->GetMeta()->GetInspectorName(); !inspectorName.empty()) {
                    m_objectDrawer = SR_UTILS_NS::Factory::Instance().Create<ObjectPropertyDrawer>(inspectorName);
                }
                if (!m_objectDrawer) {
                    m_objectDrawer = SRNew<ObjectPropertyDrawer>();
                }
            }

            if (!context.pValue && !context.noHeader) {
                SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.GetArrowWidth(), 5.0f));
                SR_GRAPH_GUI_NS::Immediate::SameLine();
            }

            PropertyDrawerContext propertyContext = context;
            auto&& valueRef = SR_UTILS_NS::Reflection::Value::CreateRef(*pClassValue);
            propertyContext.pValue = &valueRef;
            float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth);
            totalWidth -= ((!context.pValue && !context.noHeader) ? context.GetArrowWidth() : 0.f);
            propertyContext.fieldWidth = totalWidth * 0.7f;
            propertyContext.fieldTitleWidth = totalWidth * 0.3f;
            propertyContext.pProperty = nullptr;
            propertyContext.pOwner = pClassValue;
            //propertyContext.pUID = value.IsRef() ? pClassValue : (static_cast<void*>(static_cast<uint64_t*>(propertyContext.pUID) + 1));
            propertyContext.noHeader = true;

            SR_GRAPH_GUI_NS::Immediate::BeginGroup();
            PropertyDrawerFeedback propertyFeedback = m_objectDrawer->Draw(propertyContext);
            SR_GRAPH_GUI_NS::Immediate::EndGroup();

            if (propertyFeedback.isChanged) {
                feedback.isChanged = true;
            }
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        SetValue(context, feedback, value);

        //if (!context.noHeader && m_isOpened) {
        //    SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(0, context.fieldHeight / 2.f));
        //}

        return feedback;
    }
}
