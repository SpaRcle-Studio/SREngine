//
// Created by Nikita on 13.12.2020.
//

#ifndef GAMEENGINE_DIRECTIONALLIGHT_H
#define GAMEENGINE_DIRECTIONALLIGHT_H

#include <Graphics/Lighting/Light.h>

namespace Framework::Graphics {
    class Render;

    class DirectionalLight : public Light {
    public:
        DirectionalLight(Render* render);
    };
}

#endif //GAMEENGINE_DIRECTIONALLIGHT_H
