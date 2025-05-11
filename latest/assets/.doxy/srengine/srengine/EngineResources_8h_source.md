

# File EngineResources.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**EngineResources.h**](EngineResources_8h.md)

[Go to the documentation of this file](EngineResources_8h.md)


```C++
//
// Created by Monika on 09.03.2023.
//

#ifndef SR_ENGINE_ENGINERESOURCES_H
#define SR_ENGINE_ENGINERESOURCES_H

#include <Utils/Types/SharedPtr.h>

namespace SR_CORE_NS {
    class Engine;
}

namespace SR_CORE_NS::Resources {
    bool RegisterResources(const SR_HTYPES_NS::SharedPtr<Engine>& pEngin);
}

#endif //SR_ENGINE_ENGINERESOURCES_H
```


