

# File ProbeLight.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Lighting**](dir_b94c38cb0a82e06a7dce50d9e5876b41.md) **>** [**ProbeLight.h**](ProbeLight_8h.md)

[Go to the documentation of this file](ProbeLight_8h.md)


```C++
//
// Created by Nikita on 13.12.2020.
//

#ifndef SR_ENGINE_PROBELIGHT_H
#define SR_ENGINE_PROBELIGHT_H

#include <Graphics/Lighting/ILightComponent.h>

namespace SR_GRAPH_NS {
    class ProbeLight : public ILightComponent {
    protected:
        float_t m_radius = 1.f;
        float_t m_distance = 10.f;

    };
}

#endif //SR_ENGINE_PROBELIGHT_H
```


