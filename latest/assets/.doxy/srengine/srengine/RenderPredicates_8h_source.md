

# File RenderPredicates.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Render**](dir_043f3e6d57945a3feea385b5c8b9609d.md) **>** [**RenderPredicates.h**](RenderPredicates_8h.md)

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
        SR_NODISCARD virtual SR_GRAPH_NS::ShaderUseInfo ReplaceShader(const SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Shader>& pShader) const = 0;
    };
}

#endif //SR_ENGINE_GRAPHICS_RENDER_PREDICATES_H
```


