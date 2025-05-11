

# File SoundDebug.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**SoundDebug.h**](SoundDebug_8h.md)

[Go to the documentation of this file](SoundDebug_8h.md)


```C++
//
// Created by Monika on 16.07.2024.
//

#ifndef SR_ENGINE_CORE_GUI_SOUND_DEBUG_H
#define SR_ENGINE_CORE_GUI_SOUND_DEBUG_H

#include <Graphics/GUI/Widget.h>

namespace SR_CORE_GUI_NS {
    class SoundDebug : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        SoundDebug();

        void Draw() override;

    };
}

#endif //SR_ENGINE_CORE_GUI_SOUND_DEBUG_H
```


