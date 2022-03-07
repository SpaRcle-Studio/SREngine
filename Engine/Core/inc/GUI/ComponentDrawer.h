//
// Created by Monika on 23.02.2022.
//

#ifndef SRENGINE_COMPONENTDRAWER_H
#define SRENGINE_COMPONENTDRAWER_H

namespace Framework::Graphics {
    class Camera;

    namespace Types {
        class Mesh3D;
    }
}

namespace Framework::Core::GUI::ComponentDrawer {
    void DrawComponent(Framework::Graphics::Camera* camera);
    void DrawComponent(Framework::Graphics::Types::Mesh3D* mesh3d);
}

#endif //SRENGINE_COMPONENTDRAWER_H
