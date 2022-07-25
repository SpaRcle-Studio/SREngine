//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H

#include <Utils/GUI.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/SafeGateArray.h>
#include <Utils/Types/SafeGateArray.h>
#include <Utils/Types/Function.h>

namespace SR_GRAPH_NS::Types {
    class Camera;
}

namespace SR_GRAPH_NS {
    namespace GUI {
        class WidgetManager;
    }

    class Render;
    class RenderContext;
    class Environment;

    class Window : SR_UTILS_NS::NonCopyable {
        using DrawCallback = SR_HTYPES_NS::Function<void(void)>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
    public:
        Window(std::string name, std::string icoPath, const SR_MATH_NS::IVector2& size, Render* render,
                bool vsync, bool fullScreen, bool resizable, bool headerEnabled, uint8_t smoothSamples);
        ~Window() override;

    public:
        bool Create();
        bool Init();
        bool Run();
        bool Close();

    public:
        void Synchronize();
        void BeginSync();
        void EndSync();

        void RemoveWidgetManager(GUI::WidgetManager* widgetManager);
        void RegisterWidgetManager(GUI::WidgetManager* widgetManager);

    public:
        void CentralizeWindow();
        void CentralizeCursor() noexcept;
        void Resize(uint32_t w, uint32_t h);

        void SetFullScreen(bool value);
        void SetGUIEnabled(bool value);
        void SetDrawCallback(const DrawCallback& drawCallback);

    public:
        SR_NODISCARD SR_FORCE_INLINE bool IsRun() const { return m_isRun; }
        SR_NODISCARD SR_FORCE_INLINE bool IsGUIEnabled() const { return m_GUIEnabled.first; }
        SR_NODISCARD bool IsFullScreen() const;
        SR_NODISCARD SR_FORCE_INLINE bool IsWindowOpen() const { return !m_isWindowClose; }
        SR_NODISCARD SR_FORCE_INLINE bool IsWindowFocus() const { return m_isWindowFocus; }
        SR_NODISCARD SR_MATH_NS::IVector2 GetWindowSize() const;
        //SR_NODISCARD SR_FORCE_INLINE Render* GetRender() const { SRAssert(m_render); return m_render; }
        SR_NODISCARD SR_INLINE RenderContextPtr GetContext() const { return m_context; }
        SR_NODISCARD bool IsAlive() const;

        void DrawVulkan();
        void DrawOpenGL();

    private:
        void PollEvents();
        void Thread();
        bool InitEnvironment();
        bool SyncFreeResources();
        void DrawNoCamera();

        void DrawToCamera(Types::Camera* camera, uint32_t fbo);
        void DrawSingleCamera(Types::Camera* camera);

    private:
        std::atomic<bool>     m_isCreate              = false;
        std::atomic<bool>     m_isInit                = false;
        std::atomic<bool>     m_isRun                 = false;
        std::atomic<bool>     m_isClose               = false;

        std::atomic<bool>     m_hasErrors             = false;
        std::atomic<bool>     m_isEnvInit             = false;

        std::atomic<bool>     m_isWindowClose         = false;
        std::atomic<bool>     m_isWindowFocus         = true;
        std::atomic<bool>     m_isNeedResize          = false;
        std::atomic<bool>     m_isNeedMove            = false;

        std::atomic<bool>     m_vsync                 = false;
        std::atomic<bool>     m_fullScreen            = false;
        std::atomic<bool>     m_resizable             = false;
        std::atomic<bool>     m_headerEnabled         = false;

    private:
        SR_HTYPES_NS::Thread::Ptr m_thread            = nullptr;

        DrawCallback          m_drawCallback          = { };

        Environment*          m_env                   = nullptr;

        std::string           m_winName               = "Unnamed";
        std::string           m_icoPath               = "Unknown";
        uint8_t               m_smoothSamples         = 4;

        RenderContextPtr      m_context               = { };

        std::recursive_mutex  m_mutex                 = std::recursive_mutex();

        SR_MATH_NS::IVector2  m_windowPos             = { 0, 0 };
        SR_MATH_NS::IVector2  m_newWindowPos          = { 0, 0 };
        SR_MATH_NS::IVector2  m_size                  = { 0, 0 };

        Helper::Types::SafeGateArray<GUI::WidgetManager*> m_widgetManagers;

        /* 1 - current, 2 - new */
        std::pair<std::atomic<bool>, std::atomic<bool>> m_GUIEnabled = { false, false };

    };
}

#endif //GAMEENGINE_WINDOW_H
