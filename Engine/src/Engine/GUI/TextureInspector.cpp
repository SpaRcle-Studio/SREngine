//
// Created by Monika on 08.12.2025.
//

#include <Engine/GUI/TextureInspector.h>
#include <Engine/GUI/EditorGUI.h>

#include <Graphics/Render/RenderContext.h>
#include <Graphics/Overlay/Overlay.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Serialization/SRASerialization.h>
#include <Utils/Reflection/Value.h>

#include <Codegen/TextureInspector.generated.hpp>

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
                SR_UTILS_NS::ResourceManager::Instance().ReloadResource(SR_UTILS_NS::StringAtom(path.View()), SR_GTYPES_NS::Texture::GetClassStaticName());
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
            auto&& pDescriptor = GetManager()->GetContext()->GetPipeline()->GetOverlay(SR_GRAPH_NS::OverlayType::ImGui)->GetTextureDescriptorSet(textureId);
            const auto imageWidth = static_cast<float_t>(m_texture->GetWidth());
            const auto imageHeight = static_cast<float_t>(m_texture->GetHeight());
            if (imageWidth > 0.f && imageHeight > 0.f && windowWidth > 0.f) {
                const float_t aspectRatio = imageWidth / imageHeight;
                const float_t displayWidth = std::max(windowWidth, std::min(windowWidth, imageHeight));
                const float_t displayHeight = displayWidth / aspectRatio;

                SR_IMMEDIATE_GUI_NS::DrawTexture(pDescriptor, SR_MATH_NS::FVector2(displayWidth, displayHeight), false);

                auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList();
                auto&& borders = m_texture->GetImageMetaInfo().GetBorder();

                SR_MATH_NS::FVector2 imageMin  = SR_GRAPH_GUI_NS::Immediate::GetItemRectMin();
                SR_MATH_NS::FVector2 imageMax = SR_GRAPH_GUI_NS::Immediate::GetItemRectMax();

                const float_t width  = imageMax.x - imageMin.x;
                const float_t height = imageMax.y - imageMin.y;

                const float_t scaleX = width  / imageWidth;
                const float_t scaleY = height / imageHeight;

                const float_t left   = borders.left   * scaleX;
                const float_t top    = borders.top    * scaleY;
                const float_t right  = borders.right  * scaleX;
                const float_t bottom = borders.bottom * scaleY;

                const auto color = SR_COL32(255, 255, 0, 255);
                const float_t thickness = 2.f;

                /// Левая граница
                SR_IMMEDIATE_GUI_NS::DrawListAddLine(pDrawList, SR_MATH_NS::FVector2(imageMin.x + left, imageMin.y), SR_MATH_NS::FVector2(imageMin.x + left, imageMax.y), color, thickness);

                /// Верхняя граница
                SR_IMMEDIATE_GUI_NS::DrawListAddLine(pDrawList, SR_MATH_NS::FVector2(imageMin.x, imageMin.y + top), SR_MATH_NS::FVector2(imageMax.x, imageMin.y + top), color, thickness);

                /// Правая граница
                SR_IMMEDIATE_GUI_NS::DrawListAddLine(pDrawList, SR_MATH_NS::FVector2(imageMax.x - right, imageMin.y), SR_MATH_NS::FVector2(imageMax.x - right, imageMax.y), color, thickness);

                /// Нижняя граница
                SR_IMMEDIATE_GUI_NS::DrawListAddLine(pDrawList, SR_MATH_NS::FVector2(imageMin.x, imageMax.y - bottom), SR_MATH_NS::FVector2(imageMax.x, imageMax.y - bottom), color, thickness);
            }
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