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

        SR_UTILS_NS::Reflection::Value value = context.HasExplicitSetter() ? context.GetValue().Copy() : context.GetValue();
        SR_UTILS_NS::SRClass* pClassValue = value.GetSRClass();

        auto&& editorParams = context.GetEditorParams();

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().ToCStr());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        auto&& pWindow = SR_IMMEDIATE_GUI_NS::GetCurrentWindow();
        auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_IMMEDIATE_GUI_NS::GetWindowCursorPos(pWindow);

        const auto dir = m_isOpened ? SR_IMMEDIATE_GUI_NS::Direction::Down : SR_IMMEDIATE_GUI_NS::Direction::Right;

        const SR_UTILS_NS::StringView typeName = value.GetTypeInfo().pNext[0] ? SR_UTILS_NS::StringView(value.GetTypeInfo().pNext[0]->detailedType.ToStringView()) : SR_UTILS_NS::StringView();

        if (!m_openedByDefault) {
            m_isOpened |= context.openedByDefault;
            m_openedByDefault = true;
        }

        m_isOpened |= context.noHeader;

        if (context.pValue && !context.noHeader) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { 30, context.fieldHeight };

            auto&& stackSize = SR_IMMEDIATE_GUI_NS::BeginForceEnabled();
            if (SR_IMMEDIATE_GUI_NS::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_IMMEDIATE_GUI_NS::EndForceEnabled(stackSize);
        }
        else if (!context.noHeader) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(1, 5);
            SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), dir, 1.f);

            //const float_t arrowWidth = context.lineHeight * 0.75f;
            //SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(arrowWidth, 0));

            //SR_IMMEDIATE_GUI_NS::SameLine();

            //const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - arrowWidth, 0), context.fieldHeight };
            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth, 0), context.fieldHeight };

            SR_UTILS_NS::StringAtom displayName = context.GetPropertyDisplayName();
            auto&& stackSize = SR_IMMEDIATE_GUI_NS::BeginForceEnabled();
            if (SR_IMMEDIATE_GUI_NS::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_IMMEDIATE_GUI_NS::EndForceEnabled(stackSize);
        }

        SR_HTYPES_NS::SharedPtrBase* pSharedPtrBase = value.GetSharedPtrBase();
        if (!pSharedPtrBase) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "PointerPropertyDrawer::Draw() : value is not a smart pointer!");
            SR_IMMEDIATE_GUI_NS::PopStyleVar();
            SR_IMMEDIATE_GUI_NS::PopID();
            SR_IMMEDIATE_GUI_NS::PopID();
            return feedback;
        }

        if (!context.noHeader) {
            SR_IMMEDIATE_GUI_NS::SameLine();

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

            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth);

            if (m_typeNames.size() < 1) {
                SR_IMMEDIATE_GUI_NS::BeginDisabled();
            }

            if (SR_IMMEDIATE_GUI_NS::BeginCombo("##Combo", pPrevValue, SR_IMMEDIATE_GUI_NS::ComboFlags::NoArrowButton)) {
                if (!m_comboOpened) {
                    SR_IMMEDIATE_GUI_NS::SetKeyboardFocusHere();
                    m_comboOpened = true;
                }

                if (SR_IMMEDIATE_GUI_NS::InputText("##Search", &m_searchBuffer)) {
                    SR_NOOP;
                }

                for (uint64_t i = 0; i < m_typeNames.size(); ++i) {
                    if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, m_typeNames[i])) {
                        continue;
                    }

                    bool isSelected = (selectedIndex == i);
                    if (SR_IMMEDIATE_GUI_NS::Selectable(m_typeNames[i].data(), isSelected))
                    {
                        selectedIndex = i;
                        m_searchBuffer = m_typeNames[i];
                        SR_IMMEDIATE_GUI_NS::CloseCurrentPopup();
                    }

                    if (isSelected) {
                        SR_IMMEDIATE_GUI_NS::SetItemDefaultFocus();
                    }
                }
                SR_IMMEDIATE_GUI_NS::EndCombo();
            }
            else {
                m_comboOpened = false;
                m_searchBuffer.clear();
            }

            if (m_typeNames.size() < 1) {
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            }

            if (SR_IMMEDIATE_GUI_NS::BeginPopupContextItem("PointerPropertyContextMenu")) {
                auto&& pSerializable = dynamic_cast<SR_UTILS_NS::Serializable*>(pClassValue);

                static const SR_UTILS_NS::SerializationId serializeId = SR_UTILS_NS::SerializationId::Create("PointerPropertyDrawerClipboard");

                CustomContextMenu(context, pClassValue);

                if (pSerializable && SR_IMMEDIATE_GUI_NS::MenuItem("Copy")) {
                    SR_UTILS_NS::SRASerializer serializer;

                    serializer.BeginObject(serializeId);

                    SR_UTILS_NS::Serialization::Save(serializer, pSerializable->GetMeta()->GetFactoryName(), SR_UTILS_NS::SerializationId::Create("type"));
                    SR_UTILS_NS::Serialization::Save(serializer, *pSerializable, SR_UTILS_NS::SerializationId::Create("data"));

                    serializer.EndObject();

                    SR_UTILS_NS::String encoded;
                    SR_UTILS_NS::StringUtils::Instance().Base64Encode(serializer.ToString(), encoded);
                    SR_PLATFORM_NS::TextToClipboard(serializeId.ToString() + encoded);
                }

                if (auto&& clipboard = SR_PLATFORM_NS::GetClipboardText(); clipboard.starts_with(serializeId.GetName())) {
                    if (SR_IMMEDIATE_GUI_NS::MenuItem("Paste (replace)")) {
                        clipboard.erase(0, strlen(serializeId.GetName()));
                        SR_UTILS_NS::SRADeserializer deserializer;
                        SR_UTILS_NS::String decoded;
                        SR_UTILS_NS::StringUtils::Instance().Base64Decode(clipboard, decoded);
                        if (deserializer.LoadFromString(decoded)) {
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

                SR_IMMEDIATE_GUI_NS::EndPopup();
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();

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

        if (!pClassValue && context.noHeader) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "PointerPropertyDrawer::Draw() : value is nullptr!");
        }
        else if (m_isOpened && pClassValue) {
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
                SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(context.GetArrowWidth(), 5.0f));
                SR_IMMEDIATE_GUI_NS::SameLine();
            }

            PropertyDrawerContext propertyContext = context;

            SR_UTILS_NS::Reflection::TypeInfo* pTypeInfo = SR_UTILS_NS::Reflection::DetermineTypeInfoAlloc(*pClassValue);
            pTypeInfo->detailedType = value.GetTypeInfo().pNext[0]->detailedType;
            SRAssert(pTypeInfo->category != SR_UTILS_NS::Reflection::ReflectedCategoryType::Unknown);

            auto&& valueRef = SR_UTILS_NS::Reflection::Value::CreateRef(*pClassValue, pTypeInfo);

            propertyContext.pValue = &valueRef;
            float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth);
            totalWidth -= ((!context.pValue && !context.noHeader) ? context.GetArrowWidth() : 0.f);
            propertyContext.fieldWidth = totalWidth * 0.7f;
            propertyContext.fieldTitleWidth = totalWidth * 0.3f;
            propertyContext.pProperty = nullptr;
            propertyContext.pOwner = pClassValue;
            propertyContext.noHeader = true;

            SR_IMMEDIATE_GUI_NS::BeginGroup();
            PropertyDrawerFeedback propertyFeedback = m_objectDrawer->Draw(propertyContext);
            SR_IMMEDIATE_GUI_NS::EndGroup();

            if (propertyFeedback.isChanged) {
                feedback.isChanged = true;
            }
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }
}
