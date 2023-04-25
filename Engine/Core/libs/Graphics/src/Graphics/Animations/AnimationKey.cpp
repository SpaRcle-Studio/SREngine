//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/AnimationKey.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_ANIMATIONS_NS {
    void TranslationKey::Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData) {
        if (!pData->translation.has_value()) {
            pData->translation = SR_MATH_NS::FVector3::Zero();
        }

        if (auto&& pKey = dynamic_cast<TranslationKey*>(pPreviousKey)) {
            pData->translation.value() = pData->translation.value()
                    .Lerp(pKey->m_translation
                    .Lerp(m_translation, progress), weight);
        }
        else {
            pData->translation.value() = pData->translation.value().Lerp(m_translation, weight);
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void RotationKey::Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData) {
        if (!pData->rotation.has_value()) {
            pData->rotation = SR_MATH_NS::Quaternion::Identity();
        }

        if (auto&& pKey = dynamic_cast<RotationKey*>(pPreviousKey)) {
            pData->rotation.value() = pData->rotation.value()
                    .Slerp(pKey->m_rotation
                    .Slerp(m_rotation, progress), weight);
        }
        else {
            pData->rotation.value() = pData->rotation.value().Slerp(m_rotation, weight);
        }
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void ScalingKey::Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData) {
        if (!pData->scale.has_value()) {
            pData->scale = SR_MATH_NS::FVector3::One();
        }

        if (auto&& pKey = dynamic_cast<ScalingKey*>(pPreviousKey)) {
            pData->scale.value() = pData->scale.value()
                    .Lerp(pKey->m_scaling
                    .Lerp(m_scaling, progress), weight);
        }
        else {
            pData->scale.value() = pData->scale.value().Lerp(m_scaling, weight);
        }
    }
}
