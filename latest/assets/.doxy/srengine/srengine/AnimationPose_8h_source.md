

# File AnimationPose.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**AnimationPose.h**](AnimationPose_8h.md)

[Go to the documentation of this file](AnimationPose_8h.md)


```C++
//
// Created by Monika on 25.04.2023.
//

#ifndef SR_ENGINE_ANIMATIONPOSE_H
#define SR_ENGINE_ANIMATIONPOSE_H

#include <Utils/ECS/GameObject.h>

#include <Graphics/Animations/AnimationCommon.h>

namespace SR_ANIMATIONS_NS {
    class Skeleton;
    class AnimationGameObjectData;
    class AnimationClip;

    class AnimationPose : public SR_UTILS_NS::NonCopyable {
        using Index = uint32_t;
    public:
        ~AnimationPose() override;

    public:
        void SetGameObjectsCount(uint32_t count);

        SR_NODISCARD AnimationGameObjectData& GetGameObjectData(Index index) noexcept;

        SR_NODISCARD std::vector<AnimationGameObjectData>& GetGameObjects() noexcept { return m_gameObjects; }

    private:
        std::vector<AnimationGameObjectData> m_gameObjects;

    public:
        /*SR_NODISCARD AnimationData* GetData(SR_UTILS_NS::StringAtom boneName) const noexcept;
        SR_NODISCARD AnimationData* GetDataByIndex(uint16_t index) const noexcept;

        void Reset();
        void Initialize(const Skeleton* pSkeleton);
        void Apply(Skeleton* pSkeleton);
        void Update(Skeleton* pSkeleton, AnimationPose* pWorkingPose);
        void SetPose(AnimationClip* pClip);

    private:
        static void Apply(const AnimationData* pWorkingData, const SR_UTILS_NS::GameObject::Ptr& pGameObject);
        static void Update(AnimationData* pStaticData, const AnimationData* pWorkingData, const SR_UTILS_NS::GameObject::Ptr& pGameObject);

    private:
        bool m_isInitialized = false;

        ska::flat_hash_map<SR_UTILS_NS::StringAtom, AnimationData*> m_indices;
        std::vector<std::pair<SR_UTILS_NS::StringAtom, AnimationData*>> m_data;*/

    };
}

#endif //SR_ENGINE_ANIMATIONPOSE_H
```


