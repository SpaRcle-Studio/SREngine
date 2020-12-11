//
// Created by Nikita on 18.11.2020.
//

#ifndef GAMEENGINE_WINDOW_H
#define GAMEENGINE_WINDOW_H

#include <Types/WindowFormat.h>

#include <Render/Render.h>
#include <Render/Camera.h>
#include <Environment/Environment.h>
#include <Render/PostProcessing.h>
#include <thread>
#include <mutex>

using namespace Framework::Graphics::Types;

namespace Framework::Graphics {
    class Window {
    public:
        Window(
                const char* win_name,
                WindowFormat format,
                Render* render,
                //Camera* camera,
                bool vsync,
                bool fullScreen,
                unsigned int smoothSamples
                )
                : m_env(Environment::Get())
        {
            this->m_win_name        = win_name;
            this->m_format          = format;
            this->m_render          = render;
            //this->m_camera          = camera;
            this->m_fullScreen      = fullScreen;
            this->m_vsync           = vsync;
            this->m_smoothSamples   = smoothSamples;
        }
    private:
        volatile bool           m_isCreate              = false;
        volatile bool           m_isInit                = false;
        volatile bool           m_isRun                 = false;
        volatile bool           m_isClose               = false;

        volatile bool           m_hasErrors             = false;
        volatile bool           m_isEnvInit             = false;
        volatile bool           m_isWindowClose         = false;

        volatile bool           m_isWindowFocus         = true;
    private:
        std::thread             m_thread                = std::thread();

        Environment*            m_env                   = nullptr;

        const char*             m_win_name              = "Unnamed";
        WindowFormat            m_format                = WindowFormat::Unknown;
        unsigned int            m_smoothSamples         = 4;

        Render*                 m_render                = nullptr;
        //Camera*                 m_camera                = nullptr;


        std::mutex              m_camerasMutex          = std::mutex();
        std::vector<Camera*>    m_newCameras            = std::vector<Camera*>();
        size_t                  m_countNewCameras       = 0;
        std::vector<Camera*>    m_camerasToRemove       = std::vector<Camera*>();
        size_t                  m_countCamerasToRemove  = 0;
        std::vector<Camera*>    m_cameras               = std::vector<Camera*>();
        size_t                  m_countCameras          = 0;

        //PostProcessing*         m_postProcessing        = nullptr;

        bool                    m_vsync                 = false;
        bool                    m_fullScreen            = false;

        glm::vec2               m_windowPos             = { 0,0 };
    private:
        void PoolEvents();
        void Thread();
        bool InitEnvironment();
        void Draw();
    public:
        inline void AddCamera(Camera* camera) {
            Debug::Log("Window::AddCamera() : register new camera...");
            m_camerasMutex.lock();
            camera->SetUse(true);
            m_newCameras.push_back(camera);
            m_countNewCameras++;
            m_camerasMutex.unlock();
        } //TODO: mutex
        inline void RemoveCamera(Camera* camera){
            Debug::Log("Window::RemoveCamera() : register camera to remove...");
            if (!camera)
            {
                Debug::Error("Window::RemoveCamera() : camera is nullptr! The application will now crash...");
                return;
            }
            m_camerasMutex.lock();
            m_camerasToRemove.push_back(camera);
            m_countCamerasToRemove++;
            m_camerasMutex.unlock();
        }

        inline Render* GetRender() { return m_render; }
        inline bool IsRun() const noexcept { return m_isRun; }
        //inline glm::mat4& GetProjection() noexcept { return this->m_projection; }
    public:
        void CentralizeCursor() noexcept;
    public:
        [[nodiscard]] inline bool IsWindowOpen() const noexcept { return !this->m_isWindowClose; }
        [[nodiscard]] inline bool IsWindowFocus() const noexcept { return this->m_isWindowFocus; }
    public:
        bool Create();
        bool Init();
        bool Run();
        bool Close();
    };
}

#endif //GAMEENGINE_WINDOW_H
