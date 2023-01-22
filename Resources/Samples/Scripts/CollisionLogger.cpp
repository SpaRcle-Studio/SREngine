//
// Created by innerviewer on 21.01.2023.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>

#include <Libraries/Debug.h>
#include <Libraries/Input.h>

class CollisionLogger : public Behaviour {
    void OnCollisionEnter(const CollisionData& data) override {
        Debug::Log("Collision detected!");
    }
};

REGISTER_BEHAVIOUR(CollisionLogger)
