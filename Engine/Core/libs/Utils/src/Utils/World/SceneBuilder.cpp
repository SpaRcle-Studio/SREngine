//
// Created by Monika on 18.12.2022.
//

#include <Utils/World/SceneBuilder.h>

namespace SR_WORLD_NS {
    SceneBuilder::SceneBuilder(Scene *pScene)
        : Super()
        , m_scene(pScene)
    { }

    void SceneBuilder::Build(bool isPaused) {
        Initialize(isPaused);

        if (m_dirty) {
            const size_t capacity = m_updatableComponents.capacity();
            m_updatableComponents.clear();
            m_updatableComponents.reserve(capacity);

            for (auto&& pComponent : m_scene->GetComponents()) {
                if (isPaused && !pComponent->ExecuteInEditMode()) {
                    continue;
                }

                if (pComponent->IsCanUpdate()) {
                    m_updatableComponents.emplace_back(pComponent);
                }
            }

            SR_HTYPES_NS::Function<void(const SR_UTILS_NS::GameObject::Ptr& ptr)> function;

            function = [&](const SR_UTILS_NS::GameObject::Ptr& ptr) {
                for (auto&& pComponent : ptr->GetComponents()) {
                    if (isPaused && !pComponent->ExecuteInEditMode()) {
                        continue;
                    }

                    if (pComponent->IsCanUpdate()) {
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

            m_dirty = false;
        }
    }

    void SceneBuilder::Update(float_t dt) {
        for (auto&& pComponent : m_updatableComponents) {
            pComponent->Update(dt);
        }
    }

    void SceneBuilder::FixedUpdate() {
        for (auto&& pComponent : m_updatableComponents) {
            pComponent->FixedUpdate();
        }
    }

    void SceneBuilder::SetDirty() {
        m_dirty = true;
    }

    uint64_t SceneBuilder::Initialize(bool isPaused) {
        auto&& root = m_scene->GetRootGameObjects();

        m_dirty |= m_scene->IsDirty();

        m_scene->PostLoad();
        m_scene->Awake(isPaused);
        m_scene->CheckActivity();
        m_scene->Start();

        uint64_t rootHash = 0;

        for (auto&& gameObject : root) {
            m_dirty |= gameObject->IsDirty();
            rootHash = SR_UTILS_NS::HashCombine(gameObject.GetRawPtr(), rootHash);
            gameObject->PostLoad();
        }

        for (auto&& gameObject : root) {
            gameObject->Awake(isPaused);
        }

        for (auto&& gameObject : root) {
            gameObject->CheckActivity();
        }

        for (auto&& gameObject : root) {
            gameObject->Start();
        }

        return rootHash;
    }
}
