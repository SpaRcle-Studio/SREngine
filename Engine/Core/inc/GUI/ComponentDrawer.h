//
// Created by Monika on 23.02.2022.
//

#ifndef SRENGINE_COMPONENTDRAWER_H
#define SRENGINE_COMPONENTDRAWER_H

namespace SR_GRAPH_NS {
    class Camera;

    namespace Types {
        class Mesh3D;
    }
}

namespace Framework::Core::GUI::ComponentDrawer {
    void DrawComponent(SR_GRAPH_NS::Camera* camera);
    void DrawComponent(SR_GRAPH_NS::Types::Mesh3D* mesh3d);
}

#endif //SRENGINE_COMPONENTDRAWER_H
