//
// Created by Nikita on 19.07.2021.
//

#ifndef SR_ENGINE_EDITOR_GUI_H
#define SR_ENGINE_EDITOR_GUI_H

#include <Utils/Common/Enumerations.h>
#include <Utils/Types/SafePointer.h>

#include <Scripting/Base/Script.h>
#include <Scripting/Base/Compiler.h>

#include <Graphics/GUI/WidgetManager.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_GTYPES_NS {
    class Texture;
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
    class VisualScriptEditor;
    class Inspector;
    class WorldEdit;

    class EditorGUI : public SR_GRAPH_GUI_NS::WidgetManager {
        using Super = SR_GRAPH_GUI_NS::WidgetManager;
        using Widgets = std::unordered_map<size_t, SR_GRAPH_NS::GUI::Widget*>;
        using Icons = std::map<EditorIcon, SR_GTYPES_NS::Texture*>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using WindowPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::Window>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using EnginePtr = SR_HTYPES_NS::SharedPtr<SR_CORE_NS::Engine>;
        enum class Click {
            None, Drag, Miss
        };
    public:
        explicit EditorGUI(const EnginePtr& pEngine);
        ~EditorGUI() override;

    public:
        void Enable(bool value);

        template<typename T> SR_DEPRECATED void AddWindow(T* widget) {
            m_widgets.insert(std::make_pair(typeid(T).hash_code(), widget));
        }

        template<typename T> void AddWidget(T* widget) {
            if (m_widgets.count(typeid(T).hash_code()) == 1) {
                SRHalt("Widget already was added!");
                return;
            }

            m_widgets.insert(std::make_pair(typeid(T).hash_code(), widget));
        }

        template<typename T> SR_DEPRECATED T* GetWindow() {
            return GetWidget<T>();
        }

        SR_NODISCARD SR_GRAPH_GUI_NS::Widget* GetWidget(const SR_UTILS_NS::StringAtom& name) const;

        template<typename T> T* GetWidget() {
            if (auto&& pIt = m_widgets.find(typeid(T).hash_code()); pIt != m_widgets.end()) {
                if (auto&& pWidget = dynamic_cast<T*>(pIt->second))
                    return pWidget;
            }

            SRHalt("EditorGUI::GetWidget() : widget not found!\n\tName: " + std::string(typeid(T).name()));

            return nullptr;
        }

        template<typename T> T* OpenWidget() {
            if (auto&& pWidget = GetWidget<T>()) {
                pWidget->Open();
                return pWidget;
            }
            return nullptr;
        }

        void CloseAllWidgets();

        SR_NODISCARD bool Enabled() const { return m_enabled; }
        SR_NODISCARD bool IsDockingEnabled() const { return m_useDocking; }
        SR_NODISCARD void* GetIconDescriptor(EditorIcon icon) const;
        SR_NODISCARD SR_GTYPES_NS::Texture* GetIcon(EditorIcon icon) const;
        SR_NODISCARD const EnginePtr& GetEngine() const { return m_engine; }

        void SetDockingEnabled(bool value) { m_useDocking = value; }

        void Draw() override;
        void Update(float_t dt);
        void FixedUpdate();
        void Save();

        void CacheScenePath(const SR_UTILS_NS::Path& scenePath);
        bool LoadSceneFromCachedPath();

        void ReloadWindows();

        void ResetToDefault();

    private:
        void OnMouseMove(const SR_UTILS_NS::MouseInputData* data) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;

    private:
        bool Init();
        void Load();

        void DrawDockingSpace();
        void DrawMenuBar();
        void DrawWindowPage();

    private:
        SR_UTILS_NS::Path m_cachedScenePath;

        RenderContextPtr m_context;
        EnginePtr m_engine;

        Widgets m_widgets;
        Icons m_icons;

        Click m_click = Click::None;

        std::atomic<bool> m_isInit     = false;
        std::atomic<bool> m_hasErrors  = false;
        std::atomic<bool> m_enabled    = false;
        std::atomic<bool> m_loaded     = false;

        std::atomic<bool> m_useDocking = true;
        std::atomic<bool> m_dragWindow = false;

        bool m_imGuiDemo = false;

    };
}

#endif //SR_ENGINE_EDITOR_GUI_H

