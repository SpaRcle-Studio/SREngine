

# File BoneComponent.h

[**File List**](files.md) **>** [**Animations**](dir_417ea13389e3cbd1256e515e0204a036.md) **>** [**BoneComponent.h**](BoneComponent_8h.md)

[Go to the documentation of this file](BoneComponent_8h.md)


```C++
//
// Created by Monika on 28.07.2023.
//

#ifndef SR_ENGINE_BONECOMPONENT_H
#define SR_ENGINE_BONECOMPONENT_H

#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/Component.h>

namespace SR_ANIMATIONS_NS {
    class Skeleton;

    class BoneComponent : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        BoneComponent();

    public:
        void Initialize(Skeleton* pSkeleton, uint16_t boneIndex);

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

    private:
        uint16_t m_boneIndex = 0;
        SR_UTILS_NS::EntityRef m_skeleton;

    };
}

#endif //SR_ENGINE_BONECOMPONENT_H
```


