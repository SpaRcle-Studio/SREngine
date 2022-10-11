//
// Created by Nikita on 01.04.2021.
//

#ifndef GAMEENGINE_PIPELINE_H
#define GAMEENGINE_PIPELINE_H

#include <Utils/Common/Enumerations.h>

namespace SR_GTYPES_NS {
    SR_ENUM_NS_CLASS(MeshType,
         Unknown = 0,
         Static = 1,
         Wireframe = 2,
         Skinned = 3,
         Sprite2D = 4,
         Procedural = 5,
         Line
    )
}

namespace SR_GRAPH_NS {
    enum class PipeLine {
        Unknown, OpenGL, Vulkan, DirectX9, DirectX10, DirectX11, DirectX12
    };

    typedef PipeLine PipeLineType;
    typedef PipeLine PipelineType;
}

#endif //GAMEENGINE_PIPELINE_H
