

# File ComponentManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**ECS**](dir_d56b953042ff1935f3f30a5ce5fa4a33.md) **>** [**ComponentManager.h**](ComponentManager_8h.md)

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


