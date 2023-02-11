//
// Created by Monika on 07.01.2023.
//

#ifndef SRENGINE_ANIMATIONKEY_H
#define SRENGINE_ANIMATIONKEY_H

#include <Graphics/Animations/Interpolation.h>

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_ANIMATIONS_NS {
    class AnimationChannel;

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
        explicit AnimationKey(AnimationChannel* pChannel)
            : m_channel(pChannel)
        { }

        virtual ~AnimationKey() = default;

    public:
        virtual void Update(double_t interval, AnimationKey* pPreviousKey, SR_UTILS_NS::GameObject* pRoot) = 0;
        virtual AnimationKey* Copy(AnimationChannel* pChannel) const noexcept = 0;

    protected:
        AnimationChannel* m_channel = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class TranslationKey : public AnimationKey {
        using Super = AnimationKey;
    public:
        TranslationKey(AnimationChannel* pChannel, const SR_MATH_NS::FVector3& translation)
            : Super(pChannel)
            , m_translation(translation)
        { }

    public:
        void Update(double_t progress, AnimationKey* pPreviousKey, SR_UTILS_NS::GameObject* pRoot) override;

        SR_NODISCARD AnimationKey* Copy(AnimationChannel* pChannel) const noexcept override {
            return new TranslationKey(pChannel, m_translation);
        }

    private:
        SR_MATH_NS::FVector3 m_translation;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class RotationKey : public AnimationKey {
        using Super = AnimationKey;
    public:
        RotationKey(AnimationChannel* pChannel, const SR_MATH_NS::Quaternion& rotation)
            : Super(pChannel)
            , m_rotation(rotation)
        { }

    public:
        void Update(double_t progress, AnimationKey* pPreviousKey, SR_UTILS_NS::GameObject* pRoot) override;

        SR_NODISCARD AnimationKey* Copy(AnimationChannel* pChannel) const noexcept override {
            return new RotationKey(pChannel, m_rotation);
        }

    private:
        SR_MATH_NS::Quaternion m_rotation;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class ScalingKey : public AnimationKey {
        using Super = AnimationKey;
    public:
        ScalingKey(AnimationChannel* pChannel, const SR_MATH_NS::FVector3& scaling)
            : Super(pChannel)
            , m_scaling(scaling)
        { }

    public:
        void Update(double_t progress, AnimationKey* pPreviousKey, SR_UTILS_NS::GameObject* pRoot) override;

        SR_NODISCARD AnimationKey* Copy(AnimationChannel* pChannel) const noexcept override {
            return new ScalingKey(pChannel, m_scaling);
        }

    private:
        SR_MATH_NS::FVector3 m_scaling;

    };
}

#endif //SRENGINE_ANIMATIONKEY_H
