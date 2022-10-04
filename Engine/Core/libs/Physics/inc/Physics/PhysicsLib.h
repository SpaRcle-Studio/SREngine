//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_PHYSICSLIB_H
#define SRENGINE_PHYSICSLIB_H

#include <Utils/macros.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Math/Vector3.h>

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btBox2dShape.h>

#include <LinearMath/btVector3.h>
#include <LinearMath/btAlignedObjectArray.h>

namespace SR_PHYSICS_NS {
    SR_ENUM_NS_CLASS(ShapeType,
        Unknown,

        Plane,

        Box2D,
        Cylinder2D,
        Capsule2D,
        Sphere2D,
        TriangleMesh2D,
        Convex2D,
        Cone2D,

        Box3D,
        Cylinder3D,
        Capsule3D,
        Sphere3D,
        TriangleMesh3D,
        Convex3D,
        Cone3D
    )
}

namespace SR_PHYSICS_NS::Tools {
    static btVector3 FV3ToBtV3(const SR_MATH_NS::FVector3& vector3) {
        return btVector3(vector3.x, vector3.y, vector3.z);
    }

    static SR_MATH_NS::FVector3 BtV33ToFV(const btVector3& vector3) {
        return SR_MATH_NS::FVector3(vector3.x(), vector3.y(), vector3.z());
    }

    static constexpr bool IsSphere(ShapeType type) {
        switch (type) {
            case ShapeType::Sphere2D:
            case ShapeType::Sphere3D:
                return true;
            default:
                return false;
        }
    }

    static constexpr bool IsBox(ShapeType type) {
        switch (type) {
            case ShapeType::Box2D:
            case ShapeType::Box3D:
                return true;
            default:
                return false;
        }
    }

    static constexpr bool IsCapsule(ShapeType type) {
        switch (type) {
            case ShapeType::Capsule2D:
            case ShapeType::Capsule3D:
                return true;
            default:
                return false;
        }
    }

    static constexpr bool IsCylinder(ShapeType type) {
        switch (type) {
            case ShapeType::Cylinder2D:
            case ShapeType::Cylinder3D:
                return true;
            default:
                return false;
        }
    }

    static constexpr bool IsShapeHasRadius(ShapeType type) {
        return IsSphere(type) || IsCapsule(type) || IsCylinder(type);
    }

    static constexpr bool IsShapeHasHeight(ShapeType type) {
        return IsCapsule(type) || IsCylinder(type);
    }

    static constexpr bool IsShapeHasSize(ShapeType type) {
        return IsBox(type) || type == ShapeType::Plane;
    }

    static constexpr ShapeType GetDefaultShape() {
        return ShapeType::Box3D;
    }

    static constexpr bool IsShapeSupported(ShapeType type) {
        switch (type) {
            case ShapeType::Box2D:
            case ShapeType::Box3D:
            case ShapeType::Cylinder3D:
            case ShapeType::Capsule3D:
            case ShapeType::Sphere3D:
            case ShapeType::Plane:
                return true;
            case ShapeType::TriangleMesh3D:
            case ShapeType::Convex3D:
            case ShapeType::Cone3D:
            case ShapeType::Cylinder2D:
            case ShapeType::TriangleMesh2D:
            case ShapeType::Convex2D:
            case ShapeType::Cone2D:
            case ShapeType::Unknown:
            case ShapeType::Sphere2D:
            case ShapeType::Capsule2D:
            default:
                return false;
        }
    }
}

#endif //SRENGINE_PHYSICSLIB_H
