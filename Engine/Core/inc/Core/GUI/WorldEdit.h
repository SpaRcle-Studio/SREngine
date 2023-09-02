//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_WORLDEDIT_H
#define SRENGINE_WORLDEDIT_H

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
        SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene> m_scene;

    };
}

#endif //SRENGINE_WORLDEDIT_H
