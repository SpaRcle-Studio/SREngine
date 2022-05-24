//
// Created by Monika on 24.05.2022.
//

#include <Scripting/Base/Behaviour.h>
#include <ECS/GameObject.h>

namespace SR_SCRIPTING_NS {
    Behaviour::Behaviour()
        : IResource(typeid(Behaviour).name())
        , SR_UTILS_NS::Component()
    {
        Component::Init<Behaviour>();
    }

    Behaviour::GameObjectPtr Behaviour::GetGameObject() const {
        if (auto&& parent = GetParent()) {
            return parent->GetThis();
        }

        return GameObjectPtr();
    }

    Behaviour::TransformPtr Behaviour::GetTransform() const {
        if (auto&& parent = GetParent()) {
            return parent->GetTransform();
        }

        return nullptr;
    }
}