

# File Map.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Types**](dir_5acfcf7a6efc565cfce10e624e0935ad.md) **>** [**Map.h**](Map_8h.md)

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
    #include <sparsehash/dense_hash_map.h>
    #include <flat_hash_map/flat_hash_map.hpp>
#endif

#ifdef SR_ANDROID
    #pragma clang diagnostic pop
#endif

namespace SR_HTYPES_NS {

}

#endif //SR_ENGINE_MAP_H
```


