//
// Created by Nikita on 29.12.2020.
//

#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <Debug.h>
#include <Window/Window.h>
#include <Render/Render.h>
#include <World/Scene.h>
#include <Types/Skybox.h>
#include <Events/EventManager.h>
#include <Types/Time.h>
#include <FileSystem/FileSystem.h>
#include <Core/PhysEngine.h>
#include <GUI/EditorGUI.h>

#include <Types/SafePointer.h>

#include <EvoScriptAPI.h>
#include <Types/Thread.h>
#include <EngineCommands.h>

namespace Framework {
    class Engine : public Singleton<Engine> {
        friend class Singleton<Engine>;
        friend class API;
    private:
        Engine();
        ~Engine();
    public:
        enum class MainScriptType {
            None, Engine, Game, Benchmark
        };
    private:
        std::atomic<bool>            m_isCreate    = false;
        std::atomic<bool>            m_isInit      = false;
        std::atomic<bool>            m_isRun       = false;
        std::atomic<bool>            m_isClose     = false;

        std::atomic<bool>            m_exitEvent   = false;
    private:
        Engine::MainScriptType       m_scriptType  = MainScriptType::None;
        Scripting::Script*           m_mainScript  = nullptr;

        Scripting::Compiler*         m_compiler    = nullptr;
        Graphics::Window*            m_window      = nullptr;
        Graphics::Render*            m_render      = nullptr;
        Types::SafePtr<World::Scene> m_scene       = Types::SafePtr<World::Scene>(nullptr);

        Helper::Types::Time*         m_time        = nullptr;
        Helper::Types::Thread*       m_worldThread = nullptr;

        Core::GUI::EditorGUI*        m_editor      = nullptr;
        Physics::PhysEngine*         m_physics     = nullptr;
    private:
        bool RegisterLibraries();
        bool LoadMainScript();
    public:
        static void Reload() {
            Helper::FileSystem::Reload();
            EventManager::Push(EventManager::Event::Exit);
        }

        bool CloseScene();

        bool SetScene(const Types::SafePtr<World::Scene>& scene) { // TODO: add thread security!
            if (m_scene.Valid() && scene == m_scene) {
                Helper::Debug::Warn("Engine::SetScene() : scene ptr equals current scene ptr!");
                return false;
            } else {
                this->m_scene = scene;
                return true;
            }
        }

        [[nodiscard]] inline Helper::Types::Time* GetTime() const { return this->m_time; }
        [[nodiscard]] inline Types::SafePtr<World::Scene> GetScene() const { return m_scene; }
        [[nodiscard]] inline Graphics::Window* GetWindow() const { return m_window; }
        [[nodiscard]] inline Graphics::Render* GetRender() const { return m_render; }
        [[nodiscard]] inline bool IsRun() const { return m_isRun; }
        [[nodiscard]] inline Core::GUI::EditorGUI* GetEditor() const { return m_editor; }
    public:
        bool Create(Graphics::Window* window, Physics::PhysEngine* physics);
        bool Init(Engine::MainScriptType mainScriptType);
        bool Run();
        void Await();
        bool Close();
    };
}

#endif //GAMEENGINE_ENGINE_H
