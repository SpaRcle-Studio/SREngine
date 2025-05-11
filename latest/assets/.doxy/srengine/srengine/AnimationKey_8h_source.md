

# File AnimationKey.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**AnimationKey.h**](AnimationKey_8h.md)

[Go to the documentation of this file](AnimationKey_8h.md)


```C++
//
// Created by Monika on 07.01.2023.
//

#ifndef SR_ENGINE_ANIMATIONKEY_H
#define SR_ENGINE_ANIMATIONKEY_H

#include <Graphics/Animations/Interpolation.h>
#include <Graphics/Animations/AnimationPose.h>
#include <Graphics/Animations/AnimationContext.h>

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_ANIMATIONS_NS {
    class AnimationChannel;

    SR_ENUM_NS_CLASS_T(AnimationKeyType, uint8_t,
        None,
        Translation,
        Rotation,
        Scaling
    );



    struct TranslationKey {
    public:
        TranslationKey() = default;
        explicit TranslationKey(const SR_MATH_NS::FVector3& translation)
            : translation(translation)
        { }

    public:
        SR_MATH_NS::FVector3 translation;

    };


    struct RotationKey {
    public:
        RotationKey() = default;
        explicit RotationKey(const SR_MATH_NS::Quaternion& rotation)
            : rotation(rotation)
        { }

    public:
        SR_MATH_NS::Quaternion rotation;

    };


    struct ScalingKey {
    public:
        ScalingKey() = default;
        explicit ScalingKey(const SR_MATH_NS::FVector3& scaling)
            : scaling(scaling)
        { }

    public:
        SR_MATH_NS::FVector3 scaling;

    };


    struct UnionAnimationKey {
        UnionAnimationKey() = default;
        ~UnionAnimationKey() = default;

        UnionAnimationKey(const UnionAnimationKey& other) {
            CopyFrom(other);
        }

        UnionAnimationKey& operator=(const UnionAnimationKey& other) {
            if (this != &other) {
                CopyFrom(other);
            }
            return *this;
        }

        void SR_FASTCALL UpdateWithWeight(float_t progress, const UnionAnimationKey& prevKey, AnimationGameObjectData& animation, float_t weight) const noexcept;
        void SR_FASTCALL SetWithWeight(AnimationGameObjectData& animation, float_t weight) const noexcept;

        void SR_FASTCALL Update(float_t progress, const UnionAnimationKey& prevKey, AnimationGameObjectData& animation) const noexcept;
        void SR_FASTCALL Set(AnimationGameObjectData& animation) const noexcept;

        void SR_FASTCALL Update(float_t progress, const UnionAnimationKey& prevKey, AnimationGameObjectData& animation, float_t toreance) const noexcept;
        void SR_FASTCALL Set(AnimationGameObjectData& animation, float_t toreance) const noexcept;

        template<class T> void SetData(T data) {
            if constexpr (std::is_same_v<T, TranslationKey>) {
                this->data.translation = data;
                type = AnimationKeyType::Translation;
            }
            else if constexpr (std::is_same_v<T, RotationKey>) {
                this->data.rotation = data;
                type = AnimationKeyType::Rotation;
            }
            else if constexpr (std::is_same_v<T, ScalingKey>) {
                this->data.scaling = data;
                type = AnimationKeyType::Scaling;
            }
            else {
                SRHalt("Unknown key type!");
            }
        }

        void CopyFrom(const UnionAnimationKey& other);

    public:
        union Data {
            TranslationKey translation;
            RotationKey rotation;
            ScalingKey scaling;

            Data() { }
            ~Data() { }
        } data;

        AnimationKeyType type = AnimationKeyType::None;
        float_t time = 0.f;

    };
}

#endif //SR_ENGINE_ANIMATIONKEY_H
```


