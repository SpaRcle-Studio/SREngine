//
// Created by Monika on 24.12.2022.
//

#include <Utils/World/ScenePrefabLogic.h>

namespace SR_WORLD_NS {
    ScenePrefabLogic::ScenePrefabLogic(const SceneLogic::ScenePtr& scene)
        : Super(scene)
    { }

    bool ScenePrefabLogic::Save(const Path& path) {
        auto&& pMarshal = m_scene->SaveComponents(nullptr, SAVABLE_FLAG_NONE);

        SR_THIS_THREAD->GetContext()->SetValue<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3());

        auto&& root = m_scene->GetRootGameObjects();

        pMarshal->Write(static_cast<uint64_t>(root.size()));

        for (auto&& gameObject : root) {
            if (gameObject.RecursiveLockIfValid()) {
                pMarshal = gameObject->Save(pMarshal, SAVABLE_FLAG_ECS_NO_ID);
                gameObject.Unlock();
            }
        }

        SR_THIS_THREAD->GetContext()->RemoveValue<SR_MATH_NS::FVector3>();

        const bool result = pMarshal->Save(path);
        SR_SAFE_DELETE_PTR(pMarshal);
        return result;
    }

    bool ScenePrefabLogic::Load(const Path &path) {
        SR_THIS_THREAD->GetContext()->SetValue<SR_MATH_NS::FVector3>(SR_MATH_NS::FVector3());

        auto&& pMarshal = SR_HTYPES_NS::Marshal::LoadPtr(path);
        if (!pMarshal) {
            SR_ERROR("ScenePrefabLogic::Load() : failed to load marshal data!\n\tPath: " + path.ToString());
            return false;
        }

        /// ----------------------------------

        auto&& components = SR_UTILS_NS::ComponentManager::Instance().LoadComponents(*pMarshal);
        for (auto&& pComponent : components) {
            m_scene->LoadComponent(pComponent);
        }

        /// ----------------------------------

        const uint64_t count = pMarshal->Read<uint64_t>();
        for (uint64_t i = 0; i < count; ++i) {
            m_scene->Instance(*pMarshal);
        }

        /// ----------------------------------

        SR_THIS_THREAD->GetContext()->RemoveValue<SR_MATH_NS::FVector3>();

        SR_SAFE_DELETE_PTR(pMarshal);

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