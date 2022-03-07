//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_EDITORGUI_H
#define GAMEENGINE_EDITORGUI_H

#include <GUI/ICanvas.h>
#include <Base/Script.h>
#include <Base/Compiler.h>
#include <GUI/WidgetManager.h>
#include <GUI/Hierarchy.h>
#include <GUI/Editor/SceneViewer.h>

namespace SR_GRAPH_NS::GUI {
    class FileBrowser;
}

namespace Framework::Core::GUI {
    class VisualScriptEditor;
    class Inspector;
    class WorldEdit;

    class EditorGUI : public SR_GRAPH_NS::GUI::WidgetManager {
        using Widgets = std::unordered_map<size_t, Graphics::GUI::Widget*>;
    public:
        explicit EditorGUI(Scripting::Compiler* compiler);

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

        SR_NODISCARD bool Enabled() const { return m_enabled; }

        void Draw() override;
        void Update();

    private:
        void OnKeyDown(const KeyDownEvent& event) override;
        void OnKeyPress(const KeyPressEvent& event) override;
        void OnKeyUp(const KeyUpEvent& event) override;

    private:
        bool Init();
        void Save();
        void Load();

    private:
        Graphics::Window*    m_window    = nullptr;
        Scripting::Compiler* m_compiler  = nullptr;
        Scripting::Script*   m_script    = nullptr;

        std::atomic<bool>    m_isInit    = false;
        std::atomic<bool>    m_hasErrors = false;
        std::atomic<bool>    m_enabled   = false;

        Widgets              m_widgets   = {};

    };
}

#endif //GAMEENGINE_EDITORGUI_H

