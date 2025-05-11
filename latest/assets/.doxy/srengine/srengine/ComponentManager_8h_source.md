

# File ComponentManager.h

[**File List**](files.md) **>** [**ECS**](dir_df4674c010a45d2af7a2a452a0d36896.md) **>** [**ComponentManager.h**](ComponentManager_8h.md)

[Go to the documentation of this file](ComponentManager_8h.md)


```C++
//
// Created by Monika on 27.05.2022.
//

#ifndef SR_ENGINE_COMPONENT_MANAGER_H
#define SR_ENGINE_COMPONENT_MANAGER_H

#include <Utils/ECS/EntityController.h>
#include <Utils/ECS/Component.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Serialization/SRASerialization.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API ComponentManager : public Singleton<ComponentManager> {
        SR_REGISTER_SINGLETON(ComponentManager)
    public:
        SR_NODISCARD bool IsSingletonCanBeDestroyed() const override {
            return false;
        }
    };
}

#endif //SR_ENGINE_COMPONENTMANAGER_H
```


