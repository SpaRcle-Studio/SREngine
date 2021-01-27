//
// Created by Nikita on 29.12.2020.
//

#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <Debug.h>
#include <Compiler.h>
#include <Window/Window.h>
#include <Render/Render.h>
#include <EntityComponentSystem/Scene.h>
#include <Types/Skybox.h>
#include <Events/EventManager.h>

namespace Framework {
    class Engine {
    private:
        Engine();
        ~Engine();
    public:
        inline static Engine* Get() {
            static Engine* engine = nullptr;
            if (!engine)
                engine = new Engine();
            return engine;
        }
    private:
        volatile bool           m_isCreate              = false;
        volatile bool           m_isInit                = false;
        volatile bool           m_isRun                 = false;
        volatile bool           m_isClose               = false;

        volatile bool           m_exitEvent             = false;
    private:
        Scripting::Compiler*    m_compiler              = nullptr;
        Graphics::Window*       m_window                = nullptr;
        Graphics::Render*       m_render                = nullptr;
        Helper::Scene*          m_scene                 = nullptr;
    private:
        bool RegisterLibraries();
    public:
        inline Scene* GetScene() const noexcept { return m_scene; }
        inline Scripting::Compiler* GetCompiler() const noexcept { return m_compiler; }
        inline Graphics::Window* GetWindow() const noexcept { return m_window; }
        inline bool IsRun() const noexcept { return m_isRun; }
    public:
        bool Create(Graphics::Window* window, Helper::Scene* scene);
        bool Init(Graphics::Camera* scene_camera);
        bool Run();
        void Await();
        bool Close();
    };
}

#endif //GAMEENGINE_ENGINE_H
