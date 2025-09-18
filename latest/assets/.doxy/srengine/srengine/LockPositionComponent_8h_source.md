

# File LockPositionComponent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Game**](dir_8f1885d18d834cf9a317dd74a37ec10b.md) **>** [**LockPositionComponent.h**](LockPositionComponent_8h.md)

[Go to the documentation of this file](LockPositionComponent_8h.md)


```C++
//
// Created by Monika on 17.09.2025.
//

#ifndef SR_ENGINE_UTILS_LOCK_POSITION_COMPONENT_H
#define SR_ENGINE_UTILS_LOCK_POSITION_COMPONENT_H

#include <Utils/ECS/Component.h>
#include <Utils/ECS/Transform3D.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API LockPositionComponent final : public Component {
        SR_CLASS()
        using Super = Component;
    public:
        void Awake() override;
        void Update(float_t) override;

    private:
        SR_MATH_NS::FVector3 m_position;

    };
}

#endif //SR_ENGINE_UTILS_LOCK_POSITION_COMPONENT_H
```


