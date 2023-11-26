//
// Created by Monika on 18.12.2022.
//

#include <Utils/World/SceneUpdater.h>
#include <Utils/World/Scene.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Component.h>
#include <Utils/Types/Function.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_WORLD_NS {
    SceneUpdater::SceneUpdater(Scene *pScene)
        : Super()
        , m_scene(pScene)
    {
        m_updatableComponents.reserve(1024);
    }

    void SceneUpdater::Build(bool isPaused) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        if (!m_dirty) {
            return;
        }

        m_dirty = false;

        m_lastBuildTimePoint = SR_HTYPES_NS::Time::Instance().Now();

        auto&& root = m_scene->GetRootGameObjects();

        m_scene->PostLoad(false);
        m_scene->Awake(false, isPaused);
        m_scene->CheckActivity(false);
        m_scene->Start(false);

        for (auto&& gameObject : root) {
            gameObject->PostLoad(false);
        }

        for (auto&& gameObject : root) {
            gameObject->Awake(false, isPaused);
        }

        for (auto&& gameObject : root) {
            gameObject->CheckActivity(false);
        }

        for (auto&& gameObject : root) {
            gameObject->Start(false);
        }
    }

    void SceneUpdater::Update(float_t dt) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        for (uint32_t i = 0; i < m_componentsPoolSize; ++i) {
            auto&& pComponent = m_updatableComponents[i];
            if (!pComponent) {
                continue;
            }
            pComponent->Update(dt);
        }
    }

    void SceneUpdater::FixedUpdate() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        for (uint32_t i = 0; i < m_componentsPoolSize; ++i) {
            auto&& pComponent = m_updatableComponents[i];
            if (!pComponent) {
                continue;
            }
            pComponent->FixedUpdate();
        }
    }

    void SceneUpdater::SetDirty() {
        m_dirty = true;
    }

    void SceneUpdater::RegisterComponent(SR_UTILS_NS::Component* pComponent) {
        SetDirty();

        SRAssert2(pComponent->GetIndexInSceneUpdater() == SR_ID_INVALID, "Double component registration!");

        if (m_freeComponentIds.empty()) {
            pComponent->SetIndexIdSceneUpdater(static_cast<int32_t>(m_componentsPoolSize));
            ++m_componentsPoolSize;
            m_updatableComponents.emplace_back(pComponent);
        }
        else {
            const auto index = static_cast<int32_t>(m_freeComponentIds.front());
            m_freeComponentIds.pop_front();
            pComponent->SetIndexIdSceneUpdater(index);
            m_updatableComponents[index] = pComponent;
        }
    }

    void SceneUpdater::UnRegisterComponent(SR_UTILS_NS::Component* pComponent) {
        SetDirty();

        auto&& index = pComponent->GetIndexInSceneUpdater();

        if (static_cast<uint32_t>(index) >= m_componentsPoolSize) {
            SRHalt("Invalid component index!");
            return;
        }

        pComponent->SetIndexIdSceneUpdater(SR_ID_INVALID);
        m_freeComponentIds.emplace_back(index);
        m_updatableComponents[index] = nullptr;
    }
}
