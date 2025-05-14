

# File Launcher.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Launcher.h**](Launcher_8h.md)

[Go to the documentation of this file](Launcher_8h.md)


```C++
//
// Created by innerviewer on 2024-03-20.
//

#ifndef SR_ENGINE_CORE_LAUNCHER_H
#define SR_ENGINE_CORE_LAUNCHER_H

#include <Utils/Types/SharedPtr.h>
#include <Engine/Application.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_CLASS_T(LauncherInitStatus, uint8_t,
        Success,
        Error
    )

    class Launcher : public SR_CORE_NS::Application {
        using Super = SR_CORE_NS::Application;
    public:
        LauncherInitStatus InitLauncher();

    private:
        static bool UnpackEmbedded();
        bool CloneResources();

    };
}

#endif //SR_ENGINE_CORE_LAUNCHER_H
```


