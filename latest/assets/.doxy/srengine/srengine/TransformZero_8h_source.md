

# File TransformZero.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**TransformZero.h**](TransformZero_8h.md)

[Go to the documentation of this file](TransformZero_8h.md)


```C++
//
// Created by Monika on 23.08.2022.
//

#ifndef SR_ENGINE_TRANSFORM_ZERO_H
#define SR_ENGINE_TRANSFORM_ZERO_H

#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    class GameObject;

    class SR_COMMON_DLL_API TransformZero : public Transform {
        SR_CLASS()
        friend class GameObject;
    public:
        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::SpaceZero; }

    };

    class SR_COMMON_DLL_API TransformHolder : public Transform {
        SR_CLASS()
        friend class GameObject;
    public:
        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::SpaceZero; }

    };
}


#endif //SR_ENGINE_TRANSFORM_ZERO_H
```


