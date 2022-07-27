//
// Created by Nikita on 16.03.2021.
//
#include <Types/Rigidbody.h>

namespace Framework::Physics::Types {
    Rigidbody::Rigidbody() {
        SR_UTILS_NS::Component::InitComponent<Rigidbody>();
    }
}