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
