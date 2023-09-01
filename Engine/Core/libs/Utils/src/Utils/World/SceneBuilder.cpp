//
// Created by Monika on 18.12.2022.
//

#include <Utils/World/SceneBuilder.h>
#include <Utils/World/Scene.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Component.h>
#include <Utils/Types/Function.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_WORLD_NS {
    SceneBuilder::SceneBuilder(Scene *pScene)
        : Super()
        , m_scene(pScene)
    { }

    void SceneBuilder::Build(bool isPaused) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD

        Initialize(isPaused);

        if (!m_dirty) {
            return;
        }

        m_lastBuildTimePoint = SR_HTYPES_NS::Time::Instance().Now();

        m_componentsCapacity = m_updatableComponents.capacity();
        m_updatableComponents.clear();
        m_updatableComponents.reserve(m_componentsCapacity);

        for (auto&& pComponent : m_scene->GetComponents()) {
            if (isPaused && !pComponent->ExecuteInEditMode()) {
                continue;
            }

            if (pComponent->IsUpdatable()) {
                m_updatableComponents.emplace_back(pComponent);
            }
        }

        SR_HTYPES_NS::Function<void(const SR_UTILS_NS::GameObject::Ptr& ptr)> function;

        function = [&](const SR_UTILS_NS::GameObject::Ptr& ptr) {
            if (!ptr->IsEnabled()) {
                return;
            }

            for (auto&& pComponent : ptr->GetComponents()) {
                if (isPaused && !pComponent->ExecuteInEditMode()) {
                    continue;
                }

                if (pComponent->IsUpdatable()) {
                    m_updatableComponents.emplace_back(pComponent);
                }
            }

            for (auto&& children : ptr->GetChildrenRef()) {
                function(children);
            }
        };

        auto&& root = m_scene->GetRootGameObjects();

        for (auto&& gameObject : root) {
            function(gameObject);
            gameObject->SetDirty(false);
        }

        m_scene->SetDirty(false);

        m_dirty = false;
    }

    void SceneBuilder::Update(float_t dt) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD

        auto&& pIt = m_updatableComponents.begin();

    retry:
        if (m_dirty || pIt == m_updatableComponents.end()) {
            return;
        }

        (*pIt)->Update(dt);

        if (pIt == m_updatableComponents.end()) {
            return;
        }

        ++pIt;

        goto retry;
    }

    void SceneBuilder::FixedUpdate() {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD

        auto&& pIt = m_updatableComponents.begin();

    retry:
        if (m_dirty || pIt == m_updatableComponents.end()) {
            return;
        }

        (*pIt)->FixedUpdate();

        if (pIt == m_updatableComponents.end()) {
            return;
        }

        ++pIt;

        goto retry;
    }

    void SceneBuilder::SetDirty() {
        m_dirty = true;
    }

    void SceneBuilder::Initialize(bool isPaused) {
        SR_TRACY_ZONE;

        auto&& root = m_scene->GetRootGameObjects();

        m_dirty |= m_scene->IsDirty();

        m_scene->PostLoad(false);
        m_scene->Awake(false, isPaused);
        m_scene->CheckActivity(false);
        m_scene->Start(false);

        for (auto&& gameObject : root) {
            m_dirty |= gameObject->IsDirty();
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
}
