//
// Created by Nikita on 08.01.2021.
//

#ifndef GAMEENGINE_ICANVAS_H
#define GAMEENGINE_ICANVAS_H

namespace Framework::Graphics::GUI {
    // Basic class
    class ICanvas {
    protected:
        ~ICanvas() = default;
        ICanvas() = default;
    protected:
        bool m_isInit    = false;
        bool m_hasErrors = false;
    protected:
        virtual bool Init() = 0;
    public:
        static void InitStyle();
    public:
        virtual bool Destroy() = 0;
        virtual void Free() = 0;

        // Call only from window
        virtual void Draw() = 0;
    };
}

#endif //GAMEENGINE_ICANVAS_H
