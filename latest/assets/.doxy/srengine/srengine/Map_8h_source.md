

# File Map.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Map.h**](Map_8h.md)

[Go to the documentation of this file](Map_8h.md)


```C++
//
// Created by kiper220 on 23.05.2020.
//

#ifndef SR_ENGINE_MAP_H
#define SR_ENGINE_MAP_H

#include <Utils/stdInclude.h>

#ifdef SR_ANDROID
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wconstant-conversion"
    #pragma clang diagnostic ignored "-Wshift-count-overflow"
    #pragma clang diagnostic ignored "-Wc++11-narrowing"
#endif

#ifndef SR_ENGINE_CODEGEN_CLANG_PARSE_MODE
    #include <sparsehash/dense_hash_map>
    #include <flat_hash_map/flat_hash_map.hpp>
#endif

#ifdef SR_ANDROID
    #pragma clang diagnostic pop
#endif

namespace SR_HTYPES_NS {

}

#endif //SR_ENGINE_MAP_H
```


