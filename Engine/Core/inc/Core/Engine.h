//
// Created by Nikita on 29.12.2020.
//

#ifndef GAMEENGINE_ENGINE_H
#define GAMEENGINE_ENGINE_H

#include <Utils/Events/EventManager.h>
#include <Utils/Types/Time.h>
#include <Utils/Types/Timer.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Input/InputDispatcher.h>
#include <Utils/Input/InputHandler.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/SafeGateArray.h>

#include <Core/GUI/EditorGUI.h>
#include <Core/EvoScriptAPI.h>
#include <Core/EngineCommands.h>
#include <Core/EngineResources.h>
#include <Utils/Types/SafeQueue.h>

namespace SR_PHYSICS_NS {
    class PhysicsScene;
}

namespace SR_WORLD_NS {
    class Scene;
    class SceneBuilder;
}

namespace SR_GRAPH_NS {
    class Window;
    class Render;
    class Environment;
    class RenderScene;
    class RenderContext;
}

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_CORE_NS {
    class Engine : public SR_UTILS_NS::Singleton<Engine> {
        friend class SR_UTILS_NS::Singleton<Engine>;
        friend class Framework::API;
        using PipelinePtr = SR_GRAPH_NS::Environment*;
        using WindowPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::Window>;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<SR_PHYSICS_NS::PhysicsScene>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
    private:
        Engine() = default;
        ~Engine() override = default;

    public:
        void Reload();

        bool SetScene(const ScenePtr& scene);
        void SetActive(bool isActive);
        void SetPaused(bool isPaused);
        void SetSpeed(float_t speed);
        void SetGameMode(bool enabled);

        SR_NODISCARD SR_INLINE ScenePtr GetScene() const { return m_scene; }
        SR_NODISCARD SR_INLINE RenderContextPtr GetRenderContext() const { return m_renderContext; }
        SR_NODISCARD SR_INLINE RenderScenePtr GetRenderScene() const { return m_renderScene; }
        SR_NODISCARD SR_INLINE WindowPtr GetWindow() const { return m_window; }
        SR_NODISCARD SR_INLINE bool IsActive() const { return m_isActive; }
        SR_NODISCARD SR_INLINE bool IsRun() const { return m_isRun; }
        SR_NODISCARD SR_INLINE bool IsPaused() const { return m_isPaused; }
        SR_NODISCARD SR_INLINE bool IsGameMode() const { return m_isGameMode; }
        SR_NODISCARD SR_INLINE Core::GUI::EditorGUI* GetEditor() const { return m_editor; }
        SR_NODISCARD SR_INLINE SR_UTILS_NS::CmdManager* GetCmdManager() const { return m_cmdManager; }

    public:
        bool Create();
        bool Init();
        bool Run();
        void Await();
        bool Close();

    private:
        bool CreateMainWindow();
        bool IsNeedReloadResources();
        bool InitializeRender();
        void SynchronizeFreeResources();

        void Prepare();
        void FixedUpdate();
        void Update(float_t dt);
        void DrawCallback();
        void WorldThread();

        void FlushScene();

    private:
        std::atomic<bool> m_isCreate  = false;
        std::atomic<bool> m_isInit = false;
        std::atomic<bool> m_isRun = false;

        std::atomic<bool> m_isGameMode = false;
        std::atomic<bool> m_isActive = false;
        std::atomic<bool> m_isPaused = false;
        std::atomic<bool> m_autoReloadResources = false;

        float_t m_speed = 1.f;
        float_t m_updateFrequency = 1.f;
        float_t m_accumulator = 1.f;
        TimePoint m_timeStart;
        SR_HTYPES_NS::Timer m_worldTimer;

        SR_UTILS_NS::CmdManager* m_cmdManager  = nullptr;
        SR_UTILS_NS::InputDispatcher* m_input = nullptr;
        SR_WORLD_NS::SceneBuilder* m_sceneBuilder = nullptr;

        SR_HTYPES_NS::Thread::Ptr m_worldThread = nullptr;

        ScenePtr m_scene = { };
        SR_HTYPES_NS::SafeQueue<ScenePtr> m_sceneQueue;

        RenderScenePtr m_renderScene;
        PhysicsScenePtr m_physicsScene;

        Core::GUI::EditorGUI* m_editor = nullptr;

        RenderContextPtr m_renderContext = { };

        WindowPtr m_window = { };
        PipelinePtr m_pipeline = nullptr;

        CameraPtr m_mainCamera = nullptr;

    };
}

#endif //GAMEENGINE_ENGINE_H
