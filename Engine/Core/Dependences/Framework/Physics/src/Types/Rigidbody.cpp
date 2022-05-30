//
// Created by Nikita on 16.03.2021.
//
#include <Types/Rigidbody.h>

namespace Framework::Physics::Types {
    Rigidbody::Rigidbody() {
        Helper::Component::InitComponent<Rigidbody>();
    }
}