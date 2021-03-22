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
#include <Types/Time.h>
#include <FileSystem/FileSystem.h>
#include <Core/PhysEngine.h>

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

        Helper::Types::Time*    m_time                  = nullptr;

        Physics::PhysEngine*    m_physics               = nullptr;
    private:
        bool RegisterLibraries();
    public:
        static inline void Reload() {
            Helper::FileSystem::Reload();
            EventManager::Push(EventManager::Event::Exit);
        }

        [[nodiscard]] inline Helper::Types::Time* GetTime() const noexcept { return this->m_time; }
        [[nodiscard]] inline Scene* GetScene() const noexcept { return m_scene; }
        [[nodiscard]] inline Scripting::Compiler* GetCompiler() const noexcept { return m_compiler; }
        [[nodiscard]] inline Graphics::Window* GetWindow() const noexcept { return m_window; }
        [[nodiscard]] inline bool IsRun() const noexcept { return m_isRun; }
    public:
        bool Create(Graphics::Window* window, Helper::Scene* scene, Physics::PhysEngine* physics);
        bool Init(Graphics::Camera* scene_camera);
        bool Run();
        void Await();
        bool Close();
    };
}

#endif //GAMEENGINE_ENGINE_H
