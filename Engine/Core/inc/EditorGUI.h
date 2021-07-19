//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_EDITORGUI_H
#define GAMEENGINE_EDITORGUI_H

#include <GUI/ICanvas.h>
#include <Base/Script.h>
#include <Base/Compiler.h>

namespace Framework {
    class EditorGUI : public Graphics::GUI::ICanvas {
    public:
        EditorGUI(Scripting::Compiler* compiler) {
            m_compiler = compiler;
        }
    private:
        Scripting::Compiler* m_compiler = nullptr;
        Scripting::Script*   m_script   = nullptr;
    private:
        bool Init() override;
    public:
        bool Destroy() override;
        void Free() override;

        // Call only from window
        void Draw() override;
    };
}

#endif //GAMEENGINE_EDITORGUI_H
