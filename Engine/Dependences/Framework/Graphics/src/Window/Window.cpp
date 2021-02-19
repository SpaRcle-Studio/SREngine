//
// Created by Nikita on 18.11.2020.
//

#include <easy/profiler.h>

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
                float ratio = m_format.GetRatio();
                m_env->SetWindowSize(ratio, *(int *) arg1, *(int *) arg2);
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

    {
        glm::vec2 scr_size = m_env->GetScreenSize();

        unsigned int w = m_format.Width();
        unsigned int h = m_format.Height();
        Framework::Graphics::Environment::g_callback(Environment::WinEvents::Resize, nullptr, &w, &h);

        Debug::Log("Window::Thread() : screen size is " +
            std::to_string((int) scr_size.x) + "x" + std::to_string((int) scr_size.y));

        this->CentralizeWindow();

        //w = (int) (scr_size.x - (float)w) / 2;
        //h = (int) (scr_size.y - (float)h) / 2;

        //Framework::Graphics::Environment::g_callback(Environment::WinEvents::Move, nullptr, &w, &h);
    }

    while(m_isRun && !m_hasErrors && !m_isClose && this->m_env->IsWindowOpen()) {
        if (Helper::Debug::Profile()) { EASY_FUNCTION(profiler::colors::Magenta); }

        this->m_env->PoolEvents();

        this->PoolEvents();

        this->m_env->ClearBuffers();

        this->m_render->PoolEvents();

        this->Draw();

        this->m_env->SwapBuffers();
    }

    Debug::Graph("Window::Thread() : exit from main cycle.");

    m_env->StopGUI();

    if (!this->m_render->Close()) {
        Debug::Error("Window::Thread() : failed close render!");
    }

    Debug::Info("Window::Thread() : stopping window thread...");

    this->m_isWindowClose = true;
}

bool Framework::Graphics::Window::InitEnvironment() {
    Debug::Graph("Window::InitEnvironment() : initializing render environment...");

    Debug::Graph("Window::InitEnvironment() : pre-initializing...");
    if (!this->m_env->PreInit(m_smoothSamples)){
        Debug::Graph("Window::InitEnvironment() : failed pre-initializing!");
        return false;
    }

    Debug::Graph("Window::InitEnvironment() : creating window...");
    if (!this->m_env->MakeWindow(this->m_win_name, &m_format, m_fullScreen)) {
        Debug::Error("Window::InitEnvironment() : failed creating window!");
        return false;
    }

    Debug::Graph("Window::InitEnvironment() : set context current...");
    this->m_env->SetContextCurrent();

    {
        this->m_env->PreInitGUI(Helper::ResourceManager::GetResourcesFolder() + "\\Fonts\\CalibriL.ttf");
        GUI::ICanvas::InitStyle();
        this->m_env->InitGUI();
    }

    Debug::Graph("Window::InitEnvironment() : initializing environment...");
    this->m_env->Init();

    Debug::Graph("Window::InitEnvironment() : post-initializing environment...");
    this->m_env->PostInit();

    {
        Debug::Log("Window::InitEnvironment() : vendor is "   + m_env->GetVendor());
        Debug::Log("Window::InitEnvironment() : renderer is " + m_env->GetRenderer());
        Debug::Log("Window::InitEnvironment() : version is "  + m_env->GetVersion());
    }

    m_isEnvInit = true;

    return true;
}

void Framework::Graphics::Window::FindAimedMesh() {
    //this->m_render->SetCurrentCamera(m_aimedCameraTarget);

    //this->m_env->ClearBuffers();
}

void Framework::Graphics::Window::Draw() {
    if (m_GUIEnabled)
        this->m_env->BeginDrawGUI();

    for (Camera* camera : m_cameras) {
        if (!camera->IsActive())
            continue;

        this->m_render->SetCurrentCamera(camera);

        camera->GetPostProcessing()->BeginSkybox();
        {
            this->m_render->DrawSkybox();
            this->m_render->DrawGrid();
        }
        camera->GetPostProcessing()->EndSkybox();

        camera->GetPostProcessing()->Begin();
        {
            // some drawing code
            // this is window context

            this->m_render->DrawGeometry();

            this->m_render->DrawTransparentGeometry();
        }
        camera->GetPostProcessing()->End();

        //!-----------------------------------------------------------------------------//

        if (m_requireGetAimed && m_aimedCameraTarget == camera && m_aimedWindowTarget) {
            //this->FindAimedMesh();
            //if (!this->m_colorBuffer)
            //    this->m_colorBuffer = new ColorBuffer();

            //this->m_colorBuffer->InitNames(this->m_render->GetAbsoluteCountMeshes());

            this->m_render->DrawSingleColors();

            glm::vec2 pos = this->GetGlobalWindowMousePos(camera, m_aimedWindowTarget);
            glm::vec3 color = this->m_env->GetPixelColor(pos);
            //glm::u8vec3 uColor = { color.x, color.y, color.z };

            this->m_env->ClearBuffers();

            int id = this->m_render->GetColorBuffer()->GetSelectColorObject(color);

            /*ImGui::Begin("Debug");
            ImGui::Text("Mouse pos: %s", glm::to_string(pos).c_str());
            ImGui::Text("ID: %s", std::to_string(id).c_str());
            ImGui::Text("uColor: %s", glm::to_string(color).c_str());
            //ImGui::Text("Color: %s", glm::to_string(uColor).c_str());
            ImGui::ColorEdit3("Pick", &(color / 255.f)[0]);
            ImGui::End();*/

            if (id != -1)
                this->m_aimedMesh = this->m_render->GetMesh(id);

            m_requireGetAimed = false;
        }
    }

    if (m_GUIEnabled) {
        if (m_canvas)
            this->m_canvas->Draw();

        this->m_env->EndDrawGUI();
    }
}

