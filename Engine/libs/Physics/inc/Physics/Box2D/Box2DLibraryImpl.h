//
// Created by Monika on 27.11.2022.
//

#ifndef SR_ENGINE_BOX2DLIBRARYIMPL_H
#define SR_ENGINE_BOX2DLIBRARYIMPL_H

#include <Physics/LibraryImpl.h>

#include <box2d/box2d.h>

namespace SR_PHYSICS_NS {
    class Box2DLibraryImpl : public SR_PHYSICS_NS::LibraryImpl {
        using Super = SR_PHYSICS_NS::LibraryImpl;
    public:
        Box2DLibraryImpl() = default;
        ~Box2DLibraryImpl() override = default;

    public:
        SR_NODISCARD bool Initialize() override;

        SR_NODISCARD bool IsShapeSupported(ShapeType type) const override;
        SR_NODISCARD ShapeType GetDefaultShape() const override { return ShapeType::Box2D; }

        SR_NODISCARD SR_PTYPES_NS::CollisionShape* CreateCollisionShape() override;
        SR_NODISCARD SR_PTYPES_NS::Rigidbody2D* CreateRigidbody2D() override;
        SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld* CreatePhysicsWorld(Space space) override;

    };
}

#endif //SR_ENGINE_BOX2DLIBRARYIMPL_H
