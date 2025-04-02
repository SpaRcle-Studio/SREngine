

# File SwapchainPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**SwapchainPass.h**](SwapchainPass_8h.md)

[Go to the documentation of this file](SwapchainPass_8h.md)


```C++
//
// Created by Monika on 22.07.2022.
//

#ifndef SR_ENGINE_SWAPCHAINPASS_H
#define SR_ENGINE_SWAPCHAINPASS_H

#include <Utils/Math/Vector3.h>
#include <Graphics/Pass/GroupPass.h>

namespace SR_GRAPH_NS {
    class SwapchainPass : public GroupPass {
        SR_REGISTER_LOGICAL_NODE(SwapchainPass, Swapchain Pass, { "Passes" })
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        bool Render() override;
        void Update() override;
        void InitNode() override;

    private:
        float_t m_depth = 1.f;
        SR_MATH_NS::FColor m_color;

    };
}

#endif //SR_ENGINE_SWAPCHAINPASS_H
```


