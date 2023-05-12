//
// Created by Monika on 25.04.2023.
//

#ifndef SRENGINE_ANIMATIONDATA_H
#define SRENGINE_ANIMATIONDATA_H

#include <Graphics/Animations/AnimationCommon.h>

namespace SR_ANIMATIONS_NS {
    /// Ключи меняют данные в рамках одного объекта, смешивая значения
    /// После чего, в конце кадра данные применяются на объект
    class AnimationData : public SR_UTILS_NS::NonCopyable {
    public:
        void Reset() noexcept {
            if (translation.has_value()) {
                translation = std::nullopt;
            }
            if (rotation.has_value()) {
                rotation = std::nullopt;
            }
            if (scale.has_value()) {
                scale = std::nullopt;
            }
        }

    public:
        std::optional<SR_MATH_NS::FVector3> translation;
        std::optional<SR_MATH_NS::Quaternion> rotation;
        std::optional<SR_MATH_NS::FVector3> scale;

    };
}

#endif //SRENGINE_ANIMATIONDATA_H
