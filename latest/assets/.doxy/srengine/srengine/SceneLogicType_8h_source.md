

# File SceneLogicType.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**SceneLogicType.h**](SceneLogicType_8h.md)

[Go to the documentation of this file](SceneLogicType_8h.md)


```C++
//
// Created by Monika on 02.03.2025.
//

#ifndef SR_ENGINE_SCENE_LOGIC_TYPE_H
#define SR_ENGINE_SCENE_LOGIC_TYPE_H

#include <Utils/Common/Enumerations.h>

namespace SR_WORLD_NS {
    SR_ENUM_NS_CLASS_T(SceneLogicType, int16_t,
        Asset = 0,
        CubeChunk = 1,
        Prefab = 2
    )
}

#endif //SR_ENGINE_SCENE_LOGIC_TYPE_H
```


