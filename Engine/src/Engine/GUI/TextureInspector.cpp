//
// Created by Monika on 08.12.2025.
//

#include <Engine/GUI/TextureInspector.h>
#include <Engine/GUI/EditorGUI.h>

#include <Graphics/Render/RenderContext.h>

#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Serialization/SRASerialization.h>
#include <Utils/Reflection/Value.h>

namespace SR_CORE_GUI_NS {
    TextureInspector::TextureInspector()
        : SR_GRAPH_GUI_NS::Widget("Texture inspector")
    {
        m_drawer = SR_CORE_GUI_NS::PropertyDrawerBase::MakeShared<ObjectPropertyDrawer>();
        SetDefaultSize(SR_MATH_NS::IVector2(600, 800));
    }

    TextureInspector::~TextureInspector() {
        if (m_texture) {
            m_texture->RemoveUsePoint();
            m_texture.Reset();
        }
    }

    void TextureInspector::Draw() {
        if (!m_texture) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "No texture selected");
            return;
        }

        if (!m_texture->CanBeUsed()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f), "Texture still loading...");
            return;
        }

        m_imageMetaInfo = m_texture->GetImageMetaInfo();

        auto&& windowsWidth = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x;

        auto&& path = m_texture->GetResourcePath();
        SR_GRAPH_GUI_NS::Immediate::Text("Texture: %s", path.c_str());

        if (SR_GRAPH_GUI_NS::Immediate::Button("Save", SR_MATH_NS::FVector2(windowsWidth / 2.f, 0.f))) {
            SR_UTILS_NS::SRASerializer serializer;
            serializer.SetUseTabs(true);
            m_imageMetaInfo.Save(serializer);
            const auto metaPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path).ConcatExt(".meta");
            if (serializer.SaveToFile(metaPath)) {
                m_originalImageMetaInfo = m_imageMetaInfo;
                SR_LOG("TextureInspector::Draw() : saved meta info for texture at path: {}", metaPath);
            }
            else {
                SR_ERROR("TextureInspector::Draw() : failed to save meta info for texture at path: {}", metaPath);
            }
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (SR_GRAPH_GUI_NS::Immediate::Button("Discard", SR_MATH_NS::FVector2(windowsWidth / 2.f, 0.f))) {
            m_imageMetaInfo = m_originalImageMetaInfo;
            m_texture->SetImageMetaInfo(m_imageMetaInfo);
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        const float_t windowWidth = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x - m_scrollBarWidth - 10.f;
        if (const int32_t textureId = m_texture->GetId(); textureId != SR_ID_INVALID) {
            SR_GRAPH_GUI_NS::Immediate::DrawTexture(GetManager()->GetContext()->GetPipeline().Get(), textureId, windowWidth, false);
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        auto&& value = SR_UTILS_NS::Reflection::Value::CreateRef(m_imageMetaInfo);
        auto&& context = CreateDrawerContext(&value);

        context.fieldWidth += context.fieldTitleWidth;
        context.fieldTitleWidth = 0.f;
        context.noHeader = true;
        context.openedByDefault = true;
        context.editorPropertyParams.SetNotNull();
        m_drawer->Draw(context);

        m_texture->SetImageMetaInfo(m_imageMetaInfo);

        if (SR_GRAPH_GUI_NS::Immediate::GetScrollMaxY() > 0) {
            m_scrollBarWidth = SR_GRAPH_GUI_NS::Immediate::GetScrollbarSize();
        }
        else {
            m_scrollBarWidth = 0;
        }
    }

    void TextureInspector::Inspect(const SR_UTILS_NS::Path& path) {
        SR_LOG("TextureInspector::Inspect() : inspecting asset at path: {}", path.ToString());

        Open();
        Focus();

        if (m_texture) {
            m_texture->RemoveUsePoint();
            m_texture.Reset();
        }

        m_texture = CoreResLoader::Load<SR_GTYPES_NS::Texture>(path);
        if (!m_texture) {
            SR_ERROR("TextureInspector::Inspect() : texture not found at path: {}", path.ToString());
            return;
        }

        m_texture->AddUsePoint();
        m_originalImageMetaInfo = m_texture->GetImageMetaInfo();
    }

    PropertyDrawerContext TextureInspector::CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue) {
        PropertyDrawerContext context(pValue);
        context.pEditor = dynamic_cast<EditorGUI*>(GetManager());

        const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFontSize() + SR_GRAPH_GUI_NS::Immediate::GetFramePadding().y * 2.0f;
        float_t windowWidth = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x - m_scrollBarWidth;
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

    void TextureInspector::Close() {
        if (m_texture) {
            m_texture->RemoveUsePoint();
            m_texture.Reset();
        }
        Super::Close();
    }
}