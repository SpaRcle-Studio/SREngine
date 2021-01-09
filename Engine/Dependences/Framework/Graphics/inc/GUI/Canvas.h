//
// Created by Nikita on 08.01.2021.
//

#ifndef GAMEENGINE_CANVAS_H
#define GAMEENGINE_CANVAS_H

#include <Debug.h>
#include <Environment/Environment.h>

namespace Framework::Graphics::GUI {
    class Canvas {
    private:
        Canvas();
        ~Canvas() = default;
    public:
        static Canvas* Get() noexcept {
            static Canvas* canvas = nullptr;
            if (!canvas)
                canvas = new Canvas();
            return canvas;
        }
    private:
        Graphics::Environment* m_env = nullptr;
        bool m_isInit = false;
    public:
        // Call only after setting graphics context from Window.cpp
        bool Init();

        bool Stop();
    };
}

#endif //GAMEENGINE_CANVAS_H
