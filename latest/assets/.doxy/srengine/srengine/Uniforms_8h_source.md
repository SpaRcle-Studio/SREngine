

# File Uniforms.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Uniforms.h**](Uniforms_8h.md)

[Go to the documentation of this file](Uniforms_8h.md)


```C++
//
// Created by Nikita on 30.05.2021.
//

#ifndef SR_ENGINE_UNIFORMS_H
#define SR_ENGINE_UNIFORMS_H

#include <Graphics/macros.h>

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

    SR_MAYBE_UNUSED static uint64_t GetUniformSize(const std::string& name) {
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

#endif //SR_ENGINE_UNIFORMS_H
```


