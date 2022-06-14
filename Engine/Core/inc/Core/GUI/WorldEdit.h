//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_WORLDEDIT_H
#define SRENGINE_WORLDEDIT_H

#include <GUI/Widget.h>
#include <Utils/World/Scene.h>

namespace Framework::Core::GUI {
    class WorldEdit : public Graphics::GUI::Widget {
    public:
        WorldEdit();
        ~WorldEdit() override = default;

    public:
        void SetScene(const SR_WORLD_NS::Scene::Ptr& scene);

    protected:
        void Draw() override;

    private:
        SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene> m_scene;

    };
}

#endif //SRENGINE_WORLDEDIT_H
