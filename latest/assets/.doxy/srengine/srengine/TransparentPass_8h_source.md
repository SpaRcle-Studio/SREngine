

# File TransparentPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**TransparentPass.h**](TransparentPass_8h.md)

[Go to the documentation of this file](TransparentPass_8h.md)


```C++
//
// Created by Monika on 14.07.2022.
//

#ifndef SR_ENGINE_TRANSPARENTPASS_H
#define SR_ENGINE_TRANSPARENTPASS_H

#include <Graphics/Pass/IMesh3DClusterPass.h>

namespace SR_GRAPH_NS {
    class TransparentPass : public IMesh3DClusterPass {
        using Super = IMesh3DClusterPass;
    public:
        SR_NODISCARD MeshClusterType GetClusterType() const noexcept override;

    protected:
      //  void UseSharedUniforms(ShaderPtr pShader) override;

    };
}

#endif //SR_ENGINE_TRANSPARENTPASS_H
```


