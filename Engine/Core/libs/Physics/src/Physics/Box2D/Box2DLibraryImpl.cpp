//
// Created by Monika on 27.11.2022.
//

#include <Physics/Box2D/Box2DLibraryImpl.h>

namespace SR_PHYSICS_NS {
    bool Box2DLibraryImpl::Initialize() {
        return true;
    }

    bool Box2DLibraryImpl::IsShapeSupported(ShapeType type) const {
        switch (type) {
            case ShapeType::Box2D:
            case ShapeType::Circle2D:
            case ShapeType::Edge2D:
            case ShapeType::TriangleMesh2D:
                return true;
            default:
                return false;
        }
    }

    SR_PTYPES_NS::CollisionShape *Box2DLibraryImpl::CreateCollisionShape() {
        return LibraryImpl::CreateCollisionShape();
    }

    SR_PTYPES_NS::Rigidbody2D *Box2DLibraryImpl::CreateRigidbody2D() {
        return LibraryImpl::CreateRigidbody2D();
    }

    SR_PHYSICS_NS::PhysicsWorld *Box2DLibraryImpl::CreatePhysicsWorld(LibraryImpl::Space space) {
        return LibraryImpl::CreatePhysicsWorld(space);
    }
}
