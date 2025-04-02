

# File RaycastHit.h

[**File List**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**RaycastHit.h**](RaycastHit_8h.md)

[Go to the documentation of this file](RaycastHit_8h.md)


```C++
//
// Created by innerviewer on 2/13/2023.
//

#ifndef SR_ENGINE_RAYCASTHIT_H
#define SR_ENGINE_RAYCASTHIT_H


namespace SR_UTILS_NS {
    struct RaycastHit {
        void* pHandler = nullptr;
        SR_MATH_NS::FVector3 position;
        SR_MATH_NS::FVector3 normal;
        float_t distance;
    };
}

#endif //SR_ENGINE_RAYCASTHIT_H
```


