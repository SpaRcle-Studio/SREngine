//
// Created by Monika on 07.01.2023.
//

#ifndef SRENGINE_ANIMATIONKEY_H
#define SRENGINE_ANIMATIONKEY_H

#include <Utils/ECS/EntityRef.h>
#include <Graphics/Animations/Interpolation.h>

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_ANIMATIONS_NS {
    /// Это тип свойства которое изменяет AnimationKey
    SR_ENUM_NS_CLASS_T(AnimationPropertyType, uint8_t,
        Translation,
        Rotation,
        Scale,
        Skew,

        InstanceFromFile,

        ComponentEnable,
        ComponentProperty,
        ComponentRemove,
        ComponentAdd,

        GameObjectAdd,
        GameObjectRemove,
        GameObjectMove,
        GameObjectEnable,
        GameObjectName,
        GameObjectTag
    );

    /// Задача ключа обеспечить необходимый переход из предыдущего ключа в этот в зависимости от интервала времени.
    /// Интервал времени задается от 0.f до 1.f в зависимости от положения перехода в момент времени.
    /// Переход должен работать и в обратную сторону (от 1.f до 0.f)
    class AnimationKey {
    public:
        virtual ~AnimationKey() = default;

    public:
        virtual void Update(float_t interval, SR_UTILS_NS::GameObject* pRoot) = 0;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class TranslationKey : public AnimationKey {
    public:
        explicit TranslationKey(const SR_MATH_NS::FVector3& translation)
            : m_translation(translation)
        { }

    public:
        void Update(float_t interval, SR_UTILS_NS::GameObject* pRoot) override;

    private:
        SR_MATH_NS::FVector3 m_translation;
        SR_UTILS_NS::EntityRef m_entity;

    };
}

#endif //SRENGINE_ANIMATIONKEY_H
