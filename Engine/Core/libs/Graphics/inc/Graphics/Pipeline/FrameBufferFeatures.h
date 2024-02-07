//
// Created by Monika on 07.02.2024.
//

#ifndef SR_ENGINE_FRAME_BUFFER_FEATURES_H
#define SR_ENGINE_FRAME_BUFFER_FEATURES_H

#include <Utils/Debug.h>

namespace SR_GRAPH_NS {
    struct FrameBufferFeatures {
        bool depthLoad = false;
        bool colorLoad = false;
        bool depthTransferSrc = false;
        bool colorTransferSrc = false;
        bool depthTransferDst = false;
        bool colorTransferDst = false;
        bool depthShaderRead = false;
        bool colorShaderRead = true;
    };
}

#endif //SR_ENGINE_FRAME_BUFFER_FEATURES_H
