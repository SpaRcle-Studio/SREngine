

# File WorldEdit.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**WorldEdit.h**](WorldEdit_8h.md)

[Go to the documentation of this file](WorldEdit_8h.md)


```C++
//
// Created by Monika on 14.02.2022.
//

#ifndef SR_ENGINE_WORLDEDIT_H
#define SR_ENGINE_WORLDEDIT_H

#include <Utils/World/Scene.h>

#include <Graphics/GUI/Widget.h>

namespace SR_CORE_GUI_NS {
    class WorldEdit : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        WorldEdit();
        ~WorldEdit() override = default;

    public:
        void SetScene(const SR_WORLD_NS::Scene::Ptr& scene) override;

    protected:
        void Draw() override;

    private:
        SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene> m_scene;

    };
}

#endif //SR_ENGINE_WORLDEDIT_H
```


