//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/AnimationKey.h>
#include <Graphics/Animations/AnimationData.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_ANIMATIONS_NS {
    void TranslationKey::Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) {
        if (!pStaticData->translation.has_value()) {
            return;
        }

        if (!pData->translation.has_value()) {
            pData->translation = SR_MATH_NS::FVector3::Zero();
        }

        if (auto&& pKey = dynamic_cast<TranslationKey*>(pPreviousKey)) {
            auto&& newValue = (pKey->m_delta + pStaticData->translation.value()).Lerp(pStaticData->translation.value() + m_delta, progress);
            pData->translation = pData->translation->Lerp(newValue, weight);
        }
        else {
            pData->translation = pData->translation.value().Lerp(pStaticData->translation.value() + m_delta, weight);
        }
    }

    void TranslationKey::Set(float_t weight, AnimationData *pData) {
        if (!pData->translation.has_value()) {
            pData->translation = SR_MATH_NS::FVector3::Zero();
        }

        pData->translation = pData->translation.value().Lerp(m_translation, weight);
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void RotationKey::Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) {
        if (!pStaticData->rotation.has_value()) {
            return;
        }

        if (!pData->rotation.has_value()) {
            pData->rotation = SR_MATH_NS::Quaternion::Identity();
        }

        if (auto&& pKey = dynamic_cast<RotationKey*>(pPreviousKey)) {
            auto&& newValue = (pKey->m_delta * pStaticData->rotation.value()).Slerp(m_delta * pStaticData->rotation.value(), progress);
            pData->rotation = pData->rotation->Slerp(newValue, weight);
        }
        else {
            pData->rotation = pData->rotation.value().Slerp(pStaticData->rotation.value() * m_delta, weight);
        }
    }

    void RotationKey::Set(float_t weight, AnimationData *pData) {
        if (!pData->rotation.has_value()) {
            pData->rotation = SR_MATH_NS::Quaternion::Identity();
        }

        pData->rotation = pData->rotation.value().Slerp(m_rotation, weight);
    }

    /// ----------------------------------------------------------------------------------------------------------------

    void ScalingKey::Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) {
        if (!pStaticData->scale.has_value()) {
            return;
        }

        if (!pData->scale.has_value()) {
            pData->scale = SR_MATH_NS::FVector3::One();
        }

        if (auto&& pKey = dynamic_cast<ScalingKey*>(pPreviousKey)) {
            auto&& newValue = (pKey->m_delta * pStaticData->scale.value()).Lerp(pStaticData->scale.value() * m_delta, progress);
            pData->scale = pData->scale->Lerp(newValue, weight);
        }
        else {
            pData->scale = pData->scale.value().Lerp(pStaticData->scale.value() * m_delta, weight);
        }
    }

    void ScalingKey::Set(float_t weight, AnimationData* pData) {
        if (!pData->scale.has_value()) {
            pData->scale = SR_MATH_NS::FVector3::One();
        }

        pData->scale = pData->scale->Lerp(m_scaling, weight);
    }
}
