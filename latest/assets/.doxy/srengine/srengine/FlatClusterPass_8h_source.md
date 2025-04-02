

# File FlatClusterPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**FlatClusterPass.h**](FlatClusterPass_8h.md)

[Go to the documentation of this file](FlatClusterPass_8h.md)


```C++
//
// Created by Monika on 18.10.2023.
//

#ifndef SR_ENGINE_FLATCLUSTERPASS_H
#define SR_ENGINE_FLATCLUSTERPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class FlatClusterPass : public IMeshClusterPass {
        SR_REGISTER_LOGICAL_NODE(FlatClusterPass, Flat Cluster Pass, { "Passes" })
        using Super = IMeshClusterPass;
    public:
        SR_NODISCARD MeshClusterType GetClusterType() const noexcept override;

        void Update() override;
        bool Render() override;

        void UseSharedUniforms(SR_GTYPES_NS::Shader* pShader) override;
        void OnClusterDirty() override;
    };
}

#endif //SR_ENGINE_FLATCLUSTERPASS_H
```


