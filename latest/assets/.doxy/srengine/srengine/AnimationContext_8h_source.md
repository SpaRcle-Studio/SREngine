

# File AnimationContext.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**AnimationContext.h**](AnimationContext_8h.md)

[Go to the documentation of this file](AnimationContext_8h.md)


```C++
//
// Created by Monika on 03.07.2024.
//

#ifndef SR_ENGINE_ANIMATION_CONTEXT_H
#define SR_ENGINE_ANIMATION_CONTEXT_H

#include <Graphics/Animations/AnimationData.h>
#include <Utils/Types/SortedVector.h>

namespace SpaRcle::Graphics::Animations {
    class AnimationGraph;
}

namespace SR_ANIMATIONS_NS {
    class AnimationPose;

    //using AnimationDataPair = std::pair<SR_UTILS_NS::StringAtom, AnimationData>;

    //class AnimationDataPredicate {
    //    SR_NODISCARD constexpr bool operator()(const AnimationDataPair& left, const AnimationDataPair& right) const noexcept {
    //        return left.first < right.first;
    //    }
    //};

    //class AnimationDataNamePredicate {
    //    SR_NODISCARD constexpr bool operator()(const AnimationDataPair& left, const SR_UTILS_NS::StringAtom& right) const noexcept {
    //        return left.first < right;
    //    }
    //};

    struct UpdateContext {
        float_t dt = 0.f;
        float_t weight = 1.f;
        SR_UTILS_NS::TimePointType now;
        bool fpsCompensation = false;
        uint16_t frameRate = 1;
        AnimationPose* pPose = nullptr;
        AnimationGraph* pGraph = nullptr;
        float_t tolerance = 0.001f;

    };

    struct ChannelUpdateContext {
        std::optional<uint16_t> gameObjectIndex;
        AnimationPose* pPose = nullptr;
        AnimationGraph* pGraph = nullptr;
    };

    struct CompileContext {
        explicit CompileContext(std::vector<SR_UTILS_NS::GameObject::Ptr>& gameObjects)
            : gameObjects(gameObjects)
        { }

        Skeleton* pSkeleton = nullptr;

        std::vector<SR_UTILS_NS::GameObject::Ptr>& gameObjects;
    };
}

#endif //SR_ENGINE_ANIMATION_CONTEXT_H
```


