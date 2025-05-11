

# File Broadcaster.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Events**](dir_e74a527d3186554a7cccdddc0bf2b7af.md) **>** [**Broadcaster.h**](Broadcaster_8h.md)

[Go to the documentation of this file](Broadcaster_8h.md)


```C++
//
// Created by Monika on 04.05.2025.
//

#ifndef SR_ENGINE_UTILS_EVENTS_BROADCASTER_H
#define SR_ENGINE_UTILS_EVENTS_BROADCASTER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/SubscriptionHolder.h>

namespace SR_UTILS_NS {
    class Broadcaster : public Singleton<Broadcaster>, public SR_UTILS_NS::SubscriptionHolder {
        SR_REGISTER_SINGLETON(Broadcaster);
    public:

    };

    namespace Events {
        static inline const SR_UTILS_NS::StringAtom EVENT_ON_SCRIPT_MODULE_RELOADED_ID = "OnScriptModuleReloaded";
    }
}

#endif //SR_ENGINE_UTILS_EVENTS_BROADCASTER_H
```


