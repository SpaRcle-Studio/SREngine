//
// Created by Nikita on 19.07.2021.
//

#ifndef SR_ENGINE_EDITOR_GUI_H
#define SR_ENGINE_EDITOR_GUI_H

#include <Engine/Settings/EditorSettings.h>

#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/Types/Texture.h>

#include <Utils/Common/Enumerations.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/ECS/SceneObject.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_GRAPH_NS {
    class Window;
    class RenderContext;
}

namespace SR_CORE_NS {
    class Engine;
}

namespace SR_CORE_NS {
    enum class EditorIcon : uint32_t;
}

namespace SR_CORE_GUI_NS {
    class Inspector;

    class EditorGUI : public SR_GRAPH_GUI_NS::WidgetManager {
        using Super = SR_GRAPH_GUI_NS::WidgetManager;
        using Icons = SR_UTILS_NS::Map<EditorIcon, SR_GTYPES_NS::Texture::Ptr>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using WindowPtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Window>;
        using EnginePtr = SR_HTYPES_NS::SharedPtr<SR_CORE_NS::Engine>;
        using ScenePtr = SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
        enum class Click {
            None, Drag, Miss
        };
    public:
        explicit EditorGUI(const EnginePtr& pEngine);
        ~EditorGUI() override;

    public:
        void Enable(bool value);

        SR_NODISCARD bool Enabled() const { return m_enabled; }
        SR_NODISCARD bool IsDockingEnabled() const { return m_useDocking; }
        SR_NODISCARD void* GetIconDescriptor(EditorIcon icon) const;
        SR_NODISCARD const SR_GTYPES_NS::Texture* GetIcon(EditorIcon icon) const;
        SR_NODISCARD const EnginePtr& GetEngine() const { return m_engine; }
        SR_NODISCARD bool IsInitialized() const { return m_isInit; }
        SR_NODISCARD const EditorSettings::Ptr& GetSettings() const { return m_pSettings; }
        SR_NODISCARD const bool IsMetricsWindowShown() const { return m_showMetricsWindow; }

        void ShowMetricsWindow(bool isShown) { m_showMetricsWindow = isShown; }

        void SetDockingEnabled(bool value) { m_useDocking = value; }

        void Draw() override;
        void Update(float_t dt);
        void FixedUpdate();
        void Save();

        void DrawEditorInstanceMenu();

        bool Init() override;
        void DeInit() override;

        void CacheScenePath(const SR_UTILS_NS::Path& scenePath);
        bool LoadSceneFromCachedPath();

        void ReloadWindows();

        void ResetToDefault();

    private:
        void InstallOrUpdateSamples();
        void InstantiateSO(const SR_UTILS_NS::SceneObject::Ptr& pSO);

        void OnMouseMove(const SR_UTILS_NS::MouseInputData* data) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;

    private:
        void Load();

        void DrawDockingSpace();
        void DrawMenuBar();
        void DrawWindowPage();

    private:
        SR_UTILS_NS::Vector<std::pair<SR_UTILS_NS::StringAtom, SR_UTILS_NS::StringAtom>> m_windowPageWidgets;
        EditorSettings::Ptr m_pSettings;

        SR_UTILS_NS::Path m_cachedScenePath;

        RenderContextPtr m_context;
        EnginePtr m_engine;

        Icons m_icons;

        Click m_click = Click::None;

        bool m_installSamplesAsked = false;
        float_t m_samplesShowDelay = 2.5f;

        std::atomic<bool> m_isInit     = false;
        std::atomic<bool> m_hasErrors  = false;
        std::atomic<bool> m_enabled    = false;
        std::atomic<bool> m_loaded     = false;

        std::atomic<bool> m_useDocking = true;
        std::atomic<bool> m_dragWindow = false;

        bool m_showMetricsWindow = false;

        bool m_imGuiDemo = false;

    };
}

#endif //SR_ENGINE_EDITOR_GUI_H

