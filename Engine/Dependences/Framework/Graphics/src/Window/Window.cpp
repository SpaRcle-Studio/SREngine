//
// Created by Nikita on 18.11.2020.
//

//#include <easy/profiler.h>

#include "Window/Window.h"
#include <Debug.h>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <Input/Input.h>

//#include <GUI/ICanvas.h>

#include <ResourceManager/ResourceManager.h>
#include <glm/gtx/string_cast.hpp>
#include <Utils/StringUtils.h>

using namespace Framework::Helper;

bool Framework::Graphics::Window::Create() {
    if (m_isCreate) {
        Debug::Error("Window::Create() : window already create!");
        return false;
    }

    Debug::Graph("Window::Create() : creating window...");

    this->m_time = new Helper::Types::Time();
    this->m_time->SetFPSLimit(60);

    if (!this->m_render->Create(this)){
        Debug::Error("Window::Create() : failed create render!");
        m_hasErrors = true;
        return false;
    }

    this->m_env->SetWinCallBack([this](Environment::WinEvents event, void* win, void* arg1, void* arg2){
        switch (event) {
            case Environment::WinEvents::Close:
                Debug::System("Window event: close window...");
                break;
            case Environment::WinEvents::Move:
                this->m_windowPos = {*(int *) arg1, *(int *) arg2};
                this->m_env->SetWindowPosition(m_windowPos.x, m_windowPos.y);
                break;
            case Environment::WinEvents::Resize: {
                std::pair<int, int> size = {*(int *) arg1, *(int *) arg2};
                if (size.first > 0 && size.second > 0)
                    for (auto camera : m_cameras) {
                        if (camera->IsAllowUpdateProjection())
                            if (Environment::Get()->GetPipeLine() == PipeLine::OpenGL || camera->IsDirectOutput()) {
                                camera->UpdateProjection(size.first, size.second);
                            }
                    }

                //float ratio = m_format.GetRatio();
                //m_env->SetWindowSize(*(int*)arg1, *(int*)arg2);

                //this->m_camera->UpdateProjection(ratio);
                //this->m_postProcessing->ReCalcFrameBuffers(*(int *) arg1, *(int *) arg2);
                break;
            }
            case Environment::WinEvents::Scroll:
                break;
            case Environment::WinEvents::LeftClick:
                break;
            case Environment::WinEvents::RightClick:
                break;
            case Environment::WinEvents::Focus:
                this->m_isWindowFocus = *(bool*)(arg1);
                std::cout << "Window focus state: " << *(int*)(arg1) << std::endl;
                break;
        }
    });

    this->m_isCreate = true;

    return true;
}

bool Framework::Graphics::Window::Init() {
    if (!m_isCreate){
        Debug::Error("Window::Init() : window is not created!");
        return false;
    }

    if (m_isInit){
        Debug::Error("Window::Init() : window already initialize!");
        return false;
    }

    Debug::Graph("Window::Init() : initializing window...");

    {
        this->m_thread = std::thread(&Window::Thread, this);

        while (!m_isEnvInit && !m_hasErrors && !m_isClose) { } // Wait environment initialize
    }

    ret: if (!m_render->IsInit() && !m_hasErrors) goto ret;
    if (m_hasErrors) return false;

    m_isInit = true;

    return true;
}

bool Framework::Graphics::Window::Run() {
    if (!m_isInit){
        Debug::Error("Window::Run() : window is not initialized!");
        return false;
    }

    if (m_isRun) {
        Debug::Error("Window::Run() : window already is running!");
        return false;
    }

    Debug::Graph("Window::Run() : running window...");

    this->m_isRun = true;

ret: if (!m_render->IsRun() && !m_hasErrors) goto ret;
    if (m_hasErrors) return false;

    Debug::Info("Window::Run() : window has been successfully running!");

    return true;
}

