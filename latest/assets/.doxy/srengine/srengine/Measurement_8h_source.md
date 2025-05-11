

# File Measurement.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**Measurement.h**](Measurement_8h.md)

[Go to the documentation of this file](Measurement_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_MEASUREMENT_H
#define SR_ENGINE_MEASUREMENT_H

#include <Utils/Common/Enumerations.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(Measurement, int32_t,
        Unknown = -2,
        Holder = -1,
        SpaceZero = 0,
        Space1D = 1,
        Space2D = 2,
        Space3D = 3,
        Space4D = 4
    );
}

#endif //SR_ENGINE_MEASUREMENT_H
```


