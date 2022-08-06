//
// Created by Monika on 28.07.2022.
//

#include <Physics/3D/Rigidbody3D.h>

namespace SR_PHYSICS_NS::Types {
    Rigidbody3D::Rigidbody3D()
        : Rigidbody()
    {
        SR_UTILS_NS::Component::InitComponent<Rigidbody3D>();
    }
}
