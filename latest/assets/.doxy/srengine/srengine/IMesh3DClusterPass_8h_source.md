

# File IMesh3DClusterPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**IMesh3DClusterPass.h**](IMesh3DClusterPass_8h.md)

[Go to the documentation of this file](IMesh3DClusterPass_8h.md)


```C++
//
// Created by Monika on 18.10.2023.
//

#ifndef SR_ENGINE_IMESH3DCLUSTERPASS_H
#define SR_ENGINE_IMESH3DCLUSTERPASS_H

#include <Graphics/Pass/IMeshClusterPass.h>

namespace SR_GRAPH_NS {
    class SR_DEPRECATED IMesh3DClusterPass : public IMeshClusterPass {
        using Super = IMeshClusterPass;
    public:
        bool Init() override;

    protected:
        bool Render() override;
        void Update() override;

        void OnClusterDirty() override;

        virtual bool RenderCluster(MeshCluster& meshCluster);
        virtual void UpdateCluster(MeshCluster& meshCluster);
        virtual void MarkDirtyCluster(MeshCluster& meshCluster);

    protected:
        ShadowMapPass* m_shadowMapPass = nullptr;
        CascadedShadowMapPass* m_cascadedShadowMapPass = nullptr;

    };
}

#endif //SR_ENGINE_IMESH3DCLUSTERPASS_H
```


