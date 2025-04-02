

# File PointLight.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Lighting**](dir_84c906e4a9232501b7e5ce92a32284b3.md) **>** [**PointLight.h**](PointLight_8h.md)

[Go to the documentation of this file](PointLight_8h.md)


```C++
//
// Created by Nikita on 13.12.2020.
//

#ifndef SR_ENGINE_POINTLIGHT_H
#define SR_ENGINE_POINTLIGHT_H

#include <Graphics/Lighting/ILightComponent.h>

namespace SR_GRAPH_NS {
    class PointLight : public ILightComponent {
    public:

    protected:
        float_t m_radius = 1.f;

    };
}

#endif //SR_ENGINE_POINTLIGHT_H
```


