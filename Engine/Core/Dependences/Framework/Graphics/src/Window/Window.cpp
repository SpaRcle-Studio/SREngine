//
// Created by Nikita on 18.11.2020.
//

#include <Window/Window.h>
#include <Utils/Math/Vector2.h>
#include <Render/Render.h>
#include <Types/Camera.h>
#include <Environment/Environment.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Types/Thread.h>
#include <Types/Material.h>
#include <Types/Texture.h>
#include <Types/Framebuffer.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <GUI/Editor/Theme.h>
#include <GUI/WidgetManager.h>
#include <GUI/Widget.h>

namespace SR_GRAPH_NS {
    Window::Window(
            std::string name,
            std::string icoPath,
            const SR_MATH_NS::IVector2 &size,
            bool vsync, bool fullScreen, bool resizable,
            bool headerEnabled, uint8_t smoothSamples
        ) : m_env(Environment::Get())
        , m_size(size)
        , m_winName(std::move(name))
        , m_icoPath(std::move(icoPath))
        , m_fullScreen(fullScreen)
        , m_vsync(vsync)
        , m_smoothSamples(smoothSamples)
        , m_resizable(resizable)
        , m_headerEnabled(headerEnabled)
    { }

    Window::~Window() {
        SRAssert(m_isClose);
    }

    bool Window::Create() {
        if (m_isCreate) {
            SR_ERROR("Window::Create() : the window is already created!");
            return false;
        }

        SR_INFO("Window::Create() : creating the window...");

        m_context = new RenderContext();

        Environment::SetWinCallBack([this](Environment::WinEvents event, void* win, void* arg1, void* arg2){
            switch (event) {
                case Environment::WinEvents::Close:
                    SR_SYSTEM_LOG("Window event: closing the window...");
                    break;
                case Environment::WinEvents::Move: {
                    int size[2] = {*(int *) arg1, *(int *) arg2};
                    m_windowPos = { (int32_t)size[0], (int32_t)size[1] };
                    m_env->SetWindowPosition((int)m_windowPos.x, (int)m_windowPos.y);
                    break;
                }
                case Environment::WinEvents::Resize: {
                    m_context.Do([&](RenderContext* ptr) {
                        auto&& [width, height] = std::pair<int, int>{*(int *) arg1, *(int *) arg2};
                        if (width > 0 && height > 0) {
                            ptr->OnResize(SR_MATH_NS::IVector2(width, height));
                            if (m_resizeCallback) {
                                m_resizeCallback(SR_MATH_NS::IVector2(width, height));
                            }
                        }
                    });
                    break;
                }
                case Environment::WinEvents::Scroll:
                    break;
                case Environment::WinEvents::LeftClick:
                    break;
                case Environment::WinEvents::RightClick:
                    break;
                case Environment::WinEvents::Focus: {
                    m_isWindowFocus = *(bool *) (arg1);
                    SR_SYSTEM_LOG(SR_UTILS_NS::Format("Window focus state: %s", (*(bool *) (arg1)) ? "True" : "False"));
                    SR_UTILS_NS::Input::Instance().Reload();
                    break;
                }
            }
        });

        m_isCreate = true;

        return true;
    }

    bool Window::Init() {
        if (!m_isCreate) {
            SR_ERROR("Window::Init() : the window is not created!");
            return false;
        }

        if (m_isInit) {
            SR_ERROR("Window::Init() : the window is already initialized!");
            return false;
        }

        SR_GRAPH_LOG("Window::Init() : initializing the window...");

        {
            m_thread = SR_HTYPES_NS::Thread::Factory::Instance().Create(&Window::Thread, this);
            m_thread->SetPriority(Helper::ThreadPriority::SR_THREAD_PRIORITY_HIGHEST);

            /// Wait environment initialize
            while (!m_isEnvInit && !m_hasErrors && !m_isClose);
        }

        //ret:
        //if (!m_render->IsInit() && !m_hasErrors)
        //    goto ret;

        if (m_hasErrors)
            return false;

        //if (!SR_GTYPES_NS::Material::InitDefault(GetRender())) {
        //    SR_ERROR("Window::Init() : failed to initialize default material!");
        //    return false;
        //}

        m_isInit = true;

        return true;
    }

