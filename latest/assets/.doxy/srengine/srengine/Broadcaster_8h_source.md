

# File Broadcaster.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Events**](dir_44d7275059ecd594487e039c74bc8965.md) **>** [**Broadcaster.h**](Broadcaster_8h.md)

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


