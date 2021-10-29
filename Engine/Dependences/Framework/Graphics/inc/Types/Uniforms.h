//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_UNIFORMS_H
#define GAMEENGINE_UNIFORMS_H

#include <glm/glm.hpp>
#include <map>
#include <Utils/Enumerations.h>

namespace Framework::Graphics {
    SR_ENUM_CLASS(UBOType,
        Common, Shared
    )

    struct SkyboxUBO {
        glm::mat4 PVMat;
    };

    struct ProjViewUBO {
        glm::mat4 proj;
        glm::mat4 view;
    };

    struct Mesh3dUBO {
        glm::mat4 model;
    };

    struct PostProcessingUBO {
        float gamma;
        float saturation;
    };

    static uint64_t GetUniformSize(const std::string& name) {
        static const std::map<std::string, uint64_t> uniformSizes = {
                {"SkyboxUBO",         sizeof(SkyboxUBO)},
                {"ProjViewUBO",       sizeof(ProjViewUBO)},
                {"Mesh3dUBO",         sizeof(Mesh3dUBO)},
                {"PostProcessingUBO", sizeof(PostProcessingUBO)},
        };
        if (auto find = uniformSizes.find(name); find != uniformSizes.end())
            return find->second;
        else
            return 0;
    }
}

#endif //GAMEENGINE_UNIFORMS_H