    bool Window::Run() {
        if (!m_isInit) {
            SR_ERROR("Window::Run() : the window is not initialized!");
            return false;
        }

        if (m_isRun) {
            SR_ERROR("Window::Run() : the window is already running!");
            return false;
        }

        SR_GRAPH_LOG("Window::Run() : running the window...");

        m_isRun = true;

    //ret:
    //    if (!m_render->IsRun() && !m_hasErrors)
    //        goto ret;
//
    //    if (m_hasErrors)
    //        return false;

        SR_INFO("Window::Run() : the window is successfully running!");

        return true;
    }

    bool Window::Close() {
        if (!m_isRun) {
            SR_ERROR("Window::Close() : the window is not running!");
            return false;
        }

        if (m_isClose) {
            SR_ERROR("Window::Close() : window is already closed!");
            return false;
        }

        SR_GRAPH_LOG("Window::Close() : closing the window...");

        m_isRun = false;
        m_isClose = true;

        if (m_thread) {
            m_thread->TryJoin();
            m_thread->Free();
            m_thread = nullptr;
        }

        m_context.AutoFree([](RenderContext* pContext) {
            delete pContext;
        });

        return true;
    }

    void Window::Thread() {
        SR_INFO("Window::Thread() : running window's thread...");

        {
            waitInit:
            if (m_isInit && !m_isClose && !m_isRun && !m_hasErrors)
                goto waitInit;

            if (!m_hasErrors && !m_isClose)
                /// TODO: move to render context
                if (!InitEnvironment()) {
                    SR_ERROR("Window::Thread() : failed to initialize the render environment!");
                    m_hasErrors = true;
                    return;
                }

            //if (!m_render->Init()) {
            //    SR_ERROR("Window::Thread() : failed to initialize the render!");
            //    m_hasErrors = true;
            //    return;
            //}

            if (!m_context->Init()) {
                SR_ERROR("Window::Thread() : failed to initialize the render context!");
                m_hasErrors = true;
                return;
            }

            //SR_THIS_THREAD->GetContext()->SetPointer<Render>(m_render);
            SR_THIS_THREAD->GetContext()->SetValue<RenderContextPtr>(m_context);

            waitRun:
            if (!m_isRun && !m_isClose && !m_hasErrors)
                goto waitRun;

            //if (!m_render->Run()) {
            //    SR_ERROR("Window::Thread() : failed to run the render!");
            //    m_hasErrors = true;
            //    return;
            //}
        }

        SR_LOG("Window::Thread() : screen size is " + m_env->GetScreenSize().ToString());

        double deltaTime = 0;
        uint32_t frames = 0;

        /// for optimization needed pipeline
        //const PipeLine pipeLine = m_env->GetPipeLine();

        m_env->SetBuildState(false);

        while (IsAlive()) {
            auto t_start = std::chrono::high_resolution_clock::now();

            m_env->PollEvents();
            PollEvents();
            //m_render->PollEvents();

            m_context->Update();

            if (m_drawCallback) {
                m_drawCallback();
            }

            //if (pipeLine == PipeLine::Vulkan) {
            //    DrawVulkan();
            //}
            //else
            //    DrawOpenGL();

            auto t_end = std::chrono::high_resolution_clock::now();

            const double_t milliseconds = std::chrono::duration<double_t, std::milli>(t_end - t_start).count();
            deltaTime += milliseconds / CLOCKS_PER_SEC;
            ++frames;

            if (deltaTime > 1.0) { /// every second
                SR_LOG(SR_UTILS_NS::Format("FPS: %i; ms: %f", frames - 1, milliseconds));
                frames = 0; deltaTime = 0;
            }
        }

        SR_GRAPH("Window::Thread() : exiting from main cycle.");

        if (!m_widgetManagers.Empty()) {
            m_widgetManagers.Clear();
        }

        if (m_env->IsGUISupport()) {
            m_env->StopGUI();
            SR_GRAPH("Window::Thread() : completely stopping the GUI!");
        }

        //SR_GTYPES_NS::Texture::FreeNoneTexture();

        m_context->Close();

        if (!SyncFreeResources()) {
            SR_ERROR("Window::Thread() : failed to free resources!");
        }

        //if (!m_render->Close()) {
        //    SR_ERROR("Window::Thread() : failed to close the render!");
        //}

        m_env->CloseWindow();

        Memory::MeshManager::DestroySingleton();

        SR_INFO("Window::Thread() : stopping window thread...");

        m_isWindowClose = true;
    }