void Framework::Graphics::Window::CentralizeCursor() noexcept {
    if (m_isRun) {
        m_env->SetCursorPosition({m_format.Width() / 2, m_format.Height() / 2});
    }else{
        Debug::Error("Window::CentralizeCursor() : window is not run!");
    }
}

void Framework::Graphics::Window::PoolEvents() {
    if (m_countNewCameras) {
        m_camerasMutex.lock();

        for (size_t t = 0; t < m_countNewCameras; t++){
            m_newCameras[t]->Create(this);
            m_cameras.push_back(m_newCameras[t]);
            m_countCameras++;
        }

        m_newCameras.clear();
        m_countNewCameras = 0;

        m_camerasMutex.unlock();
    }

    if (m_countCamerasToDestroy) {
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

        m_camerasMutex.unlock();
    }

    if (m_isNeedResize) {
        unsigned int w = m_format.Width();
        unsigned int h = m_format.Height();
        Framework::Graphics::Environment::g_callback(Environment::WinEvents::Resize, nullptr, &w, &h);
        this->m_isNeedResize = false;
    }

    if (m_isNeedMove) {
        unsigned int x = m_newWindowPos.x;
        unsigned int y = m_newWindowPos.y;
        Framework::Graphics::Environment::g_callback(Environment::WinEvents::Move, nullptr, &x, &y);
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
    this->m_format.SetFreeValue(w, h);
    this->m_isNeedResize = true;
}

void Framework::Graphics::Window::CentralizeWindow() {
    glm::vec2 scr_size = m_env->GetScreenSize();

    unsigned int w = m_format.Width();
    unsigned int h = m_format.Height();

    w = (int) (scr_size.x - (float)w) / 2;
    h = (int) (scr_size.y - (float)h) / 2;

    this->m_newWindowPos = { w, h + 20 }; // TODO: SEE
    this->m_isNeedMove = true;
}

glm::vec2 Framework::Graphics::Window::GetGlobalWindowMousePos(Framework::Graphics::Camera *camera, ImGuiWindow *win) {
    glm::vec2 win_pos = { m_aimedWindowTarget->Pos.x, m_aimedWindowTarget->Pos.y };
    glm::vec2 win_size = { m_aimedWindowTarget->Size.x, m_aimedWindowTarget->Size.y };
    glm::vec2 window_size = this->GetWindowSize();
    glm::vec2 img_size = camera->GetSize();

    glm::vec2 pos = m_env->GetMousePos();

    const float dx = win_size.x / img_size.x;
    const float dy = win_size.y / img_size.y;

    if (dy > dx)
        img_size *= dx;
    else
        img_size *= dy;

    // Вычисляем положение мыши в окне относительно изображения н окне интерфейса

    pos -= win_pos;
    pos *= window_size / win_size;

    pos -= ((win_size - img_size) / 2.f) * window_size / win_size;
    pos *= win_size / img_size;

    pos.y = window_size.y - pos.y;

    return pos;
}





/*
bool Framework::Graphics::Window::AddFunctionAtContext(const std::string &funName, std::function<void(void)> fun) {
    m_contexFuncsMutex.lock();

    auto find = m_contextFuncs.find(funName);
    if (find != m_contextFuncs.end()) {
        Debug::Error("Window::AddFunctionAtContext() : function \""+funName+"\" already exists!");
        m_contexFuncsMutex.unlock();
        return false;
    }

    Debug::Graph("Window::AddFunctionAtContext() : register new function \""+funName+"\"...");

    this->m_contextFuncs.insert(std::make_pair(funName, fun));
    this->m_countContextFuncs++;

    m_contexFuncsMutex.unlock();
    return true;
}

bool Framework::Graphics::Window::RemoveFunctionFromContext(const std::string &funName) {
    m_contexFuncsMutex.lock();

    auto find = m_contextFuncs.find(funName);
    if (find == m_contextFuncs.end()) {
        Debug::Error("Window::RemoveFunctionFromContext() : function \""+funName+"\" is not exists!");
        m_contexFuncsMutex.unlock();
        return false;
    }

    Debug::Graph("Window::RemoveFunctionFromContext() : remove function \""+funName+"\"...");

    m_countContextFuncs--;
    m_contextFuncs.erase(find);

    m_contexFuncsMutex.unlock();
    return true;
}*/