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
        auto&& root = m_scene->GetRootGameObjects();

        uint64_t rootHash = 0;

        m_scene->PostLoad();

        for (auto&& gameObject : root) {
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

        /// WARNING: если произойдет коллизия хешей при уничтожении коренного объекта, то будет краш!
        if (rootHash == m_rootHash) {
            for (auto&& gameObject : root) {
                if (!gameObject->IsDirty()) {
                    continue;
                }

                SetDirty();
                break;
            }
        }
        else {
            SetDirty();
            m_rootHash = rootHash;
        }

        if (m_dirty) {
            const size_t capacity = m_updatableComponents.capacity();
            m_updatableComponents.clear();
            m_updatableComponents.reserve(capacity);

            for (auto&& pComponents : m_scene->GetComponents()) {

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

                    for (auto&& children : ptr->GetChildrenRef()) {
                        function(children);
                    }
                }
            };

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
}
