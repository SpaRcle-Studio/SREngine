//
// Created by Monika on 18.09.2022.
//

#include <Physics/3D/BoxCollider3D.h>
#include <Utils/Types/DataStorage.h>

namespace SR_PHYSICS_NS::Types {
    BoxCollider3D::BoxCollider3D()
        : Collider()
    {
        SR_UTILS_NS::Component::InitComponent<BoxCollider3D>();
    }

    BoxCollider3D::ComponentPtr BoxCollider3D::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        return new BoxCollider3D();
    }
}
