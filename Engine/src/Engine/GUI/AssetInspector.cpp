//
// Created by Monika on 12.07.2025.
//

#include <Engine/GUI/AssetInspector.h>
#include <Engine/GUI/EditorGUI.h>

#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Reflection/Value.h>

#include <Codegen/AssetInspector.generated.hpp>

namespace SR_CORE_GUI_NS {
    AssetInspector::AssetInspector()
        : SR_GRAPH_GUI_NS::Widget("Asset inspector")
    {
        m_pPointerDrawer = SR_CORE_GUI_NS::PropertyDrawerBase::MakeShared<PointerPropertyDrawer>();
        SetDefaultSize(SR_MATH_NS::IVector2(600, 800));
    }

    AssetInspector::~AssetInspector() {
        if (m_pAsset) {
            m_pAsset->RemoveUsePoint();
            m_pAsset.Reset();
        }
    }

    void AssetInspector::Update(float_t dt) {
        Super::Update(dt);
    }

    void AssetInspector::Draw() {
        if (!m_pAsset) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "No asset selected");
            return;
        }

        auto&& windowsWidth = SR_IMMEDIATE_GUI_NS::GetWindowSize().x;

        auto&& path = m_pAsset->GetResourcePath();
        SR_IMMEDIATE_GUI_NS::Text("Asset: %s", path.c_str());
        SR_IMMEDIATE_GUI_NS::Text("Type: %s", m_pAsset->GetMeta()->GetFactoryName().c_str());

        if (SR_IMMEDIATE_GUI_NS::Button("Save", SR_MATH_NS::FVector2(windowsWidth / 2.f, 0.f))) {
            if (!m_pAsset->SaveAsset()) {
                SR_ERROR("AssetInspector::Draw() : failed to save asset at path: {}", path.ToString());
            }
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (SR_IMMEDIATE_GUI_NS::Button("Discard", SR_MATH_NS::FVector2(windowsWidth / 2.f, 0.f))) {
            if (!m_pAsset->Reload()) {
                SR_ERROR("AssetInspector::Draw() : failed to reload asset at path: {}", path.ToString());
            }
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        auto&& value = SR_UTILS_NS::Reflection::Value::CreateRef(m_pAsset);
        auto&& context = CreateDrawerContext(&value);

        context.fieldWidth += context.fieldTitleWidth;
        context.fieldTitleWidth = 0.f;
        context.noHeader = true;
        context.openedByDefault = true;
        context.editorPropertyParams.SetNotNull();
        m_pPointerDrawer->Draw(context);

        if (SR_IMMEDIATE_GUI_NS::GetScrollMaxY() > 0) {
            m_scrollBarWidth = SR_IMMEDIATE_GUI_NS::GetScrollbarSize();
        }
        else {
            m_scrollBarWidth = 0;
        }
    }

    void AssetInspector::Inspect(const SR_UTILS_NS::Path& path) {
        SR_LOG("AssetInspector::Inspect() : inspecting asset at path: {}", path.ToString());

        Open();
        Focus();

        if (m_pAsset) {
            m_pAsset->RemoveUsePoint();
            m_pAsset.Reset();
        }

        m_pAsset = SR_UTILS_NS::Asset::Load(path);
        if (!m_pAsset) {
            SR_ERROR("AssetInspector::Inspect() : asset not found at path: {}", path.ToString());
            return;
        }

        m_pAsset->AddUsePoint();
    }

    PropertyDrawerContext AssetInspector::CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue) {
        PropertyDrawerContext context(pValue);
        context.pEditor = dynamic_cast<EditorGUI*>(GetManager());

        const float_t lineHeight = SR_IMMEDIATE_GUI_NS::GetFontSize() + SR_IMMEDIATE_GUI_NS::GetFramePadding().y * 2.0f;
        float_t windowWidth = SR_IMMEDIATE_GUI_NS::GetWindowSize().x - m_scrollBarWidth;
        context.lineHeight = lineHeight;
        context.axisButtonWidth = context.lineHeight;
        context.spaceWidth = windowWidth;
        context.fieldHeight = lineHeight;
        context.fieldTitleWidth = windowWidth * 0.3f;
        context.fieldWidth = windowWidth * 0.7f;
        context.noHeader = true;
        context.editorPropertyParams.SetDragSpeed(0.1f);
        context.onBeforeChangeCallback = m_onBeforeChangeCallback;

        return context;
    }

    void AssetInspector::Close() {
        if (m_pAsset) {
            m_pAsset->RemoveUsePoint();
            m_pAsset.Reset();
        }
        Super::Close();
    }
}