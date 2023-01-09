//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/AnimationKey.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_ANIMATIONS_NS {
    void TranslationKey::Update(double_t progress, AnimationKey* pPreviousKey, SR_UTILS_NS::GameObject *pRoot) {
        if (auto&& pKey = dynamic_cast<TranslationKey*>(pPreviousKey)) {
            pRoot->GetTransform()->SetTranslation(pKey->m_translation.Lerp(m_translation, progress));
        }
        else {
            pRoot->GetTransform()->SetTranslation(m_translation);
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void RotationKey::Update(double_t progress, AnimationKey* pPreviousKey, SR_UTILS_NS::GameObject* pRoot) {
        if (auto&& pKey = dynamic_cast<RotationKey*>(pPreviousKey)) {
            pRoot->GetTransform()->SetRotation(pKey->m_rotation.Slerp(m_rotation, progress));
        }
        else {
            pRoot->GetTransform()->SetRotation(m_rotation);
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void ScalingKey::Update(double_t progress, AnimationKey *pPreviousKey, SR_UTILS_NS::GameObject *pRoot) {
        if (auto&& pKey = dynamic_cast<ScalingKey*>(pPreviousKey)) {
            pRoot->GetTransform()->SetScale(pKey->m_scaling.Lerp(m_scaling, progress));
        }
        else {
            pRoot->GetTransform()->SetScale(m_scaling);
        }
    }
}