bool Framework::Graphics::Window::Close() {
    if (!m_isRun){
        Debug::Error("Window::Close() : window is not running!");
        return false;
    }

    if (m_isClose) {
        Debug::Error("Window::Close() : window already is closed!");
        return false;
    }

    Debug::Graph("Window::Close() : close window...");

    if (this->m_canvas)
        this->m_canvas->Close();

    this->m_isRun   = false;
    this->m_isClose = true;

    if (m_thread.joinable()) m_thread.join();

    if (m_time)
        delete m_time;

    return true;
}

void Framework::Graphics::Window::Thread() {
    Debug::Info("Window::Thread() : running window thread...");

    {
        waitInit:
        if (m_isInit && !m_isClose && !m_isRun && !m_hasErrors) goto waitInit;

        if (!m_hasErrors && !m_isClose)
            if (!this->InitEnvironment()) {
                Debug::Error("Window::Thread() : failed initialize render environment!");
                m_hasErrors = true;
                return;
            }

        if (!m_render->Init()) {
            Debug::Error("Window::Thread() : failed initialize render!");
            this->m_hasErrors = true;
            return;

        }

        waitRun:
        if (!m_isRun && !m_isClose && !m_hasErrors) goto waitRun;

        if (!m_render->Run()) {
            Debug::Error("Window::Thread() : failed running render!");
            m_hasErrors = true;
            return;
        }
    }

    { // centralize window and print default size
        glm::vec2 scr_size = m_env->GetScreenSize();
        Debug::Log("Window::Thread() : screen size is " +
            std::to_string((int) scr_size.x) + "x" + std::to_string((int) scr_size.y));
        this->CentralizeWindow();
    }

    double deltaTime = 0;
    unsigned int frames = 0;

    // for optimization needed pipeline
    const PipeLine pipeLine = m_env->GetPipeLine();

    this->m_env->SetBuildState(false);

    if (pipeLine == PipeLine::Vulkan) {
        while (m_isRun && !m_hasErrors && !m_isClose && this->m_env->IsWindowOpen() && !m_env->HasErrors()) {
            clock_t beginFrame = clock();

            {
                this->m_env->PollEvents();
                this->PollEvents();
                this->m_render->PollEvents();

                if (m_env->IsNeedReBuild())
                {
                    if (!m_cameras.empty()) {
                        m_render->SetCurrentCamera(m_cameras[0]);

                        Helper::Debug::Info("Window::Thread() : re-build render...");

                        if (m_cameras[0]->GetPostProcessing()->BeginGeometry()) {
                            //this->m_render->DrawTransparentGeometry();
                            //this->m_render->DrawGeometry();
                            m_cameras[0]->GetPostProcessing()->EndGeometry();
                        }

                        {
                            this->m_env->ClearBuffers(0.5f, 0.5f, 0.5f, 1.f, 1.f, 1);

                            for (uint8_t i = 0; i < m_env->GetCountBuildIter(); i++) {
                                m_env->SetBuildIteration(i);

                                m_env->BindFrameBuffer(0);

                                m_env->BeginRender();
                                {
                                    this->m_env->SetViewport();
                                    this->m_env->SetScissor();

                                    this->m_render->DrawGeometry();
                                }
                                m_env->EndRender();
                            }
                        }

                        //this->m_render->DrawSkybox();

                        m_env->SetBuildState(true);
                    }
                    continue;
                } else {
                    this->m_render->UpdateGeometry();
                }

                if (m_GUIEnabled && m_env->IsGUISupport() && !m_env->IsWindowCollapsed()) {
                    if (this->m_env->BeginDrawGUI()) {
                        //if (m_canvas)
                        //    this->m_canvas->Draw();

                        if (ImGui::Begin("Texture")) {
                            ImGui::BeginChild("Texture 1");

                            auto texture = m_env->GetTexture(0);
                            if (texture.Ready()) {
                                static auto imTex = m_env->GetImGuiTextureDescriptorFromTexture(0);

                                GUI::GUIWindow::DrawTexture(GUI::GUIWindow::GetWindowSize(),
                                                            { texture.m_width, texture.m_height },
                                                            m_env->GetDescriptorSetFromDTDSet(imTex), true);
                            }

                            ImGui::EndChild();
                            ImGui::End();
                        }

                        this->m_env->EndDrawGUI();
                    }
                }

                this->m_env->DrawFrame();
            }

            deltaTime += double(clock() - beginFrame) / (double) CLOCKS_PER_SEC;
            frames++;

            if (deltaTime > 1.0) { //every second
                std::cout << "FPS: " << frames - 1 << std::endl;
                frames = 0; deltaTime = 0; }
        }
    }
    else {
        while (m_isRun && !m_hasErrors && !m_isClose && this->m_env->IsWindowOpen() && !m_env->HasErrors()) {
            clock_t beginFrame = clock();

            {
                this->m_env->PollEvents();

                this->PollEvents();

                this->m_env->ClearBuffers();

                this->m_render->PollEvents();

                {
                    if (m_countCameras == 1) {
                        if (m_cameras[0]->IsReady()) {
                            DrawToCamera(m_cameras[0]);
                        }
                    }
                    else
                        for (Camera* camera : m_cameras) {
                            if (!camera->IsReady())
                                continue;
                            DrawToCamera(camera);
                        }

                    if (m_GUIEnabled && m_env->IsGUISupport()) {
                        if (this->m_env->BeginDrawGUI()) {
                            if (m_canvas)
                                this->m_canvas->Draw();

                            this->m_env->EndDrawGUI();
                        }
                    }
                }

                this->m_env->SwapBuffers();
            }

            deltaTime += double(clock() - beginFrame) / (double) CLOCKS_PER_SEC;
            frames++;

            if (deltaTime > 1.0) { //every second
                std::cout << "FPS: " << frames - 1 << std::endl;
                frames = 0; deltaTime = 0; }
        }
    }

    Helper::Debug::Graph("Window::Thread() : exit from main cycle.");

    if (m_env->IsGUISupport())
        m_env->StopGUI();

    if (!this->m_render->Close()) {
        Debug::Error("Window::Thread() : failed close render!");
    }

    this->m_env->CloseWindow();

    Debug::Info("Window::Thread() : stopping window thread...");

    this->m_isWindowClose = true;
}

