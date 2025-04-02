

# File MeshTypes.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Utils**](dir_08379350d528ecfd47c79c18ec259ee8.md) **>** [**MeshTypes.h**](MeshTypes_8h.md)

[Go to the documentation of this file](MeshTypes_8h.md)


```C++
//
// Created by Monika on 20.03.2023.
//

#ifndef SR_ENGINE_MESHTYPES_H
#define SR_ENGINE_MESHTYPES_H

#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(MeshType, uint8_t,
         Unknown,
         Static,
         Wireframe,
         Skinned,
         Sprite,
         Procedural,
         Line,
         Text
    )
}

#endif //SR_ENGINE_MESHTYPES_H
```


