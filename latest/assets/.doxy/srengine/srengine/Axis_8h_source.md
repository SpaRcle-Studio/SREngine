

# File Axis.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Math**](dir_3900fe4b4d95d895210b9082ab5cdd34.md) **>** [**Axis.h**](Axis_8h.md)

[Go to the documentation of this file](Axis_8h.md)


```C++
//
// Created by Monika on 03.02.2024.
//

#ifndef SR_ENGINE_UTILS_AXIS_H
#define SR_ENGINE_UTILS_AXIS_H

#include <Utils/Common/Enumerations.h>

namespace SR_MATH_NS {
    SR_ENUM_NS_STRUCT_T(Axis, uint64_t,
        None = 0,
        X    = 1 << 0,
        Y    = 1 << 1,
        Z    = 1 << 2,

        XY   = X | Y,
        XZ   = X | Z,
        YZ   = Y | Z,
        XYZ  = X | Y | Z
    );
}

#endif //SR_ENGINE_UTILS_AXIS_H
```


