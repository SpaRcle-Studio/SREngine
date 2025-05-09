

# File Device.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pipeline**](dir_5b8a811d805f0a9bb3b25de386a42645.md) **>** [**Device.h**](Device_8h.md)

[Go to the documentation of this file](Device_8h.md)


```C++
//
// Created by Monika on 08.02.2023.
//

#ifndef SR_ENGINE_GRAPHICS_DEVICE_H
#define SR_ENGINE_GRAPHICS_DEVICE_H

#include <Graphics/macros.h>

#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(DeviceType, uint8_t,
        Nvidia, AMD, Intel
    );
}

#endif //SR_ENGINE_GRAPHICS_DEVICE_H
```


