//
// Created by Monika on 28.07.2022.
//

#include <Physics/3D/Rigidbody3D.h>
#include <Utils/Types/DataStorage.h>

namespace SR_PHYSICS_NS::Types {
    Rigidbody3D::Rigidbody3D()
        : Rigidbody()
    {
        SR_UTILS_NS::Component::InitComponent<Rigidbody3D>();
    }

    void Rigidbody3D::OnAttached() {
        Rigidbody::OnAttached();
    }

    Rigidbody3D::ComponentPtr Rigidbody3D::LoadComponent(SR_HTYPES_NS::Marshal &marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        return new Rigidbody3D();
    }
}
