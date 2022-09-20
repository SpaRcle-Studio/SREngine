//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_UNIFORMS_H
#define GAMEENGINE_UNIFORMS_H

#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS(UBOType,
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
        glm::vec4 color;
    };

    struct WireframeUBO {
        glm::mat4 model;
        glm::vec4 color;
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
                {"WireframeUBO",      sizeof(WireframeUBO)},
                {"PostProcessingUBO", sizeof(PostProcessingUBO)},
        };
        if (auto find = uniformSizes.find(name); find != uniformSizes.end())
            return find->second;
        else
            return 0;
    }
}

#endif //GAMEENGINE_UNIFORMS_H
