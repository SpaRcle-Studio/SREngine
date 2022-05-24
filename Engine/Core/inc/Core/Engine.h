//
// Created by Nikita on 29.12.2020.
//

#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <Core/GUI/EditorGUI.h>
#include <Core/EvoScriptAPI.h>
#include <Core/EngineCommands.h>

#include <Debug.h>
#include <Events/EventManager.h>
#include <Types/Time.h>
#include <FileSystem/FileSystem.h>
#include <Core/PhysEngine.h>

#include <Types/SafePointer.h>

#include <Types/Thread.h>
#include <Types/SafePointer.h>

#include <Input/InputDispatcher.h>
#include <Input/InputHandler.h>

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

        bool CloseScene();
        bool SetScene(const ScenePtr& scene);

        [[nodiscard]] SR_INLINE Helper::Types::Time* GetTime() const { return this->m_time; }
        [[nodiscard]] SR_INLINE ScenePtr GetScene() const { return m_scene; }
        [[nodiscard]] SR_INLINE Graphics::Window* GetWindow() const { return m_window; }
        [[nodiscard]] SR_INLINE Graphics::Render* GetRender() const { return m_render; }
        [[nodiscard]] SR_INLINE bool IsRun() const { return m_isRun; }
        [[nodiscard]] SR_INLINE Core::GUI::EditorGUI* GetEditor() const { return m_editor; }
        [[nodiscard]] SR_INLINE Helper::CmdManager* GetCmdManager() const { return m_cmdManager; }

    public:
        bool Create(Graphics::Window* window, Physics::PhysEngine* physics);
        bool Init(Engine::MainScriptType mainScriptType);
        bool Run();
        void Await();
        bool Close();

    private:
        bool RegisterLibraries();
        bool LoadMainScript();

    private:
        std::atomic<bool>         m_isCreate    = false;
        std::atomic<bool>         m_isInit      = false;
        std::atomic<bool>         m_isRun       = false;
        std::atomic<bool>         m_isClose     = false;

        std::atomic<bool>         m_exitEvent   = false;

        Engine::MainScriptType    m_scriptType  = MainScriptType::None;
        Scripting::Script*        m_mainScript  = nullptr;

        Helper::CmdManager*       m_cmdManager  = nullptr;
        Scripting::Compiler*      m_compiler    = nullptr;
        SR_GRAPH_NS::Window*      m_window      = nullptr;
        SR_GRAPH_NS::Render*      m_render      = nullptr;
        ScenePtr                  m_scene       = ScenePtr(nullptr);

        Helper::InputDispatcher*  m_input       = nullptr;
        SR_HTYPES_NS::Time*       m_time        = nullptr;
        SR_HTYPES_NS::Thread::Ptr m_worldThread = nullptr;

        Core::GUI::EditorGUI*     m_editor      = nullptr;
        Physics::PhysEngine*      m_physics     = nullptr;

    };
}

#endif //GAMEENGINE_ENGINE_H
