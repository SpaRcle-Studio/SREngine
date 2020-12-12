//
// Created by Nikita on 13.12.2020.
//

#ifndef GAMEENGINE_SPOTLIGHT_H
#define GAMEENGINE_SPOTLIGHT_H

#include <Lighting/Light.h>

namespace Framework::Graphics {
    class Render;

    class Spotlight : public Light {
    public:
        Spotlight(Render* render);
    private:
        float m_radius = 1.f;
        float m_distance = 10.f;
    };
}

#endif //GAMEENGINE_SPOTLIGHT_H
