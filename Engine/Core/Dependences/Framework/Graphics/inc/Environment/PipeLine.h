//
// Created by Nikita on 01.04.2021.
//

#ifndef GAMEENGINE_PIPELINE_H
#define GAMEENGINE_PIPELINE_H

#include <Utils/macros.h>

namespace SR_GRAPH_NS {
    enum class PipeLine {
        Unknown, OpenGL, Vulkan, DirectX9, DirectX10, DirectX11, DirectX12
    };
}

#endif //GAMEENGINE_PIPELINE_H