bool Framework::Graphics::Window::InitEnvironment() {
    Debug::Graph("Window::InitEnvironment() : initializing render environment...");

    Debug::Graph("Window::InitEnvironment() : pre-initializing...");
    if (!this->m_env->PreInit(m_smoothSamples, "SpaRcle Engine", "SREngine")){
        Debug::Error("Window::InitEnvironment() : failed pre-initializing environment!");
        return false;
    }

    Debug::Graph("Window::InitEnvironment() : creating window...");
    if (!this->m_env->MakeWindow(this->m_win_name, m_fullScreen, m_resizable)) {
        Debug::Error("Window::InitEnvironment() : failed creating window!");
        return false;
    }
    this->m_env->SetWindowIcon(std::string(Helper::ResourceManager::GetResourcesFolder().append("/Textures/").append(m_icoPath)).c_str());

    Debug::Graph("Window::InitEnvironment() : set context current...");
    if (!this->m_env->SetContextCurrent()) {
        Debug::Error("Window::InitEnvironment() : failed set context!");
        return false;
    }

    Debug::Graph("Window::InitEnvironment() : initializing environment...");
    if (!this->m_env->Init(m_vsync)) {
        Debug::Error("Window::InitEnvironment() : failed initializing environment!");
        return false;
    }

    Debug::Graph("Window::InitEnvironment() : post-initializing environment...");
    this->m_env->PostInit();

    {
        Debug::Log("Window::InitEnvironment() : vendor is "   + m_env->GetVendor());
        Debug::Log("Window::InitEnvironment() : renderer is " + m_env->GetRenderer());
        Debug::Log("Window::InitEnvironment() : version is "  + m_env->GetVersion());
    }

    if (m_env->IsGUISupport()) {
        if (this->m_env->PreInitGUI(Helper::ResourceManager::GetResourcesFolder() + "\\Fonts\\CalibriL.ttf")) {
            GUI::ICanvas::InitStyle();
            this->m_env->InitGUI();
        } else
            Debug::Error("Window::InitEnvironment() : failed pre-initializing GUI!");
    }

    m_isEnvInit = true;

    return true;
}

