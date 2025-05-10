

# File Utils.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**Utils.h**](Graphics_2inc_2Graphics_2GUI_2Utils_8h.md)

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


