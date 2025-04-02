

# File Importers.h

[**File List**](files.md) **>** [**Common**](dir_5facaa05c86060793c747e3dfab17af4.md) **>** [**Importers.h**](Importers_8h.md)

[Go to the documentation of this file](Importers_8h.md)


```C++
//
// Created by Monika on 11.01.2023.
//

#ifndef SR_ENGINE_IMPORTERS_H
#define SR_ENGINE_IMPORTERS_H

#include <Utils/Types/SharedPtr.h>

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_ANIMATIONS_NS {
    class Skeleton;
}

namespace SR_CORE_NS::Importers {
    bool ImportSkeletonFromRawMesh(const SR_HTYPES_NS::RawMesh* pRawMesh, SR_HTYPES_NS::SharedPtr<SR_ANIMATIONS_NS::Skeleton> pSkeleton);
    SR_HTYPES_NS::SharedPtr<SR_ANIMATIONS_NS::Skeleton> ImportSkeletonFromRawMesh(const SR_HTYPES_NS::RawMesh* pRawMesh);
}

#endif //SR_ENGINE_IMPORTERS_H
```


