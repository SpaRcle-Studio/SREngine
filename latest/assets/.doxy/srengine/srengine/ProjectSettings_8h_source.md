

# File ProjectSettings.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Settings**](dir_e2003efd86638652fa75d292679631aa.md) **>** [**ProjectSettings.h**](ProjectSettings_8h.md)

[Go to the documentation of this file](ProjectSettings_8h.md)


```C++
//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_PROJECT_SETTINGS_H
#define SR_ENGINE_PROJECT_SETTINGS_H

#include <Engine/macros.h>

#include <Utils/Resources/Asset.h>

namespace SR_CORE_NS {
    class ProjectSettings : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        SR_INLINE static const char* EXTENSION_NAME = "srproject";

    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ProjectSettings>;

    public:
        SR_UTILS_NS::StringAtom projectName = "New Project";

    };
}

#endif //SR_ENGINE_PROJECT_SETTINGS_H
```


