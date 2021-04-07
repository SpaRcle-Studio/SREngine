//
// Created by Nikita on 07.04.2021.
//

#ifndef GAMEENGINE_VULKANUNIFORM_H
#define GAMEENGINE_VULKANUNIFORM_H

namespace Framework::Graphics::VulkanTools {
    struct UniformTransformation {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };

    struct UniformBVec3 {

    };

    struct UniformIVec3 {

    };

    struct UniformFVec4 {

    };
}

#endif //GAMEENGINE_VULKANUNIFORM_H
