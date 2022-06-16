//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_EDITORGUI_H
#define GAMEENGINE_EDITORGUI_H

#include <Scripting/Base/Script.h>
#include <Scripting/Base/Compiler.h>
#include <GUI/WidgetManager.h>
#include <Utils/Common/Enumerations.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class Window;
}

namespace SR_GRAPH_NS::GUI {
    class FileBrowser;
}

namespace SR_CORE_NS::GUI {
    class VisualScriptEditor;
    class Inspector;
    class WorldEdit;

    SR_ENUM_CLASS(EditorIcon,
            Unknown
    );

    class EditorGUI : public SR_GRAPH_NS::GUI::WidgetManager {
        using Widgets = std::unordered_map<size_t, Graphics::GUI::Widget*>;
        using Icons = std::map<EditorIcon, SR_GTYPES_NS::Texture*>;
    public:
        explicit EditorGUI();

    private:
        ~EditorGUI() override;

    public:
        void Enable(bool value);
        bool Destroy();
        void Free();

        template<typename T> void AddWindow(T* widget) {
            m_widgets.insert(std::make_pair(typeid(T).hash_code(), widget));
        }

        template<typename T> T* GetWindow() {
            if (auto&& pIt = m_widgets.find(typeid(T).hash_code()); pIt != m_widgets.end())
                if (auto&& pWidget = dynamic_cast<T*>(pIt->second))
                    return pWidget;
            return nullptr;
        }

        void CloseAllWindows();

        SR_NODISCARD bool Enabled() const { return m_enabled; }
        SR_NODISCARD bool IsDockingEnabled() const { return m_useDocking; }

        void SetDockingEnabled(bool value) { m_useDocking = value; }

        void Draw() override;
        void Update();

    private:
        void OnMouseDrag(const SR_UTILS_NS::MouseInputData* data) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;

    private:
        bool Init();
        void Save();
        void Load();

    private:
        Graphics::Window*    m_window     = nullptr;

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

