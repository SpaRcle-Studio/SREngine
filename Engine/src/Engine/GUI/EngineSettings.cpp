//
// Created by Monika on 04.03.2022.
//

#include <Engine/GUI/EngineSettings.h>

#include <Graphics/Lighting/LightSystem.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/Common/StoreUtils.h>
#include <Utils/Events/Broadcaster.h>
#include <Utils/Reflection/Value.h>
#include <Utils/Serialization/SRASerialization.h>

#include <Codegen/EngineSettings.generated.hpp>

namespace SR_CORE_GUI_NS {
    EngineSettings::EngineSettings()
        : SR_GRAPH_NS::GUI::Widget("Settings")
    {
        m_onRenderSettingsChanged = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_RENDER_SETTINGS_CHANGED_ID, [this](auto&&) {
            PrepareRenderPresets();
        });
    }

    EngineSettings::~EngineSettings() {
        m_onRenderSettingsChanged.Reset();
    }

    void EngineSettings::Draw() {
        SR_TRACY_ZONE;

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 0.0f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        DrawEditorSettings();
        SR_IMMEDIATE_GUI_NS::Separator();
        DrawGraphicsSettings();

        if (SR_IMMEDIATE_GUI_NS::GetScrollMaxY() > 0) {
            m_scrollBarWidth = SR_IMMEDIATE_GUI_NS::GetScrollbarSize();
        }
        else {
            m_scrollBarWidth = 0;
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar(2);
    }

    void EngineSettings::DrawGraphicsSettings() {
        SR_TRACY_ZONE;

        SR_IMMEDIATE_GUI_NS::PushID("GraphicsSettings");

        if (!m_graphicsSettingsDrawer) {
            m_graphicsSettingsDrawer = new ObjectPropertyDrawer();
        }

        m_cachedGraphicsSettings = GetContext()->GetActiveGraphicsSettings();
        auto&& value = SR_UTILS_NS::Reflection::Value::CreateRef(m_cachedGraphicsSettings);

        const float_t lineHeight = SR_IMMEDIATE_GUI_NS::GetFontSize() + SR_IMMEDIATE_GUI_NS::GetFramePadding().y * 2.0f;
        float_t windowWidth = SR_IMMEDIATE_GUI_NS::GetWindowSize().x - m_scrollBarWidth;

        if (SR_IMMEDIATE_GUI_NS::Button("Save", { windowWidth * 0.2f, lineHeight })) {
            SR_UTILS_NS::SRASerializer serializer;
            m_cachedGraphicsSettings.Save(serializer);
            auto&& path = SR_PLATFORM_NS::GetApplicationUserDataDirectory()
                .Concat("User")
                .Concat(SR_PLATFORM_NS::GetApplicationInfo().project)
                .Concat("GraphicsSettings.sra");
            if (!serializer.SaveToFile(path)) {
                SR_ERROR("EngineSettings::DrawGraphicsSettings() : failed to save graphics settings to path: {}", path);
            }
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        SR_IMMEDIATE_GUI_NS::BeginDisabled();
        SR_IMMEDIATE_GUI_NS::Button("Graphics settings", { windowWidth * 0.6f, lineHeight });
        SR_IMMEDIATE_GUI_NS::EndDisabled();

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (SR_IMMEDIATE_GUI_NS::Button("Reset", { windowWidth * 0.2f, lineHeight })) {
            GetContext()->ReloadGraphicsSettings();
        }

        PropertyDrawerContext context(&value);
        context.lineHeight = lineHeight;
        context.axisButtonWidth = context.lineHeight;
        context.spaceWidth = windowWidth;
        context.fieldHeight = lineHeight;
        context.fieldTitleWidth = windowWidth * 0.4f;
        context.fieldWidth = windowWidth * 0.6f;
        context.noHeader = true;
        context.editorPropertyParams.SetDragSpeed(0.1f);

        auto&& feedback = m_graphicsSettingsDrawer->Draw(context);
        if (feedback.isChanged) {
            GetContext()->SetGraphicsSettings(m_cachedGraphicsSettings);
        }

        SR_IMMEDIATE_GUI_NS::Text("Swapchain image count changes require saving and restarting.");
        bool optimizedRenderUpdate = GetContext()->IsOptimizedRenderUpdateEnabled();
        if (SR_IMMEDIATE_GUI_NS::Checkbox("Optimized render update", &optimizedRenderUpdate)) {
            GetContext()->SetOptimizedRenderUpdateEnabled(optimizedRenderUpdate);
        }

        SR_IMMEDIATE_GUI_NS::PopID();
    }

    void EngineSettings::DrawEditorSettings() {
        SR_TRACY_ZONE;

        static const SR_UTILS_NS::StringAtom showEntityIdKey = "ShowEntityId";
        static const SR_UTILS_NS::StringAtom editorDebugModeKey = "EditorDebugMode";
        static const SR_UTILS_NS::StringAtom showHiddenEntitiesKey = "ShowHiddenEntities";
        static const SR_UTILS_NS::StringAtom fontSizeKey = "EditorFontSize";

        float_t fontSize = SR_UTILS_NS::StoreUtils::User::GetFloat(fontSizeKey, SR_IMMEDIATE_GUI_NS::DEFAULT_FONT_SIZE);
        bool showEntityId = SR_UTILS_NS::StoreUtils::User::GetBool(showEntityIdKey, false);
        bool showHiddenEntities = SR_UTILS_NS::StoreUtils::User::GetBool(showHiddenEntitiesKey, false);
        bool editorDebugMode = SR_UTILS_NS::StoreUtils::User::GetBool(editorDebugModeKey, false);

        if (SR_IMMEDIATE_GUI_NS::InputFloat("Font size", &fontSize, 1.0f, 1.0f, "%.1f", SR_IMMEDIATE_GUI_NS::InputTextFlags::EnterReturnsTrue)) {
            SR_UTILS_NS::StoreUtils::User::SetFloat(fontSizeKey, fontSize);
        }

        if (SR_IMMEDIATE_GUI_NS::Checkbox("Show entity id", &showEntityId)) {
            SR_UTILS_NS::StoreUtils::User::SetBool(showEntityIdKey, showEntityId);
        }

        if (SR_IMMEDIATE_GUI_NS::Checkbox("Editor debug mode", &editorDebugMode)) {
            SR_UTILS_NS::StoreUtils::User::SetBool(editorDebugModeKey, editorDebugMode);
        }

        if (SR_IMMEDIATE_GUI_NS::Checkbox("Show hidden entities", &showHiddenEntities)) {
            SR_UTILS_NS::StoreUtils::User::SetBool(showHiddenEntitiesKey, showHiddenEntities);
        }

        if (SR_IMMEDIATE_GUI_NS::Combo("Render preset", &m_activeRenderPreset, m_renderPresetsMemory.c_str())) {
            uint32_t index = 0;
            for (auto&& preset : m_renderPresets) {
                if (index == m_activeRenderPreset) {
                    GetContext()->SetActivePreset(preset);
                    break;
                }
                index++;
            }
        }

        if (SR_IMMEDIATE_GUI_NS::Button("Save")) {
            SR_UTILS_NS::StoreUtils::Storage::Instance().Save();
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (SR_IMMEDIATE_GUI_NS::Button("Load")) {
            SR_UTILS_NS::StoreUtils::Storage::Instance().Load();
        }
    }

    void EngineSettings::PrepareRenderPresets() {
        m_renderPresets.clear();
        m_renderPresetsMemory.clear();
        m_activeRenderPreset = 0;

        m_renderPresets.insert("Default");
        m_renderPresets.insert(GetContext()->GetSettings().defaultPreset.name);

        for (auto&& preset : GetContext()->GetSettings().presets) {
            m_renderPresets.insert(preset.name);
        }

        uint32_t index = 0;
        for (auto&& preset : m_renderPresets) {
            if (preset == GetContext()->GetActivePreset()) {
                m_activeRenderPreset = index;
                break;
            }
            index++;
        }

        for (auto&& preset : m_renderPresets) {
            m_renderPresetsMemory += preset.ToStringRef();
            m_renderPresetsMemory += '\0';
        }
    }

    void EngineSettings::OnOpen() {
        Super::OnOpen();
        PrepareRenderPresets();
    }
}
