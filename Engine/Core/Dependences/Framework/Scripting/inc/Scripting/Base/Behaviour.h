//
// Created by Monika on 24.05.2022.
//

#ifndef SRENGINE_BEHAVIOUR_H
#define SRENGINE_BEHAVIOUR_H

#include <ECS/Component.h>
#include <ResourceManager/IResource.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Transform3D;
}

namespace SR_SCRIPTING_NS {
    class Behaviour : public SR_UTILS_NS::IResource, public SR_UTILS_NS::Component {
        using GameObjectPtr = SR_HTYPES_NS::SafePtr<SR_UTILS_NS::GameObject>;
        using TransformPtr = SR_UTILS_NS::Transform3D*;
    public:
        Behaviour();

    protected:
        ~Behaviour() override = default;

    public:
        SR_NODISCARD GameObjectPtr GetGameObject() const;
        SR_NODISCARD TransformPtr GetTransform() const;

    protected:
        bool Load() override { return SR_UTILS_NS::IResource::Load(); }
        bool Unload() override { return SR_UTILS_NS::IResource::Unload(); }

    };
}

#endif //SRENGINE_BEHAVIOUR_H
