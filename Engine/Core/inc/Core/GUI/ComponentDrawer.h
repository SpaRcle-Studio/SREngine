//
// Created by Monika on 23.02.2022.
//

#ifndef SRENGINE_COMPONENTDRAWER_H
#define SRENGINE_COMPONENTDRAWER_H

#include <Utils/stdInclude.h>

namespace SR_SCRIPTING_NS {
    class Behaviour;
}

namespace SR_GRAPH_NS {
    class Camera;

    namespace Types {
        class Mesh3D;
        class Material;
    }
}

namespace SR_CORE_NS::GUI::ComponentDrawer {
    void DrawComponent(SR_SCRIPTING_NS::Behaviour*& behaviour, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Camera*& camera, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::Mesh3D*& mesh3d, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::Material*& material, int32_t index);
}

#endif //SRENGINE_COMPONENTDRAWER_H
