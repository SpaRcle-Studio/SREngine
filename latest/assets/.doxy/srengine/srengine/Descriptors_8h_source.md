

# File Descriptors.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Descriptors.h**](Descriptors_8h.md)

[Go to the documentation of this file](Descriptors_8h.md)


```C++
//
// Created by Monika on 06.06.2021.
//

#ifndef SR_ENGINE_DESCRIPTORS_H
#define SR_ENGINE_DESCRIPTORS_H

#include <Graphics/macros.h>

#include <Utils/macros.h>

namespace SR_GRAPH_NS {
    enum class DescriptorType {
        Unknown, Uniform, CombinedImage, Storage
    };
}

#endif //SR_ENGINE_DESCRIPTORS_H
```


