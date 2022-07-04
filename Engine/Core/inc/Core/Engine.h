//
// Created by Nikita on 29.12.2020.
//

#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <Core/GUI/EditorGUI.h>
#include <Core/EvoScriptAPI.h>
#include <Core/PhysEngine.h>
#include <Core/EngineCommands.h>

#include <Utils/Events/EventManager.h>
#include <Utils/Types/Time.h>
#include <Utils/Types/Timer.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Input/InputDispatcher.h>
#include <Utils/Input/InputHandler.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_GRAPH_NS {
    class Window;
    class Render;
}

namespace Framework {
    using ScenePtr = Helper::Types::SafePtr<SR_WORLD_NS::Scene>;

    class Engine : public Helper::Singleton<Engine> {
        friend class Singleton<Engine>;
        friend class API;

    public:
        enum class MainScriptType {
            None, Engine, Game, Benchmark
        };

    private:
        Engine() = default;
        ~Engine() override = default;

    public:
        void Reload();
        bool SetScene(const ScenePtr& scene);

        SR_NODISCARD SR_INLINE Helper::Types::Time* GetTime() const { return this->m_time; }
        SR_NODISCARD SR_INLINE ScenePtr GetScene() const { return m_scene; }
        SR_NODISCARD SR_INLINE Graphics::Window* GetWindow() const { return m_window; }
        SR_NODISCARD SR_INLINE Graphics::Render* GetRender() const { return m_render; }
        SR_NODISCARD SR_INLINE bool IsRun() const { return m_isRun; }
        SR_NODISCARD SR_INLINE Core::GUI::EditorGUI* GetEditor() const { return m_editor; }
        SR_NODISCARD SR_INLINE Helper::CmdManager* GetCmdManager() const { return m_cmdManager; }

    public:
        bool Create(Graphics::Window* window, Physics::PhysEngine* physics);
        bool Init();
        bool Run();
        void Await();
        bool Close();

    private:
        bool RegisterLibraries();

    private:
        std::atomic<bool>         m_isCreate    = false;
        std::atomic<bool>         m_isInit      = false;
        std::atomic<bool>         m_isRun       = false;
        std::atomic<bool>         m_isClose     = false;

        std::atomic<bool>         m_exitEvent   = false;

        Helper::CmdManager*       m_cmdManager  = nullptr;
        SR_GRAPH_NS::Window*      m_window      = nullptr;
        SR_GRAPH_NS::Render*      m_render      = nullptr;

        SR_HTYPES_NS::Time*       m_time        = nullptr;
        SR_HTYPES_NS::Thread::Ptr m_worldThread = nullptr;

        Core::GUI::EditorGUI*     m_editor      = nullptr;
        Physics::PhysEngine*      m_physics     = nullptr;
        ScenePtr                  m_scene       = ScenePtr(nullptr);
        Helper::InputDispatcher*  m_input       = nullptr;

    };
}

#endif //GAMEENGINE_ENGINE_H
