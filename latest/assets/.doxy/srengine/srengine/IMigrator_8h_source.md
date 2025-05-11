

# File IMigrator.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Serialization**](dir_1c3f3ba47f77e74f680b6bcf664148dc.md) **>** [**IMigrator.h**](IMigrator_8h.md)

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


