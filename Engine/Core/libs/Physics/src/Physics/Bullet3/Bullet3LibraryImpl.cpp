//
// Created by Monika on 22.11.2022.
//

#include <Physics/Bullet3/Bullet3LibraryImpl.h>

#include <Physics/Bullet3/Bullet3CollisionShape.h>
#include <Physics/Bullet3/Bullet3Rigidbody3D.h>
#include <Physics/Bullet3/Bullet3PhysicsWorld.h>

namespace SR_PHYSICS_NS {
    bool Bullet3LibraryImpl::IsShapeSupported(ShapeType type) const {
        switch (type) {
            case ShapeType::Box2D:
            case ShapeType::Box3D:
            case ShapeType::Cylinder3D:
            case ShapeType::Capsule3D:
            case ShapeType::Sphere3D:
            case ShapeType::Plane3D:
                return true;
            default:
                return false;
        }
    }

    SR_PTYPES_NS::CollisionShape *Bullet3LibraryImpl::CreateCollisionShape() {
        return new SR_PTYPES_NS::Bullet3CollisionShape(this);
    }

    SR_PTYPES_NS::Rigidbody3D *Bullet3LibraryImpl::CreateRigidbody3D() {
        auto&& pRigidbody = new SR_PTYPES_NS::Bullet3Rigidbody3D(this);

        return pRigidbody;
    }

    SR_PHYSICS_NS::PhysicsWorld *Bullet3LibraryImpl::CreatePhysicsWorld(Space space) {
        return new SR_PHYSICS_NS::Bullet3PhysicsWorld(this, space);
    }
}