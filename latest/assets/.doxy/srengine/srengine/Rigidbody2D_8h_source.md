

# File Rigidbody2D.h

[**File List**](files.md) **>** [**2D**](dir_58410a853955bb3b198b618cee9ab374.md) **>** [**Rigidbody2D.h**](Rigidbody2D_8h.md)

[Go to the documentation of this file](Rigidbody2D_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_RIGIDBODY2D_H
#define SR_ENGINE_RIGIDBODY2D_H

#include <Physics/Rigidbody.h>

namespace SR_PTYPES_NS {
    class Rigidbody2DImpl : public RigidbodyImpl {

    };

    class Rigidbody2D : public Rigidbody {
        SR_CLASS()
        using Super = Rigidbody;
    public:
        SR_NODISCARD SR_UTILS_NS::Measurement GetMeasurement() const override;

    };
}

#endif //SR_ENGINE_RIGIDBODY2D_H
```


