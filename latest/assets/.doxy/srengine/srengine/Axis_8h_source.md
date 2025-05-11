

# File Axis.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**Axis.h**](Axis_8h.md)

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


