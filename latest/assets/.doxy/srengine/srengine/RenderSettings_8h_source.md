

# File RenderSettings.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**RenderSettings.h**](RenderSettings_8h.md)

[Go to the documentation of this file](RenderSettings_8h.md)


```C++
//
// Created by Monika on 11.08.2023.
//

#ifndef SR_ENGINE_RENDERSETTINGS_H
#define SR_ENGINE_RENDERSETTINGS_H

#include <Graphics/macros.h>

#include <Graphics/Render/RenderSettings.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(Quality, uint8_t,
        None,
        Low,
        Medium,
        High,
        Ultra,
        Extreme
    );

    class RenderSettings : public SR_UTILS_NS::NonCopyable {
        Quality shadows = Quality::None;
        Quality ScreenSpaceAO = Quality::None;
        Quality particles = Quality::None;

    };
}

#endif //SR_ENGINE_RENDERSETTINGS_H
```


