

# File Raycast.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**Raycast.h**](Raycast_8h.md)

[Go to the documentation of this file](Raycast_8h.md)


```C++
//
// Created by innerviewer on 2/15/2023.
//

#ifndef SR_ENGINE_RAYCAST_H
#define SR_ENGINE_RAYCAST_H

#include <Physics/macros.h>

#include <Utils/Common/RaycastHit.h>

namespace SR_PHYSICS_NS {
    class PhysicsWorld;

    class Raycast {
    public:
        using RaycastHits = std::vector<SR_UTILS_NS::RaycastHit>;

    public:
        virtual ~Raycast() = default;

        void SwitchPhysics(SR_PHYSICS_NS::PhysicsWorld* pWorld) { m_world = pWorld; }

    protected:
        SR_PHYSICS_NS::PhysicsWorld* m_world = nullptr;
    };
}

#endif //SR_ENGINE_RAYCAST_H
```


