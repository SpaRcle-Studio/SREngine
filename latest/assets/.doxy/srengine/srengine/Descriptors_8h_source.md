

# File Descriptors.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Descriptors.h**](Descriptors_8h.md)

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


