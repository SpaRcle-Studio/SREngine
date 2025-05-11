

# File ScriptableContext.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Scripting**](dir_ed9a5d5d83e243074230cc8c3c9f6b17.md) **>** [**ScriptableContext.h**](ScriptableContext_8h.md)

[Go to the documentation of this file](ScriptableContext_8h.md)


```C++
//
// Created by Monika on 31.03.2025.
//

#ifndef SR_ENGINE_CORE_SCRIPTABLE_CONTEXT_H
#define SR_ENGINE_CORE_SCRIPTABLE_CONTEXT_H

#include <Engine/Engine.h>

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


