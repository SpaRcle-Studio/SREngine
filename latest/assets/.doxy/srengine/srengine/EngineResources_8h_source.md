

# File EngineResources.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**EngineResources.h**](EngineResources_8h.md)

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


