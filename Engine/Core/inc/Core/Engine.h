//
// Created by Nikita on 29.12.2020.
//

#ifndef SR_ENGINE_ENGINE_H
#define SR_ENGINE_ENGINE_H

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
#include <Utils/TaskManager/ThreadWorker.h>

#include <Core/EvoScriptAPI.h>
#include <Core/EngineCommands.h>
#include <Core/EngineResources.h>
#include <Utils/Types/SafeQueue.h>
#include <Utils/Localization/LocalizationManager.h>

namespace SR_GRAPH_NS {
    class Window;
    class Render;
    class RenderScene;
    class RenderContext;
}

namespace SR_PHYSICS_NS {
    class PhysicsScene;
}

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_WORLD_NS {
    class Scene;
    class SceneUpdater;
}

namespace SR_CORE_GUI_NS {
    class EditorGUI;
}

namespace SR_CORE_NS {
    class EngineScene;
    class Application;

    class Engine : public SR_HTYPES_NS::SharedPtr<Engine> {
        using Super = SR_HTYPES_NS::SharedPtr<Engine>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Engine>;
        using WindowPtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::Window>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using Clock = std::chrono::high_resolution_clock;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<SR_PHYSICS_NS::PhysicsScene>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;
    public:
        explicit Engine(Application* pApplication);
        ~Engine();

        SR_NODISCARD bool Execute();

        void Reload();

        bool SetScene(const ScenePtr& scene);
        void SetActive(bool isActive);
        void SetPaused(bool isPaused);
        void SetSpeed(float_t speed);
        void SetGameMode(bool enabled);

        bool IsNeedReloadResources();

        void FixedUpdate();
        bool FlushScene();

        void AddWindow(WindowPtr pWindow);

        SR_NODISCARD bool HasSceneInQueue() const { return !m_sceneQueue.Empty(); }
        SR_NODISCARD ScenePtr GetScene() const;
        SR_NODISCARD RenderContextPtr GetRenderContext() const { return m_renderContext; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD PhysicsScenePtr GetPhysicsScene() const;
        SR_NODISCARD WindowPtr GetMainWindow() const { return m_windows.empty() ? nullptr : m_windows.front(); }
        SR_NODISCARD SR_WORLD_NS::SceneUpdater* GetSceneBuilder() const;
        SR_NODISCARD bool IsActive() const { return m_isActive; }
        SR_NODISCARD bool IsRun() const { return m_isRun; }
        SR_NODISCARD bool IsPaused() const { return m_isPaused; }
        SR_NODISCARD bool IsGameMode() const { return m_isGameMode; }
        SR_NODISCARD SR_CORE_GUI_NS::EditorGUI* GetEditor() const { return m_editor; }
        SR_NODISCARD SR_UTILS_NS::CmdManager* GetCmdManager() const { return m_cmdManager; }
        SR_NODISCARD EngineScene* GetEngineScene() const { return m_engineScene; }
        SR_NODISCARD bool IsApplicationFocused() const;

    public:
        bool Create();
        bool Init();
        bool Run();
        bool Close();

    private:
        static WindowPtr CreateMainWindow();
        void DrawCallback();

    private:
        mutable std::recursive_mutex m_mutex;

        std::atomic<bool> m_isCreate  = false;
        std::atomic<bool> m_isInit = false;
        std::atomic<bool> m_isRun = false;

        std::atomic<bool> m_isGameMode = false;
        std::atomic<bool> m_isActive = false;
        std::atomic<bool> m_isPaused = false;
        std::atomic<bool> m_autoReloadResources = false;

        float_t m_speed = 1.f;
        SR_UTILS_NS::TimePointType m_timeStart;

        SR_UTILS_NS::ThreadsWorker::Ptr m_threadsWorker = nullptr;

        SR_UTILS_NS::CmdManager* m_cmdManager  = nullptr;
        SR_UTILS_NS::InputDispatcher* m_input = nullptr;

        SR_HTYPES_NS::SafeQueue<ScenePtr> m_sceneQueue;

        EngineScene* m_engineScene = nullptr;
        Application* m_application = nullptr;

        SR_UTILS_NS::Localization::LocalizationManager* m_localizationManager = nullptr;

        SR_CORE_GUI_NS::EditorGUI* m_editor = nullptr;

        RenderContextPtr m_renderContext = { };

        std::vector<WindowPtr> m_windows;
        std::optional<Utils::CursorLock> m_cursorLockOpt = std::nullopt;

    };
}

#endif //SR_ENGINE_ENGINE_H
