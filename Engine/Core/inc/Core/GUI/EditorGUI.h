//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_EDITORGUI_H
#define GAMEENGINE_EDITORGUI_H

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

namespace SR_GRAPH_NS::GUI {
    class FileBrowser;
}

namespace SR_CORE_NS {
    enum class EditorIcon : uint32_t;
}

namespace SR_CORE_NS::GUI {
    class VisualScriptEditor;
    class Inspector;
    class WorldEdit;

    class EditorGUI : public SR_GRAPH_NS::GUI::WidgetManager {
        using Widgets = std::unordered_map<size_t, SR_GRAPH_NS::GUI::Widget*>;
        using Icons = std::map<EditorIcon, SR_GTYPES_NS::Texture*>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using WindowPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::Window>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
    public:
        explicit EditorGUI();
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

        template<typename T> T* GetWidget() {
            if (auto&& pIt = m_widgets.find(typeid(T).hash_code()); pIt != m_widgets.end()) {
                if (auto&& pWidget = dynamic_cast<T*>(pIt->second))
                    return pWidget;
            }

            SRHalt("EditorGUI::GetWidget() : widget not found!\n\tName: " + std::string(typeid(T).name()));

            return nullptr;
        }

        void CloseAllWidgets();

        SR_NODISCARD bool Enabled() const { return m_enabled; }
        SR_NODISCARD bool IsDockingEnabled() const { return m_useDocking; }
        SR_NODISCARD SR_GTYPES_NS::Texture* GetIcon(EditorIcon icon) const;
        SR_NODISCARD void* GetIconDescriptor(EditorIcon icon) const;

        void SetDockingEnabled(bool value) { m_useDocking = value; }

        void Draw() override;
        void Update();

    private:
        void OnMouseMove(const SR_UTILS_NS::MouseInputData* data) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;

    private:
        bool Init();
        void Save();
        void Load();

    private:
        RenderContextPtr m_context = { };
        WindowPtr m_window = { };

        std::atomic<bool>    m_isInit     = false;
        std::atomic<bool>    m_hasErrors  = false;
        std::atomic<bool>    m_enabled    = false;
        std::atomic<bool>    m_loaded     = false;

        std::atomic<bool>    m_useDocking = true;
        std::atomic<bool>    m_dragWindow = false;

        Widgets              m_widgets    = { };
        Icons                m_icons      = { };

    };
}

#endif //GAMEENGINE_EDITORGUI_H

