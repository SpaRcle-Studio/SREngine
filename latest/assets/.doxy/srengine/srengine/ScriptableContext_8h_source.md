

# File ScriptableContext.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**Scripting**](dir_7ce46455ccb3010cb58ed75f07d53122.md) **>** [**ScriptableContext.h**](ScriptableContext_8h.md)

[Go to the documentation of this file](ScriptableContext_8h.md)


```C++
//
// Created by Monika on 31.03.2025.
//

#ifndef SR_ENGINE_CORE_SCRIPTABLE_CONTEXT_H
#define SR_ENGINE_CORE_SCRIPTABLE_CONTEXT_H

#include <Core/Engine.h>

namespace SR_CORE_NS {
    struct ScriptableContext {
        SR_CORE_NS::Engine& GetEngine() {
            return *pEngine;
        }
        SR_CORE_NS::Engine* pEngine = nullptr;
    };
}

#endif //SR_ENGINE_CORE_SCRIPTABLE_CONTEXT_H
```


