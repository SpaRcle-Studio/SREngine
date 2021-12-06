//
// Created by Nikita on 13.12.2020.
//

#ifndef GAMEENGINE_POINTLIGHT_H
#define GAMEENGINE_POINTLIGHT_H

#include <Lighting/Light.h>

namespace Framework::Graphics {
    class Render;

    class PointLight : public Light {
    public:
        PointLight(Render* render);
    private:
        float m_radius = 1.f;
    };
}

#endif //GAMEENGINE_POINTLIGHT_H