void Framework::Graphics::Window::DrawToCamera(Framework::Graphics::Camera* camera) {
    m_render->SetCurrentCamera(camera);

    camera->GetPostProcessing()->BeginGeometry();
    {
        m_render->DrawGeometry();
        m_render->DrawTransparentGeometry();
    }
    camera->GetPostProcessing()->EndGeometry();

    camera->GetPostProcessing()->BeginSkybox();
    {
        m_render->DrawSkybox();
        m_render->DrawGrid();
    }
    camera->GetPostProcessing()->EndSkybox();

    camera->GetPostProcessing()->Complete();

    if (m_requireGetAimed) {
        if (m_aimedCameraTarget == camera && m_aimedWindowTarget) {
            m_render->DrawSingleColors();

            glm::vec2 pos = GetGlobalWindowMousePos(camera, m_aimedWindowTarget);
            glm::vec3 color = m_env->GetPixelColor(pos);

            m_env->ClearBuffers();

            auto id = m_render->GetColorBuffer()->GetSelectColorObject(color);
            if (id != std::numeric_limits<size_t>::max())
                this->m_aimedMesh = this->m_render->GetMesh(id);
            m_requireGetAimed = false;
        }
    }
}

void Framework::Graphics::Window::CentralizeCursor() noexcept {
    if (m_isRun) {
        m_env->SetCursorPosition({ m_env->GetWindowFormat()->Width() / 2,  m_env->GetWindowFormat()->Height() / 2});
    }else{
        Debug::Error("Window::CentralizeCursor() : window is not run!");
    }
}

void Framework::Graphics::Window::PollEvents() {
    if (m_countNewCameras > 0) {
        m_camerasMutex.lock();

        for (size_t t = 0; t < m_countNewCameras; t++){
            m_newCameras[t]->Create(this);
            m_cameras.push_back(m_newCameras[t]);
            m_countCameras++;
        }

        m_newCameras.clear();
        m_countNewCameras = 0;

        m_render->SetCurrentCamera(nullptr);
        m_camerasMutex.unlock();
    }

    if (m_countCamerasToDestroy > 0) {
        m_camerasMutex.lock();

        for (Camera* camera : m_camerasToDestroy)
            for (size_t t = 0; t < m_countCameras; t++) {
                if (camera == m_cameras[t]) {
                    //if(Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
                        Helper::Debug::Log("Window::PoolEvents() : remove camera...");

                    m_cameras.erase(m_cameras.begin() + t);
                    m_countCameras--;
                    camera->Free();
                    //camera->SetUse(false);
                }
            }

        m_camerasToDestroy.clear();
        m_countCamerasToDestroy = 0;

        m_render->SetCurrentCamera(nullptr);
        m_camerasMutex.unlock();
    }

    if (m_isNeedResize) { // TODO
        //unsigned int w =  m_env->GetWindowFormat()->Width();
        //unsigned int h =  m_env->GetWindowFormat()->Height();

        unsigned int w = this->m_newWindowSize.x;
        unsigned int h = this->m_newWindowSize.y;

        m_env->SetWindowSize(w, h);

        //Framework::Graphics::Environment::g_callback(Environment::WinEvents::Resize, nullptr, &w, &h);
        this->m_isNeedResize = false;
    }

    if (m_isNeedMove) { // TODO
        int x = m_newWindowPos.x;
        int y = m_newWindowPos.y;
        //Framework::Graphics::Environment::g_callback(Environment::WinEvents::Move, nullptr, &x, &y);

        m_env->SetWindowPosition(x, y);

        this->m_isNeedMove = false;
    }
}

