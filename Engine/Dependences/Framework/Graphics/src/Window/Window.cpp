//
// Created by Nikita on 18.11.2020.
//

#include "Window/Window.h"
#include <Debug.h>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <Input/Input.h>

#include <GUI/Canvas.h>

using namespace Framework::Helper;

bool Framework::Graphics::Window::Create() {
    if (m_isCreate) {
        Debug::Error("Window::Create() : window already create!");
        return false;
    }

    Debug::Graph("Window::Create() : creating window...");

    if (!this->m_render->Create(this)){ //, m_camera
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

        w = (int) (scr_size.x - (float)w) / 2;
        h = (int) (scr_size.y - (float)h) / 2;

        Framework::Graphics::Environment::g_callback(Environment::WinEvents::Move, nullptr, &w, &h);
    }

    while(m_isRun && !m_hasErrors && !m_isClose && this->m_env->IsWindowOpen()) {
        this->m_env->PoolEvents();

        this->PoolEvents();

        this->m_env->ClearColorBuffers(0.2, 0.2, 0.2, 1.0);
        this->m_env->ClearBuffers();

        this->m_render->PoolEvents();

        for (Camera* camera : m_cameras) {
            if (!camera->IsActive())
                continue;

            this->m_render->SetCurrentCamera(camera);

            camera->GetPostProcessing()->Begin();
            {
                // some drawing code
                // this is window context

                this->m_render->DrawSkybox();

                this->m_render->DrawGeometry();

                this->m_render->DrawTransparentGeometry();
            }
            camera->GetPostProcessing()->End();
        }

        this->m_env->SwapBuffers();
    }

    Debug::Graph("Window::Thread() : exit from main cycle.");

    GUI::Canvas::Get()->Stop();

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

    GUI::Canvas::Get()->Init();

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

void Framework::Graphics::Window::Draw() {

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

    if (m_countCamerasToRemove) {
        m_camerasMutex.lock();

        for (Camera* camera : m_camerasToRemove)
            for (size_t t = 0; t < m_countCameras; t++) {
                if (camera == m_cameras[t]) {
                    m_cameras.erase(m_cameras.begin() + t);
                    m_countCameras--;
                    camera->SetUse(false);
                }
            }

        m_camerasToRemove.clear();
        m_countCamerasToRemove = 0;

        m_camerasMutex.unlock();
    }
}

bool Framework::Graphics::Window::Free() {
    if (m_isClose) {
        Debug::Info("Window::Free() : free window pointer...");
        delete this;
        return true;
    }
    else
        return false;
}
