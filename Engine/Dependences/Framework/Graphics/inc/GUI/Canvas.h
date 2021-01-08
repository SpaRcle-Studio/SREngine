//
// Created by Nikita on 08.01.2021.
//

#ifndef GAMEENGINE_CANVAS_H
#define GAMEENGINE_CANVAS_H

#include <Debug.h>

namespace Framework::Graphics::GUI {
    class Canvas {
    private:
        Canvas() = default;
        ~Canvas() = default;
    public:
        static Canvas* Get() noexcept {
            static Canvas* canvas = nullptr;
            if (!canvas)
                canvas = new Canvas();
            return canvas;
        }
    private:
        bool m_isInit = false;
    public:
        // Call only after setting graphics context from Window.cpp
        bool Init();

        bool Stop();
    };
}

#endif //GAMEENGINE_CANVAS_H
