//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_EDITORGUI_H
#define GAMEENGINE_EDITORGUI_H

#include <GUI/ICanvas.h>
#include <Base/Script.h>
#include <Base/Compiler.h>

namespace Framework::Core::GUI {
    class FileBrowser;

    class EditorGUI : public Graphics::GUI::ICanvas {
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

        [[nodiscard]] FileBrowser* GetFileBrowser() const { return m_fileBrowser; }

        // Call only from window
        void Draw() override;

    private:
        Scripting::Compiler* m_compiler    = nullptr;
        Scripting::Script*   m_script      = nullptr;
        FileBrowser*         m_fileBrowser = nullptr;

    };
}

#endif //GAMEENGINE_EDITORGUI_H
