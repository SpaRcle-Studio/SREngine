

# File Launcher.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**Launcher.h**](Launcher_8h.md)

[Go to the documentation of this file](Launcher_8h.md)


```C++
//
// Created by innerviewer on 2024-03-20.
//

#ifndef SR_ENGINE_CORE_LAUNCHER_H
#define SR_ENGINE_CORE_LAUNCHER_H

#include <Utils/Types/SharedPtr.h>
#include <Core/Application.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_CLASS_T(LauncherInitStatus, uint8_t,
        Success,
        Error,
        Unpacking
    )

    class Launcher : public SR_CORE_NS::Application {
        using Super = SR_CORE_NS::Application;
    public:
        LauncherInitStatus InitLauncher();

    protected:
        bool InitializeResourcesFolder() override { return true; }

    private:
        static bool UnpackAndExecute();
        static void DeleteOldApplication();
        bool CloneResources();

    };
}

#endif //SR_ENGINE_CORE_LAUNCHER_H
```


