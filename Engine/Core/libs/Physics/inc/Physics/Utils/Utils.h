//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_PHYSICS_UTILS_H
#define SRENGINE_PHYSICS_UTILS_H

#include <Utils/Common/Enumerations.h>

namespace SR_PHYSICS_NS {
    SR_ENUM_NS_CLASS(LibraryType,
         Unknown = 0,
         Bullet3 = 1,
         Newton = 2,
         PhysX = 3,
         Havok = 4,
         Volt = 5,
         Shark = 6
    );

    SR_ENUM_NS_CLASS(ShapeType,
         Unknown,

         Box2D,
         Cylinder2D,
         Capsule2D,
         Sphere2D,
         TriangleMesh2D,
         Convex2D,
         Cone2D,

         Plane3D,
         Box3D,
         Cylinder3D,
         Capsule3D,
         Sphere3D,
         TriangleMesh3D,
         Convex3D,
         Cone3D
    )
}

namespace SR_PHYSICS_UTILS_NS {
    SR_MAYBE_UNUSED static bool Is2DShape(ShapeType type) {
        switch (type) {
            case ShapeType::Box2D:
            case ShapeType::Cylinder2D:
            case ShapeType::Capsule2D:
            case ShapeType::Sphere2D:
            case ShapeType::TriangleMesh2D:
            case ShapeType::Convex2D:
            case ShapeType::Cone2D:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static bool Is3DShape(ShapeType type) {
        switch (type) {
            case ShapeType::Plane3D:
            case ShapeType::Box3D:
            case ShapeType::Cylinder3D:
            case ShapeType::Capsule3D:
            case ShapeType::Sphere3D:
            case ShapeType::TriangleMesh3D:
            case ShapeType::Convex3D:
            case ShapeType::Cone3D:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static constexpr bool IsSphere(ShapeType type) {
        switch (type) {
            case ShapeType::Sphere2D:
            case ShapeType::Sphere3D:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static constexpr bool IsBox(ShapeType type) {
        switch (type) {
            case ShapeType::Box2D:
            case ShapeType::Box3D:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static constexpr bool IsCapsule(ShapeType type) {
        switch (type) {
            case ShapeType::Capsule2D:
            case ShapeType::Capsule3D:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static constexpr bool IsCylinder(ShapeType type) {
        switch (type) {
            case ShapeType::Cylinder2D:
            case ShapeType::Cylinder3D:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static constexpr bool IsShapeHasRadius(ShapeType type) {
        return IsSphere(type) || IsCapsule(type) || IsCylinder(type);
    }

    SR_MAYBE_UNUSED static constexpr bool IsShapeHasHeight(ShapeType type) {
        return IsCapsule(type) || IsCylinder(type);
    }

    SR_MAYBE_UNUSED static constexpr bool IsShapeHasSize(ShapeType type) {
        return IsBox(type) || type == ShapeType::Plane3D;
    }
}

#endif //SRENGINE_PHYSICS_UTILS_H
