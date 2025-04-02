

# File Uniforms.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Uniforms.h**](Uniforms_8h.md)

[Go to the documentation of this file](Uniforms_8h.md)


```C++
//
// Created by Nikita on 30.05.2021.
//

#ifndef SR_ENGINE_UNIFORMS_H
#define SR_ENGINE_UNIFORMS_H

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


