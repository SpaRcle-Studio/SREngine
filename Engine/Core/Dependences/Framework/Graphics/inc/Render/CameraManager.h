//
// Created by Monika on 05.06.2022.
//

#ifndef SRENGINE_CAMERAMANAGER_H
#define SRENGINE_CAMERAMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Types/SafePointer.h>

namespace SR_GRAPH_NS {
    class Camera;
    class Window;

    class CameraManager : public SR_UTILS_NS::Singleton<CameraManager> {
        friend class Camera;
        friend class SR_UTILS_NS::Singleton<CameraManager>;
        using CameraPtr = Camera*;
    protected:
        ~CameraManager() override = default;

    public:
        void Update();

        void OnWindowResized(Window* pWindow, uint32_t width, uint32_t height);

        SR_NODISCARD uint32_t GetCountCameras() const;
        SR_NODISCARD CameraPtr GetFirstCamera() const;
        SR_NODISCARD std::list<CameraPtr> GetCameras() const;

    protected:
        void OnSingletonDestroy() override;

    private:
        void RegisterCamera(const CameraPtr& camera);
        void DestroyCamera(const CameraPtr& camera);

    private:
        std::map<CameraPtr, bool> m_cameras;

    };
}

#endif //SRENGINE_CAMERAMANAGER_H
