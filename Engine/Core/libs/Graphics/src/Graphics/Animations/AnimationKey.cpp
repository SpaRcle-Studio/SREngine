//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/AnimationKey.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform.h>

namespace SR_ANIMATIONS_NS {
    void TranslationKey::Update(float_t interval, SR_UTILS_NS::GameObject *pRoot) {
        SR_MATH_NS::FVector3 interpolation = pRoot->GetTransform()->GetTranslation();

        interpolation.x += (m_translation.x - interpolation.x) * interval;
        interpolation.y += (m_translation.y - interpolation.y) * interval;
        interpolation.z += (m_translation.z - interpolation.z) * interval;

        pRoot->GetTransform()->SetTranslation(interpolation);
    }
}
