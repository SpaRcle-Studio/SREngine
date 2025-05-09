

# File RenderPredicates.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**RenderPredicates.h**](RenderPredicates_8h.md)

[Go to the documentation of this file](RenderPredicates_8h.md)


```C++
//
// Created by Monika on 03.06.2024.
//

#ifndef SR_ENGINE_GRAPHICS_RENDER_PREDICATES_H
#define SR_ENGINE_GRAPHICS_RENDER_PREDICATES_H

#include <Graphics/macros.h>

#include <Utils/Types/StringAtom.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GTYPES_NS {
    class Shader;
}

namespace SR_GRAPH_NS {
    class LayerFilterPredicate {
    public:
        virtual ~LayerFilterPredicate() = default;
        SR_NODISCARD virtual bool IsLayerAllowed(SR_UTILS_NS::StringAtom layer) const = 0;
    };

    class PriorityFilterPredicate {
    public:
        virtual ~PriorityFilterPredicate() = default;
        SR_NODISCARD virtual bool IsPriorityAllowed(int64_t priority) const = 0;
    };

    class ShaderReplacePredicate {
    public:
        virtual ~ShaderReplacePredicate() = default;
        SR_NODISCARD virtual SR_GRAPH_NS::ShaderUseInfo ReplaceShader(SR_GTYPES_NS::Shader* pShader) const = 0;
    };
}

#endif //SR_ENGINE_GRAPHICS_RENDER_PREDICATES_H
```


