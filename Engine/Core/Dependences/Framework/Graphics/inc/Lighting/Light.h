//
// Created by Nikita on 13.12.2020.
//

#ifndef GAMEENGINE_LIGHT_H
#define GAMEENGINE_LIGHT_H

#include <Math/Vector3.h>

namespace Framework::Graphics {
    class Render;

    class Light {
    protected:
        Light(Render* render);
        ~Light() = default;
    protected:
        Render* m_render = nullptr;

        glm::vec3 m_position = { 0,0,0 };
        glm::vec3 m_rotation = { 0, 0, 0 };
        float m_intensity = 1.f;
    };
}

#endif //GAMEENGINE_LIGHT_H
