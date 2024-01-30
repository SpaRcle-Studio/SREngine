//
// Created by Monika on 24.12.2022.
//

#include <Utils/World/ScenePrefabLogic.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/LayerManager.h>

namespace SR_WORLD_NS {
    ScenePrefabLogic::ScenePrefabLogic(const SceneLogic::ScenePtr& scene)
        : Super(scene)
    {
        m_tag = SR_UTILS_NS::TagManager::Instance().GetDefaultTag();
        m_layer = SR_UTILS_NS::LayerManager::Instance().GetDefaultLayer();
    }

    bool ScenePrefabLogic::Save(const Path& path) {
        if (!Super::Save(path)) {
            SR_ERROR("ScenePrefabLogic::Save() : failed to save base logic!");
            return false;
        }

        auto&& pMarshal = new SR_HTYPES_NS::Marshal();

        pMarshal->Write(static_cast<uint64_t>(ENTITY_ID_MAX));
        pMarshal->Write(GameObject::VERSION);
        pMarshal->Write<bool>(false /** is prefab */);
        pMarshal->Write<bool>(true /** is enabled */);
        pMarshal->Write(m_scene->GetName());
        pMarshal->Write<uint64_t>(m_tag.GetHash());
        pMarshal->Write<uint64_t>(m_layer.GetHash());

        auto&& pTransformMarshal = Transform3D().Save(SR_UTILS_NS::SavableContext(nullptr, SAVABLE_FLAG_ECS_NO_ID));
        pMarshal->Write<uint64_t>(pTransformMarshal->Size());
        pMarshal->Append(pTransformMarshal);

        pMarshal = m_scene->SaveComponents(SR_UTILS_NS::SavableContext(pMarshal, SAVABLE_FLAG_ECS_NO_ID));

        auto&& root = m_scene->GetRootGameObjects();

        uint16_t childrenNum = 0;
        for (auto&& gameObject : root) {
            if (gameObject->IsDontSave()) {
                continue;
            }
            ++childrenNum;
        }

        pMarshal->Write(static_cast<uint16_t>(childrenNum));

        for (auto&& gameObject : root) {
            if (gameObject->IsDontSave()) {
                continue;
            }

            pMarshal = gameObject->Save(SR_UTILS_NS::SavableContext(pMarshal, SAVABLE_FLAG_ECS_NO_ID));
        }

        const bool result = pMarshal->Save(path);
        SR_SAFE_DELETE_PTR(pMarshal);
        return result;
    }

    bool ScenePrefabLogic::Load(const Path &path) {
        auto&& pPrefab = Prefab::Load(path);
        if (!pPrefab) {
            SR_ERROR("ScenePrefabLogic::Load() : failed to load prefab!\n\tPath: " + path.ToString());
            return false;
        }

        pPrefab->AddUsePoint();

        m_tag = pPrefab->GetData()->GetTag();
        m_layer = pPrefab->GetData()->GetLayer();

        for (auto&& pComponent : pPrefab->GetData()->GetLoadedComponents()) {
            if (auto&& pCopy = pComponent->CopyComponent()) {
                m_scene->AddComponent(pCopy);
            }
        }

        for (auto&& gameObject : pPrefab->GetData()->GetChildrenRef()) {
            /// при копировании объекта на сцену, он автоматически инстанциируется на ней
            SR_MAYBE_UNUSED auto&& copy = gameObject->Copy(m_scene->Get());
        }

        pPrefab->RemoveUsePoint();

        return true;
    }

    bool ScenePrefabLogic::Reload() {
        return SceneLogic::Reload();
    }

    void ScenePrefabLogic::Destroy() {
        SceneLogic::Destroy();
    }

    void ScenePrefabLogic::Update(float_t dt) {
        SceneLogic::Update(dt);
    }
}