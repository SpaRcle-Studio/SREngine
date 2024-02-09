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

#include <Core/GUI/EditorGUI.h>
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
}

namespace SR_CORE_NS {
    class EngineScene;
    class Application;

    class Engine : public SR_HTYPES_NS::SharedPtr<Engine> {
        using Super = SR_HTYPES_NS::SharedPtr<Engine>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Engine>;
        using WindowPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::Window>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using Clock = std::chrono::high_resolution_clock;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<SR_PHYSICS_NS::PhysicsScene>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;
    public:
        explicit Engine(Application* pApplication);

        void Reload();

        bool SetScene(const ScenePtr& scene);
        void SetActive(bool isActive);
        void SetPaused(bool isPaused);
        void SetSpeed(float_t speed);
        void SetGameMode(bool enabled);

        void FixedUpdate();
        void FlushScene();

        SR_NODISCARD bool HasSceneInQueue() const { return !m_sceneQueue.Empty(); }
        SR_NODISCARD SR_INLINE ScenePtr GetScene() const;
        SR_NODISCARD SR_INLINE RenderContextPtr GetRenderContext() const { return m_renderContext; }
        SR_NODISCARD SR_INLINE RenderScenePtr GetRenderScene() const;
        SR_NODISCARD SR_INLINE WindowPtr GetWindow() const { return m_window; }
        SR_NODISCARD SR_INLINE SR_WORLD_NS::SceneUpdater* GetSceneBuilder() const;
        SR_NODISCARD SR_INLINE bool IsActive() const { return m_isActive; }
        SR_NODISCARD SR_INLINE bool IsRun() const { return m_isRun; }
        SR_NODISCARD SR_INLINE bool IsPaused() const { return m_isPaused; }
        SR_NODISCARD SR_INLINE bool IsGameMode() const { return m_isGameMode; }
        SR_NODISCARD SR_INLINE SR_CORE_GUI_NS::EditorGUI* GetEditor() const { return m_editor; }
        SR_NODISCARD SR_INLINE SR_UTILS_NS::CmdManager* GetCmdManager() const { return m_cmdManager; }

    public:
        bool Create();
        bool Init();
        bool Run();
        bool Close();

    private:
        bool CreateMainWindow();
        bool IsNeedReloadResources();
        bool InitializeRender();
        void SynchronizeFreeResources();

        void DrawCallback();
        void WorldThread();

    private:
        std::atomic<bool> m_isCreate  = false;
        std::atomic<bool> m_isInit = false;
        std::atomic<bool> m_isRun = false;

        std::atomic<bool> m_isGameMode = false;
        std::atomic<bool> m_isActive = false;
        std::atomic<bool> m_isPaused = false;
        std::atomic<bool> m_autoReloadResources = false;

        float_t m_speed = 1.f;
        SR_UTILS_NS::TimePointType m_timeStart;
        SR_HTYPES_NS::Timer m_worldTimer;

        SR_UTILS_NS::CmdManager* m_cmdManager  = nullptr;
        SR_UTILS_NS::InputDispatcher* m_input = nullptr;

        SR_HTYPES_NS::Thread::Ptr m_worldThread = nullptr;

        SR_HTYPES_NS::SafeQueue<ScenePtr> m_sceneQueue;

        EngineScene* m_engineScene = nullptr;
        Application* m_application = nullptr;

        SR_CORE_GUI_NS::EditorGUI* m_editor = nullptr;

        SR_UTILS_NS::Localization::LocalizationManager* m_localizationManager = nullptr;

        RenderContextPtr m_renderContext = { };

        WindowPtr m_window;

    };
}

#endif //SR_ENGINE_ENGINE_H
