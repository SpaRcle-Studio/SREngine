

# File TransformZero.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**TransformZero.h**](TransformZero_8h.md)

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


