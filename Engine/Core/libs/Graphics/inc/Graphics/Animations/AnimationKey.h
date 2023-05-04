//
// Created by Monika on 07.01.2023.
//

#ifndef SRENGINE_ANIMATIONKEY_H
#define SRENGINE_ANIMATIONKEY_H

#include <Graphics/Animations/Interpolation.h>
#include <Graphics/Animations/AnimationPose.h>

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_ANIMATIONS_NS {
    class AnimationChannel;

    /// Задача ключа обеспечить необходимый переход из предыдущего ключа в этот в зависимости от интервала времени.
    /// Интервал времени задается от 0.f до 1.f в зависимости от положения перехода в момент времени.
    /// Переход должен работать и в обратную сторону (от 1.f до 0.f)
    class AnimationKey : public SR_UTILS_NS::NonCopyable {
    public:
        explicit AnimationKey(AnimationChannel* pChannel)
            : m_channel(pChannel)
        { }

    public:
        virtual void Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) = 0;
        virtual void Set(float_t weight, AnimationData* pData) = 0;
        virtual AnimationKey* Copy(AnimationChannel* pChannel) const noexcept = 0;

    protected:
        AnimationChannel* m_channel = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class TranslationKey : public AnimationKey {
        using Super = AnimationKey;
    public:
        TranslationKey(AnimationChannel* pChannel, const SR_MATH_NS::FVector3& translation, const SR_MATH_NS::FVector3& delta)
            : Super(pChannel)
            , m_translation(translation)
            , m_delta(delta)
        { }

    public:
        void Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) override;
        void Set(float_t weight, AnimationData* pData) override;

        SR_NODISCARD AnimationKey* Copy(AnimationChannel* pChannel) const noexcept override {
            return new TranslationKey(pChannel, m_translation, m_delta);
        }

    private:
        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::FVector3 m_delta;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class RotationKey : public AnimationKey {
        using Super = AnimationKey;
    public:
        RotationKey(AnimationChannel* pChannel, const SR_MATH_NS::Quaternion& rotation, const SR_MATH_NS::Quaternion& delta)
            : Super(pChannel)
            , m_rotation(rotation)
            , m_delta(delta)
        { }

    public:
        void Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) override;
        void Set(float_t weight, AnimationData* pData) override;

        SR_NODISCARD AnimationKey* Copy(AnimationChannel* pChannel) const noexcept override {
            return new RotationKey(pChannel, m_rotation, m_delta);
        }

    private:
        SR_MATH_NS::Quaternion m_rotation;
        SR_MATH_NS::Quaternion m_delta;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class ScalingKey : public AnimationKey {
        using Super = AnimationKey;
    public:
        ScalingKey(AnimationChannel* pChannel, const SR_MATH_NS::FVector3& scaling, const SR_MATH_NS::FVector3& delta)
            : Super(pChannel)
            , m_scaling(scaling)
            , m_delta(delta)
        { }

    public:
        void Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) override;
        void Set(float_t weight, AnimationData* pData) override;

        SR_NODISCARD AnimationKey* Copy(AnimationChannel* pChannel) const noexcept override {
            return new ScalingKey(pChannel, m_scaling, m_delta);
        }

    private:
        SR_MATH_NS::FVector3 m_scaling;
        SR_MATH_NS::FVector3 m_delta;

    };
}

#endif //SRENGINE_ANIMATIONKEY_H
