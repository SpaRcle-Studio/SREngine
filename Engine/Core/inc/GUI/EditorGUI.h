//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_EDITORGUI_H
#define GAMEENGINE_EDITORGUI_H

#include <GUI/ICanvas.h>
#include <Base/Script.h>
#include <Base/Compiler.h>

namespace SR_GRAPH_NS::GUI {
    class FileBrowser;
}

namespace Framework::Core::GUI {
    class VisualScriptEditor;

    class EditorGUI : public SR_GRAPH_NS::GUI::ICanvas {
    public:
        explicit EditorGUI(Scripting::Compiler* compiler)
            : m_compiler(compiler) { }

    private:
        ~EditorGUI() = default;

    private:
        bool Init() override;

    public:
        bool Destroy() override;
        void Free() override;

        [[nodiscard]] SR_GRAPH_NS::GUI::FileBrowser* GetFileBrowser() const { return m_fileBrowser; }
        [[nodiscard]] VisualScriptEditor* GetVisualScriptEditor() const { return m_scriptEditor; }

        // Call only from window
        void Draw() override;

    private:
        Scripting::Compiler*           m_compiler     = nullptr;
        Scripting::Script*             m_script       = nullptr;
        VisualScriptEditor*            m_scriptEditor = nullptr;
        SR_GRAPH_NS::GUI::FileBrowser* m_fileBrowser  = nullptr;

    };
}

#endif //GAMEENGINE_EDITORGUI_H
