//
// Created by Nikita on 13.01.2021.
//

#ifndef GAMEENGINE_CANVAS_H
#define GAMEENGINE_CANVAS_H

#include <GUI/ICanvas.h>
#include <Script.h>

namespace Framework {
    class Canvas : public Graphics::GUI::ICanvas {
    public:
        Canvas(Scripting::Script* script);
    public:
        // Call only from camera or window
        bool Close() override;
        // Call only from camera or window
        bool Free() override;
        void Draw() override;
    };
}

#endif //GAMEENGINE_CANVAS_H
