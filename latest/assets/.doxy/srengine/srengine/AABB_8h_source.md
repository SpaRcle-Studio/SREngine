

# File AABB.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**AABB.h**](AABB_8h.md)

[Go to the documentation of this file](AABB_8h.md)


```C++
//
// Created by Monika on 28.06.2025.
//

#ifndef SR_ENGINE_COMMON_MATH_AABB_H
#define SR_ENGINE_COMMON_MATH_AABB_H

#include <Utils/Math/Vector3.h>

namespace SR_MATH_NS {
    struct SR_RENDERER_DLL_API AABB {
        FVector3 min = FVector3(0.f, 0.f, 0.f);
        FVector3 max = FVector3(0.f, 0.f, 0.f);

        AABB();
        AABB(const FVector3& min, const FVector3& max);

        SR_NODISCARD bool IsValid() const noexcept;
        SR_NODISCARD bool IsEmpty() const noexcept;
        SR_NODISCARD FVector3 GetCenter() const noexcept;

    };
}

#endif //SR_ENGINE_COMMON_MATH_AABB_H
```


