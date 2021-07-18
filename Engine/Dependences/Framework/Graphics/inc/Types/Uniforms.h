//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_UNIFORMS_H
#define GAMEENGINE_UNIFORMS_H

#include <glm/glm.hpp>

namespace Framework::Graphics {
    enum class UBOType {
        Common, Shared
    };

    struct SkyboxUBO {
        glm::mat4 PVMat;
    };

    struct ProjViewUBO {
        glm::mat4 proj;
        glm::mat4 view;
    };

    struct Mesh3DUBO {
        glm::mat4 model;
    };
}

#endif //GAMEENGINE_UNIFORMS_H
