

# File MaterialType.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Material**](dir_2ed0f653e9a17ea2b9386330cebea31f.md) **>** [**MaterialType.h**](MaterialType_8h.md)

[Go to the documentation of this file](MaterialType_8h.md)


```C++
//
// Created by Monika on 26.05.2024.
//

#ifndef SR_ENGINE_GRAPHICS_MATERIAL_TYPE_H
#define SR_ENGINE_GRAPHICS_MATERIAL_TYPE_H

#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(MaterialType, uint8_t,
        None, File, Unique
    );
}

#endif //SR_ENGINE_GRAPHICS_MATERIAL_TYPE_H
```


