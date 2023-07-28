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

    class TranslationKey;
    class RotationKey;
    class ScalingKey;

    /// Задача ключа обеспечить необходимый переход из предыдущего ключа в этот в зависимости от интервала времени.
    /// Интервал времени задается от 0.f до 1.f в зависимости от положения перехода в момент времени.
    /// Переход должен работать и в обратную сторону (от 1.f до 0.f)
    class AnimationKey : public SR_UTILS_NS::NonCopyable {
    public:
        explicit AnimationKey(AnimationChannel* pChannel);

    public:
        virtual void SR_FASTCALL Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) noexcept = 0;
        virtual void SR_FASTCALL Set(float_t weight, AnimationData* pData) noexcept = 0;
        virtual AnimationKey* Copy(AnimationChannel* pChannel) const noexcept = 0;

        SR_NODISCARD SR_FORCE_INLINE TranslationKey* SR_FASTCALL GetTranslation() const noexcept { return m_translation; }
        SR_NODISCARD SR_FORCE_INLINE RotationKey* SR_FASTCALL GetRotation() const noexcept { return m_rotation; }
        SR_NODISCARD SR_FORCE_INLINE ScalingKey* SR_FASTCALL GetScaling() const noexcept { return m_scaling; }

    protected:
        AnimationChannel* m_channel = nullptr;

        TranslationKey* m_translation = nullptr;
        RotationKey* m_rotation = nullptr;
        ScalingKey* m_scaling = nullptr;

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
        void SR_FASTCALL Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) noexcept override;
        void SR_FASTCALL Set(float_t weight, AnimationData* pData) noexcept override;

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
        void SR_FASTCALL Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) noexcept override;
        void SR_FASTCALL Set(float_t weight, AnimationData* pData) noexcept override;

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
        void SR_FASTCALL Update(double_t progress, float_t weight, AnimationKey* pPreviousKey, AnimationData* pData, AnimationData* pStaticData) noexcept override;
        void SR_FASTCALL Set(float_t weight, AnimationData* pData) noexcept override;

        SR_NODISCARD AnimationKey* Copy(AnimationChannel* pChannel) const noexcept override {
            return new ScalingKey(pChannel, m_scaling, m_delta);
        }

    private:
        SR_MATH_NS::FVector3 m_scaling;
        SR_MATH_NS::FVector3 m_delta;

    };
}

#endif //SRENGINE_ANIMATIONKEY_H
