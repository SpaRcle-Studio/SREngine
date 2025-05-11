

# File Utils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**Utils.h**](Graphics_2inc_2Graphics_2GUI_2Utils_8h.md)

[Go to the documentation of this file](Graphics_2inc_2Graphics_2GUI_2Utils_8h.md)


```C++
//
// Created by Monika on 16.02.2022.
//

#ifndef SR_ENGINE_GUI_UTILS_H
#define SR_ENGINE_GUI_UTILS_H

#include <Graphics/macros.h>

#include <Utils/Debug.h>
#include <Utils/Math/Mathematics.h>
#include <Utils/Math/Rect.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/SRLM/DataType.h>
#include <Utils/TypeTraits/Properties.h>

namespace SR_GRAPH_GUI_NS {
    class ImGuiDisabledLockGuard : public SR_UTILS_NS::NonCopyable {
    public:
        explicit ImGuiDisabledLockGuard(bool disabled);
        ~ImGuiDisabledLockGuard() override;

    private:
        bool m_disabled = false;

    };

    bool RadioButton(const char* label, bool active, float_t radius = 1.f);
}

#endif //SR_ENGINE_GUI_UTILS_H
```


