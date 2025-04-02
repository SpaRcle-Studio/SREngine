

# File IMigrator.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Serialization**](dir_ffec67008ecd4ba04c0216def73faaef.md) **>** [**IMigrator.h**](IMigrator_8h.md)

[Go to the documentation of this file](IMigrator_8h.md)


```C++
//
// Created by Monika on 08.03.2025.
//

#ifndef SR_ENGINE_I_MIGRATOR_H
#define SR_ENGINE_I_MIGRATOR_H

#include <Utils/TypeTraits/SRClass.h>
#include <Utils/Common/Enumerations.h>

namespace SR_UTILS_NS {
    class IDeserializer;

    class IMigrator : public SRClass, public SR_HTYPES_NS::SharedPtr<IMigrator> {
        using Super = SR_HTYPES_NS::SharedPtr<IMigrator>;
        SR_CLASS()
    public:
        IMigrator()
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

    public:
        SR_NODISCARD virtual MigrationResult Migrate(SR_UTILS_NS::SerializationNode& node) = 0;

    };

}

#endif //SR_ENGINE_I_MIGRATOR_H
```