bool Framework::Graphics::Window::Free() {
    if (m_isClose) {
        Debug::Info("Window::Free() : free window pointer...");

        if (m_canvas)
            this->m_canvas->Free();

        delete this;
        return true;
    }
    else
        return false;
}

bool Framework::Graphics::Window::SetCanvas(Framework::Graphics::GUI::ICanvas *canvas) {
    if (m_canvas){
        Helper::Debug::Error("Window::SetCanvas() : canvas already setted!");
        return false;
    } else
        Debug::Graph("Window::SetCanvas() : setting canvas...");

    this->m_canvas = canvas;

    return true;
}

void Framework::Graphics::Window::Resize(unsigned int w, unsigned int h) {
    this->m_newWindowSize = { w, h };
    this->m_isNeedResize = true;
}

void Framework::Graphics::Window::CentralizeWindow() {
    ret:
    if (m_isNeedResize)
        goto ret;

    glm::vec2 scr_size = m_env->GetScreenSize();

    unsigned int w = m_env->GetWindowSize().x;
    unsigned int h = m_env->GetWindowSize().y;

    w = (int) (scr_size.x - (float)w) / 2;
    h = (int) (scr_size.y - (float)h) / 2;

    this->m_newWindowPos = { w, h + 20 }; // TODO: SEE
    this->m_isNeedMove = true;
}

glm::vec2 Framework::Graphics::Window::GetGlobalWindowMousePos(Framework::Graphics::Camera *camera, ImGuiWindow *aimedWindowTarget) {
    glm::vec2 win_pos = { aimedWindowTarget->Pos.x, aimedWindowTarget->Pos.y };
    glm::vec2 win_size = { aimedWindowTarget->Size.x, aimedWindowTarget->Size.y };
    glm::vec2 window_size = this->GetWindowSize().ToGLM();
    glm::vec2 img_size = camera->GetSize().ToGLM();

    glm::vec2 pos = m_env->GetMousePos();

    const float dx = win_size.x / img_size.x;
    const float dy = win_size.y / img_size.y;

    if (dy > dx)
        img_size *= dx;
    else
        img_size *= dy;

    // Вычисляем положение мыши в окне относительно изображения н окне интерфейса

    pos -= win_pos;
    pos *= (window_size / win_size);

    pos -= ((win_size - img_size) / 2.f) * window_size / win_size;
    pos *= win_size / img_size;

    pos.y = window_size.y - pos.y;

    return pos;
}

bool Framework::Graphics::Window::RequireAimedMesh(Framework::Graphics::Camera *camera, ImGuiWindow *window) noexcept  {
    if (this->m_requireGetAimed)
        return false;

    this->m_requireGetAimed = true;

    this->m_aimedCameraTarget = camera;
    this->m_aimedWindowTarget = window;
    this->m_aimedMesh = nullptr;

    return true;
}

Framework::Graphics::Types::Mesh *Framework::Graphics::Window::PopAimedMesh() noexcept  {
    if (m_aimedMesh) {
        Types::Mesh* aim = m_aimedMesh;
        m_aimedMesh = nullptr;
        return aim;
    } else
        return nullptr;
}

void Framework::Graphics::Window::DestroyCamera(Framework::Graphics::Camera *camera) {
    Debug::Log("Window::RemoveCamera() : register camera to remove...");
    if (!camera)
    {
        Debug::Error("Window::RemoveCamera() : camera is nullptr! The application will now crash...");
        return;
    }
    m_camerasMutex.lock();
    m_camerasToDestroy.push_back(camera);
    m_countCamerasToDestroy++;
    m_camerasMutex.unlock();
}

void Framework::Graphics::Window::AddCamera(Framework::Graphics::Camera *camera)  {
    Debug::Log("Window::AddCamera() : register new camera...");
    m_camerasMutex.lock();
    //camera->SetUse(true);
    m_newCameras.push_back(camera);
    m_countNewCameras++;
    m_camerasMutex.unlock();
} //TODO: mutex

                                                           