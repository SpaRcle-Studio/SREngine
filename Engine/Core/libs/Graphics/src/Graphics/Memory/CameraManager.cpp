//
// Created by Monika on 05.06.2022.
//

#include <Utils/Types/Thread.h>

#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_GRAPH_NS::Memory {
    void CameraManager::Update() {
        SR_LOCK_GUARD

        for (auto pIt = m_cameras.begin(); pIt != m_cameras.end();) {
            auto /** copy */ [pCamera, info] = *pIt;

            if (info.destroyed) {
                SR_LOG("CameraManager::Update() : free camera...");

                delete pCamera;

                pIt = m_cameras.erase(pIt);
            }
            else {
                ++pIt;
            }
        }
    }

    void CameraManager::OnWindowResized(Window *pWindow, uint32_t width, uint32_t height) {
        SR_LOCK_GUARD

        for (auto&&[camera, info] : m_cameras) {
            if (info.destroyed) {
                continue;
            }

           // camera->UpdateProjection(width, height);
        }
    }

    uint32_t CameraManager::GetCountCameras() const {
        SR_LOCK_GUARD

        return static_cast<uint32>(m_cameras.size());
    }

    CameraManager::CameraPtr CameraManager::GetFirstCamera() const {
        SR_LOCK_GUARD

        for (auto&&[camera, info] : m_cameras) {
            if (info.destroyed) {
                continue;
            }

            if (!camera->IsActive()) {
                continue;
            }

            return camera;
        }

        return CameraManager::CameraPtr();
    }

    CameraManager::CameraPtr CameraManager::GetMainCamera(RenderScene *pRScene) {
        SR_LOCK_GUARD

        CameraPtr pMainCamera = nullptr;
        int32_t priority = -1;

        for (auto&& [pCamera, info] : m_cameras) {
            if (info.destroyed) {
                continue;
            }

            if (info.pRenderScene.Get() != pRScene) {
                continue;
            }

            if (!pCamera->IsActive()) {
                continue;
            }

            if (pCamera->GetPriority() > priority) {
                pMainCamera = pCamera;
                priority = pCamera->GetPriority();
            }
        }

        return pMainCamera;
    }

    std::list<CameraManager::CameraPtr> CameraManager::GetOffScreenCameras(RenderScene *pRScene) {
        SR_LOCK_GUARD

        std::list<CameraManager::CameraPtr> list;

        for (auto&& [pCamera, info] : m_cameras) {
            if (info.destroyed) {
                continue;
            }

            if (info.pRenderScene.Get() != pRScene) {
                continue;
            }

            if (!pCamera->IsActive()) {
                continue;
            }

            if (pCamera->GetPriority() < 0) {
                list.emplace_back(pCamera);
            }
        }

        std::stable_sort(list.begin(), list.end(), [](CameraPtr lhs, CameraPtr rhs) {
            return lhs->GetPriority() < rhs->GetPriority();
        });

        return list;
    }

    std::list<CameraManager::CameraPtr> CameraManager::GetCameras() const {
        SR_LOCK_GUARD

        std::list<CameraPtr> cameras;

        for (auto&&[camera, info] : m_cameras) {
            if (info.destroyed) {
                continue;
            }

            if (!camera->IsActive()) {
                continue;
            }

            cameras.emplace_back(camera);
        }

        return cameras;
    }

    void CameraManager::OnSingletonDestroy() {
        Update();

        SRAssert(m_cameras.empty());

        Singleton::OnSingletonDestroy();
    }

    void CameraManager::RegisterCamera(const CameraPtr &pCamera) {
        SR_LOCK_GUARD

        SR_LOG("CameraManager::RegisterCamera() : register new camera...");

        CameraInfo info;

        info.destroyed = false;

        /// У каждой камеры должна быть свя сцена рендера, иначе будет непонятно куда рендерить
        if (auto&& scene = pCamera->GetScene(); scene.RecursiveLockIfValid()) {
            info.pRenderScene = scene->GetDataStorage().GetValueDef<RenderScenePtr>(RenderScenePtr());
            if (info.pRenderScene.Valid()) {
                info.pRenderScene->SetDirty();
            }
            else {
                SR_WARN("CameraManager::RegisterCamera() : render scene is invalid!");
            }
            scene.Unlock();
        }
        else {
            SRHalt("CameraManager::RegisterCamera() : scene is invalid!");
        }

        m_cameras.insert(std::make_pair(
                pCamera,
                info
        ));

        auto&& renderScene = info.pRenderScene;
        if (renderScene.RecursiveLockIfValid()) {
            renderScene->SetDirty();
            renderScene.Unlock();
        }
        else {
            /// TODO: remove this
            Environment::Get()->SetBuildState(false);
        }
    }

    void CameraManager::DestroyCamera(const CameraPtr &camera) {
        SR_LOCK_GUARD

        SR_LOG("CameraManager::Update() : destroy camera...");

        if (auto &&pIt = m_cameras.find(camera); pIt != m_cameras.end()) {
            auto&& [pCamera, info] = *pIt;
            auto&& renderScene = info.pRenderScene;

            info.destroyed = true;

            if (renderScene.LockIfValid()) {
                renderScene->SetDirty();
                renderScene.Unlock();
            }
            else {
                /// TODO: remove this
                Environment::Get()->SetBuildState(false);
            }
        }
        else {
            SRHalt("Camera is not registered!");
        }
    }

    bool CameraManager::IsRegistered(const CameraManager::CameraPtr &camera) const {
        SR_LOCK_GUARD
        return m_cameras.count(camera) != 0;
    }

    void CameraManager::UnRegisterCamera(CameraManager::CameraPtr const &camera) {
        SR_LOCK_GUARD

        SR_LOG("CameraManager::UnRegisterCamera() : unregister camera...");

        if (auto &&pIt = m_cameras.find(camera); pIt != m_cameras.end()) {
            auto&& [pCamera, info] = *pIt;
            auto&& renderScene = info.pRenderScene;

            SRAssert2(!info.destroyed, "Unregistering destroyed camera!");

            if (renderScene.LockIfValid()) {
                renderScene->SetDirty();
                renderScene.Unlock();
            }
            else {
                /// TODO: remove this
                Environment::Get()->SetBuildState(false);
            }
        }
        else {
            SRHalt("Camera is not registered!");
        }
    }

    bool CameraManager::IsDestroyed(const CameraManager::CameraPtr &camera) const {
        SR_LOCK_GUARD

        if (auto&& pIt = m_cameras.find(camera); pIt != m_cameras.end()) {
            return pIt->second.destroyed;
        }

        return false;
    }
}