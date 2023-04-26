//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/AnimationKey.h>
#include <Graphics/Animations/AnimationData.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_ANIMATIONS_NS {
    void TranslationKey::Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) {
        if (!pData->translation.has_value()) {
            pData->translation = SR_MATH_NS::FVector3::Zero();
        }

        if (!pStaticData->translation.has_value()) {
            return;
        }

        if (auto&& pKey = dynamic_cast<TranslationKey*>(pPreviousKey)) {
            //pData->translation.value() = pData->translation.value()
            //        .Lerp(pKey->m_translation
            //        .Lerp(m_translation, progress), weight);

            //pData->translation.value() = pData->translation.value().Lerp(pData->translation.value() + pKey->m_delta.Lerp(m_delta, progress), weight);
            //pData->translation.value() = pData->translation.value().Lerp(pData->translation.value() + m_delta, progress);
            //pData->translation.value() += m_delta.Lerp(SR_MATH_NS::FVector3::Zero(), 1.f - progress);
            //pData->translation = pData->translation.value().Lerp(pStaticData->translation.value() + m_delta, progress * weight);

            auto&& newValue = (pKey->m_delta + pStaticData->translation.value()).Lerp(pStaticData->translation.value() + m_delta, progress);
            pData->translation = pData->translation->Lerp(newValue, weight);
        }
        else {
            //pData->translation.value() = pData->translation.value().Lerp(m_translation, weight);
            //pData->translation.value() = pData->translation.value().Lerp(pData->translation.value() + m_delta, weight);
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
        if (!pData->rotation.has_value()) {
            pData->rotation = SR_MATH_NS::Quaternion::Identity();
        }

        if (!pStaticData->rotation.has_value()) {
            return;
        }

        if (auto&& pKey = dynamic_cast<RotationKey*>(pPreviousKey)) {
            //pData->rotation.value() = pData->rotation.value()
            //        .Slerp(pKey->m_rotation
            //        .Slerp(m_rotation, progress), weight);

            //auto&& delta = m_delta.Slerp(SR_MATH_NS::Quaternion::Identity(), 1.f - weight);
            //pData->rotation.value() *= pKey->m_delta.Slerp(delta, progress);

            //pData->rotation = pData->rotation.value().Slerp(pData->rotation.value() * m_delta, progress);
            //pData->rotation = pData->rotation.value().Slerp(pData->rotation.value() * m_delta, progress);
            //pData->rotation.value() *= m_delta.Slerp(SR_MATH_NS::Quaternion::Identity(), 1.f - progress);
            //pData->rotation = pData->rotation.value().Slerp(pStaticData->rotation.value() * m_delta, progress * weight);
            auto&& newValue = (pKey->m_delta * pStaticData->rotation.value()).Slerp(m_delta * pStaticData->rotation.value(), progress);
            pData->rotation = pData->rotation->Slerp(newValue, weight);
        }
        else {
            //pData->rotation.value() = pData->rotation.value().Slerp(m_rotation, weight);
            //pData->rotation.value() *= m_delta.Slerp(SR_MATH_NS::Quaternion::Identity(), 1.f - weight);
            //pData->rotation.value() *= m_delta;
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

    void ScalingKey::Set(float_t weight, AnimationData* pData) {
        if (!pData->scale.has_value()) {
            pData->scale = SR_MATH_NS::FVector3::One();
        }

        pData->scale = pData->scale->Lerp(m_scaling, weight);
    }
}
