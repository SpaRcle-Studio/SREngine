

# File RaycastHit.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**RaycastHit.h**](RaycastHit_8h.md)

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


