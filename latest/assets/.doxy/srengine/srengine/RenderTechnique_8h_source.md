

# File RenderTechnique.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Render**](dir_5ea2fe9b8fa53724ec2c57fac60d8202.md) **>** [**RenderTechnique.h**](RenderTechnique_8h.md)

[Go to the documentation of this file](RenderTechnique_8h.md)


```C++
//
// Created by Monika on 17.07.2022.
//

#ifndef SR_ENGINE_RENDERTECHNIQUE_H
#define SR_ENGINE_RENDERTECHNIQUE_H

#include <Graphics/Render/IRenderTechnique.h>

namespace SR_GRAPH_NS {
    class RenderTechnique : public SR_UTILS_NS::Settings, public IRenderTechnique {
    private:
        RenderTechnique() = default;

    public:
        static RenderTechnique* Load(const SR_UTILS_NS::Path& path);

    protected:
        bool Build() override;

        bool Load() override;
        bool Unload() override;

        bool LoadSettings(const SR_XML_NS::Node &node) override;
        void ClearSettings() override;

    private:
        void LoadPass(const SR_XML_NS::Node& node);
        void ProcessNode(const SR_XML_NS::Node& passNode);

    };
}

#endif //SR_ENGINE_RENDERTECHNIQUE_H
```


