//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_UNIFORMS_H
#define GAMEENGINE_UNIFORMS_H

#include <glm/glm.hpp>

namespace Framework::Graphics {
    struct Model3DUniform {
        glm::mat4 proj;
        glm::mat4 view;
        glm::mat4 model;
    };
}

#endif //GAMEENGINE_UNIFORMS_H
