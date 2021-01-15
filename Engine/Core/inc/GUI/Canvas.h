//
// Created by Nikita on 13.01.2021.
//

#ifndef GAMEENGINE_CANVAS_H
#define GAMEENGINE_CANVAS_H

#include <GUI/ICanvas.h>
#include <Script.h>
#include <mutex>

namespace Framework {
    class Canvas : public Graphics::GUI::ICanvas {
    public:
        Canvas(Scripting::Script* script);
    protected:
        bool Init() override;
    private:
        bool                m_isClosed = false;
        bool                m_hasDraw = false;
        Scripting::Script*  m_script  = nullptr;
        std::mutex          m_mutex = std::mutex();
    public:
        // Call only from camera or window
        bool Close() override;
        // Call only from camera or window
        bool Free() override;
        void Draw() override;
    };
}

#endif //GAMEENGINE_CANVAS_H