    bool Window::InitEnvironment() {
        SR_GRAPH("Window::InitEnvironment() : initializing the render environment...");

        SR_GRAPH("Window::InitEnvironment() : pre-initializing...");
        if (!m_env->PreInit(
                m_smoothSamples,
                "SpaRcle Engine", /// App name
                "SREngine",       /// Engine name
                SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Utilities/glslc.exe")))
        {
            SR_ERROR("Window::InitEnvironment() : failed to pre-initialize the environment!");
            return false;
        }

        SR_GRAPH("Window::InitEnvironment() : creating the window...");
        if (!m_env->MakeWindow(m_winName, m_size, m_fullScreen, m_resizable, m_headerEnabled)) {
            SR_ERROR("Window::InitEnvironment() : failed to create the window!");
            return false;
        }

        m_env->SetWindowIcon(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(m_icoPath).CStr());

        SR_GRAPH_LOG("Window::InitEnvironment() : set thread context as current...");
        if (!m_env->SetContextCurrent()) {
            SR_ERROR("Window::InitEnvironment() : failed to set context!");
            return false;
        }

        SR_GRAPH("Window::InitEnvironment() : initializing the environment...");
        if (!m_env->Init(m_vsync)) {
            SR_ERROR("Window::InitEnvironment() : failed to initialize the environment!");
            return false;
        }

        SR_GRAPH("Window::InitEnvironment() : post-initializing the environment...");

        if (!m_env->PostInit()) {
            SR_ERROR("Window::InitEnvironment() : failed to post-initialize environment!");
            return false;
        }

        {
            SR_LOG("Window::InitEnvironment() : vendor is "   + m_env->GetVendor());
            SR_LOG("Window::InitEnvironment() : renderer is " + m_env->GetRenderer());
            SR_LOG("Window::InitEnvironment() : version is "  + m_env->GetVersion());
        }

        if (m_env->IsGUISupport()) {
            if (m_env->PreInitGUI(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Fonts/CalibriL.ttf"))) {
                ImGuiStyle & style = ImGui::GetStyle();

                if (auto&& theme = GUI::Theme::Load("Engine/Configs/Themes/Dark.xml")) {
                    theme->Apply(style);
                    delete theme;
                }
                else {
                    SR_ERROR(" Window::InitEnvironment() : failed to load theme!");
                }

                const static auto iniPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Configs/ImGuiEditor.config");
                ImGui::GetIO().IniFilename = iniPath.CStr();

                if (!m_env->InitGUI()) {
                    SR_ERROR("Window::InitEnvironment() : failed to initialize the GUI!");
                    return false;
                }
            }
            else {
                SR_ERROR("Window::InitEnvironment() : failed to pre-initialize the GUI!");
            }
        }

        m_isEnvInit = true;

        return true;
    }

    void Window::CentralizeCursor() noexcept {
        if (m_isRun) {
            m_env->SetCursorPosition({ GetWindowSize().x / 2,  GetWindowSize().y / 2});
        }
        else {
            SR_ERROR("Window::CentralizeCursor() : the window is not running!");
        }
    }

    void Window::PollEvents() {
        /// change gui enabled
        //if (m_GUIEnabled.first != m_GUIEnabled.second) {
        //    m_env->SetBuildState(false);
        //    this->m_env->SetGUIEnabled(m_GUIEnabled.second);
        //    m_GUIEnabled.first.store(m_GUIEnabled.second);
        //}

        if (m_widgetManagers.NeedFlush())
            m_widgetManagers.Flush();

        if (m_isNeedResize) {
            SR_LOCK_GUARD

            m_env->SetWindowSize((uint32_t)m_size.x, (uint32_t)m_size.y);
            m_isNeedResize = false;
            m_size = { 0, 0 };
        }

        if (m_isNeedMove) {
            SR_LOCK_GUARD

            m_env->SetWindowPosition((int)m_newWindowPos.x, (int)m_newWindowPos.y);

            this->m_isNeedMove = false;
        }
    }

    void Window::Resize(uint32_t w, uint32_t h) {
        SR_LOCK_GUARD

        SR_LOG("Window::Resize() : set new window sizes: W = " + std::to_string(w) + "; H = " + std::to_string(h));

        m_size = { (int32_t)w, (int32_t)h };
        m_isNeedResize = true;
    }

    void Window::CentralizeWindow() {
        SR_INFO("Window::CentralizeWindow() : wait to centralize window...");

        SR_LOCK_GUARD

        if (!m_env->GetBasicWindow()) {
            SR_WARN("Window::CentralizeWindow() : basic window is nullptr!");
            return;
        }

        auto scr_size = m_env->GetScreenSize();

        auto w = m_isNeedResize ? m_size.x : m_env->GetBasicWindow()->GetWidth();
        auto h = m_isNeedResize ? m_size.y : m_env->GetBasicWindow()->GetHeight();

        w = (int) (scr_size.x - (float)w) / 2;
        h = (int) (scr_size.y - (float)h) / 2;

        m_newWindowPos = { (int32_t)w, (int32_t)h };
        m_isNeedMove = true;
    }

    void Window::BeginSync() {
        m_mutex.lock();
    }

    void Window::EndSync() {
        m_mutex.unlock();
    }

    bool Window::IsAlive() const {
        return m_isRun && !m_hasErrors && !m_isClose && m_env->IsWindowOpen() && !m_env->HasErrors();
    }

    bool Window::SyncFreeResources() {
        SR_SYSTEM_LOG("Window::SyncFreeResources() : synchronizing resources...");

        std::atomic<bool> syncComplete(false);

        //m_render->SetSkybox(nullptr);

        /** Ждем, пока все графические ресурсы не освободятся */
        auto&& thread = SR_HTYPES_NS::Thread::Factory::Instance().Create([&syncComplete, this]() {
            uint32_t syncStep = 0;
            const uint32_t maxErrStep = 50;

            SR_UTILS_NS::ResourceManager::Instance().Synchronize(true);

            //if (auto material = SR_GTYPES_NS::Material::GetDefault(); material && material->GetCountUses() == 1)
            //    SR_GTYPES_NS::Material::FreeDefault();

           // m_render->Synchronize();

            ///!m_render->IsClean() &&
            while(!m_context->IsEmpty()) {
                SR_SYSTEM_LOG("Window::SyncFreeResources() : synchronizing resources (step " + std::to_string(++syncStep) + ")");

                //if (auto material = SR_GTYPES_NS::Material::GetDefault(); material && material->GetCountUses() == 1)
                //    SR_GTYPES_NS::Material::FreeDefault();

                SR_UTILS_NS::ResourceManager::Instance().Synchronize(true);
                //m_render->Synchronize();

                if (maxErrStep == syncStep) {
                    SR_ERROR("Window::SyncFreeResources() : [FATAL] resources can not be released!");
                    SR_UTILS_NS::ResourceManager::Instance().PrintMemoryDump();
                    SR_UTILS_NS::Debug::Instance().Terminate();
                    break;
                }

                Helper::Types::Thread::Sleep(50);
            }

            syncComplete = true;
        });

        /** Так как некоторые ресурсы, такие как материалы, имеют вложенные ресурсы,
         * то они могут ожидать пока графический поток уберет метку использования с них */
        while (!syncComplete) {
            PollEvents();
            SR_UTILS_NS::ResourceManager::LockSingleton();
            //m_render->PollEvents();
            m_context.Do([](RenderContext* ptr) {
                ptr->Update();
            });
            SR_UTILS_NS::ResourceManager::UnlockSingleton();
        }

        //if (auto&& material = SR_GTYPES_NS::Material::GetDefault()) {
        //    SRAssert2(false, "Window::SyncFreeResources() : default material was not be freed!\n\tUses count: " +
        //                     std::to_string(material->GetCountUses()));
        //}

        thread->TryJoin();
        thread->Free();

        SR_SYSTEM_LOG("Window::SyncFreeResources() : synchronizing is complete!");

        return true;
    }

    void Window::Synchronize() {
    ret:
        if (!m_isNeedMove && !m_isNeedResize && !m_env->IsNeedReBuild() && m_GUIEnabled.first == m_GUIEnabled.second)
            return;

        Helper::Types::Thread::Sleep(10);
        goto ret;
    }

    void Window::DrawToCamera(Types::Camera* camera, uint32_t fbo) {
        //m_render->SetCurrentCamera(camera);

        for (uint8_t i = 0; i < m_env->GetCountBuildIter(); ++i) {
            m_env->SetBuildIteration(i);

            m_env->BindFrameBuffer(fbo);

            m_env->BeginRender();
            {
                m_env->SetViewport();
                m_env->SetScissor();

                //m_render->DrawGeometry();
                //m_render->DrawSkybox();
            }
            m_env->EndRender();
        }
    }

    void Window::DrawSingleCamera(Types::Camera *camera) {
        //m_render->SetCurrentCamera(camera);

        m_env->ClearFramebuffersQueue();

        ///

        //static auto* fbo1 = SR_GTYPES_NS::Framebuffer::Create(1, SR_MATH_NS::IVector2(1000), "Engine/framebuffer_screen_left.srsl");
        //if (fbo1->Bind() && fbo1->BeginRender()) {
        //    //m_render->DrawGeometry();
        //    m_render->DrawSkybox();
        //    fbo1->EndRender();
        //}
//
        //static auto* fbo2 = SR_GTYPES_NS::Framebuffer::Create(1, SR_MATH_NS::IVector2(1000), "Engine/framebuffer_screen_right.srsl");
//
        //if (fbo2->Bind() && fbo2->BeginRender()) {
        //    m_render->DrawGeometry();
        //    //m_render->DrawSkybox();
        //    fbo2->EndRender();
        //}

        ///

        m_env->ClearBuffers(0.5f, 0.5f, 0.5f, 1.f, 1.f, 1);

        for (uint8_t i = 0; i < m_env->GetCountBuildIter(); ++i) {
            m_env->SetBuildIteration(i);

            m_env->BindFrameBuffer(0);

            m_env->BeginRender();
            {
                m_env->SetViewport();
                m_env->SetScissor();

                //fbo1->Draw();
                //fbo2->Draw();

                //m_render->DrawSkybox();
                //m_render->DrawGeometry();
            }
            m_env->EndRender();
        }
    }

    void Window::DrawNoCamera() {
        m_env->ClearFramebuffersQueue();

        {
            m_env->ClearBuffers(0.5f, 0.5f, 0.5f, 1.f, 1.f, 1);

            //m_render->CalculateAll();

            for (uint8_t i = 0; i < m_env->GetCountBuildIter(); ++i) {
                m_env->SetBuildIteration(i);

                m_env->BindFrameBuffer(0);

                m_env->BeginRender();
                {
                    m_env->SetViewport();
                    m_env->SetScissor();
                }
                m_env->EndRender();
            }
        }

        m_env->DrawFrame();
    }

    void Window::RemoveWidgetManager(GUI::WidgetManager* widgetManager) {
        m_widgetManagers.SyncRemove(widgetManager);
    }

    void Window::RegisterWidgetManager(GUI::WidgetManager* widgetManager) {
        m_widgetManagers.Add(widgetManager);
    }

    void Window::SetGUIEnabled(bool value) {
        if (value) {
            SR_LOG("Window::SetGUIEnabled() : enabling gui...");
        }
        else
            SR_LOG("Window::SetGUIEnabled() : disabling gui...");

        m_GUIEnabled.second = value;
    }

    void Window::SetFullScreen(bool value) {
        m_env->SetFullScreen(value);
    }

    void Window::DrawVulkan() {
        const bool canUseGUI = IsGUIEnabled() && m_env->IsGUISupport() && !m_env->IsWindowCollapsed();

        if (canUseGUI) {
            if (m_env->BeginDrawGUI()) {
                for (auto &&widgetManager : m_widgetManagers.GetElements())
                    widgetManager->Draw();

                m_env->EndDrawGUI();
            }
        }

        Memory::CameraManager::LockSingleton();

        auto&& cameraManager = Memory::CameraManager::Instance();
        auto&& firstCamera = cameraManager.GetFirstCamera();
        auto&& uboManager = Memory::UBOManager::Instance();

        if (!firstCamera) {
            if (canUseGUI) {
                DrawNoCamera();
            }

            m_env->SetBuildState(true);
            Memory::CameraManager::UnlockSingleton();
            return;
        }

        const bool multipleRender = SR_UTILS_NS::Features::Instance().Enabled("MultiRenderTargets");
        auto&& cameras = cameraManager.GetCameras();

        if (m_env->IsNeedReBuild()) {
            //SR_LOG("Window::DrawVulkan() : re-build scene...");

            if (!multipleRender || cameras.size() == 1) {
                uboManager.SetCurrentCamera(firstCamera);
                DrawSingleCamera(firstCamera);
            }
            else {
                m_env->ClearFramebuffersQueue();

                m_env->ClearBuffers(0.5f, 0.5f, 0.5f, 1.0f, 1.f, 1);

                for (auto &&pCamera : cameras) {
                    uboManager.SetCurrentCamera(pCamera);
                    DrawToCamera(pCamera, 0);
                }
            }

            m_env->SetBuildState(true);
        }
        else {
            if (!multipleRender || cameras.size() == 1) {
                uboManager.SetCurrentCamera(firstCamera);
               //m_render->SetCurrentCamera(firstCamera);
               //m_render->UpdateUBOs();
            }
            else {
                for (auto &&pCamera : cameras) {
                    uboManager.SetCurrentCamera(pCamera);
                   //m_render->SetCurrentCamera(pCamera);
                   //m_render->UpdateUBOs();
                }
            }
        }

        Memory::CameraManager::UnlockSingleton();

        m_env->DrawFrame();
    }

    void Window::DrawOpenGL() {

    }

    bool Window::IsFullScreen() const {
        return m_env->IsFullScreen();
    }

    SR_MATH_NS::IVector2 Window::GetWindowSize() const {
        if (!m_env || !m_env->HasWindow()) {
            return m_size;
        }

        return m_env->GetWindowSize();
    }

    void Window::SetDrawCallback(const Window::DrawCallback &drawCallback) {
        m_drawCallback = drawCallback;
    }

    void Window::SetResizeCallback(const Window::ResizeCallback &resizeCallback) {
        m_resizeCallback = resizeCallback;
    }
}