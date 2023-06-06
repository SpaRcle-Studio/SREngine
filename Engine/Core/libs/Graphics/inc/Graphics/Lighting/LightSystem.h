//
// Created by Monika on 22.05.2023.
//

#ifndef SRENGINE_LIGHTSYSTEM_H
#define SRENGINE_LIGHTSYSTEM_H

#include <Graphics/Pipeline/Pipeline.h>

namespace SR_GRAPH_NS {
    class DirectionalLight;

    class LightSystem : SR_UTILS_NS::NonCopyable {
    public:
        SR_MATH_NS::FVector3 m_position = SR_MATH_NS::FVector3(40, 30, 5);

    };
}

#endif //SRENGINE_LIGHTSYSTEM_H
