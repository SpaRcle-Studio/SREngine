//
// Created by Nikita on 08.01.2021.
//

#ifndef GAMEENGINE_ICANVAS_H
#define GAMEENGINE_ICANVAS_H

#include <Debug.h>
#include <Environment/Environment.h>

namespace Framework::Graphics{
    class Camera;
    class Window;
}

/*

 Пусть канвас определяется определенным собственным скриптом, который будет отвечать за его рендер
 В при инициализации передавать имя скрипта

 Должен быть глобальный канвас, и множество канвасов для камер
 Главное окно и камеры должны вызвавать метод отрисовки

 Канвас должен сам определять метод отрисовки

 Например, регистрировать в нем некую функцию

 А эта функция будет загружать скрипт и вызвать из него методы

 Пример:
    lua:
        canvas = ICanvas.Create(camera, "editor.lua");

    C++:
        ICanvas* Create(Camera* camera, std::string name) {
            std::function fun =
            ICanvas* canvas =
        }

 Хотя, канвас скорее всего нужно поднять на уровень движка, чтобы он сам содержал скрипты
 */

namespace Framework::Graphics::GUI {
    // Basic class
    class ICanvas {
    protected:
        ~ICanvas() = default;
        ICanvas() = default;
    //public:
        //ICanvas(Graphics::Camera* camera);
        //ICanvas(Graphics::Window* window);
    public:
        // Call only from camera or window
        virtual bool Close() = 0;
        // Call only from camera or window
        virtual bool Free() = 0;
        virtual void Draw() = 0;
    private:
        //inline static Graphics::Environment*    g_env       = nullptr;
        //bool                                    m_isInit    = false;
        //Graphics::Camera*                       m_camera    = nullptr;
        //Graphics::Window*                       m_window    = nullptr;
    public:
        // Call only after setting graphics context from Window.cpp
        //static bool Init();

        //static bool Stop();
    };
}

#endif //GAMEENGINE_ICANVAS_H
