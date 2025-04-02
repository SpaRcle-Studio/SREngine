

# File Utils.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**Utils**](dir_dd1b3b4f1ed2be15b5dc9d2255b7a6aa.md) **>** [**Utils.h**](Physics_2inc_2Physics_2Utils_2Utils_8h.md)

[Go to the documentation of this file](Physics_2inc_2Physics_2Utils_2Utils_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_PHYSICS_UTILS_H
#define SR_ENGINE_PHYSICS_UTILS_H

#include <Utils/Common/Measurement.h>

namespace SR_PHYSICS_NS {
    SR_ENUM_NS_CLASS(LibraryType,
         Unknown = 0,
         Bullet3 = 1,
         Newton = 2,
         PhysX = 3,
         Havok = 4,
         Volt = 5,
         Shark = 6,
         Box2D = 7
    );

    SR_ENUM_NS_CLASS(ShapeType,
         Unknown,

         Box2D,
         Cylinder2D,
         Capsule2D,
         Circle2D,
         TriangleMesh2D,
         Cone2D,
         Edge2D,

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
            case ShapeType::Circle2D:
            case ShapeType::TriangleMesh2D:
            case ShapeType::Edge2D:
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
            case ShapeType::Circle2D:
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

    SR_MAYBE_UNUSED static constexpr bool IsPlane(ShapeType type) {
        switch (type) {
            case ShapeType::Plane3D:
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

    SR_MAYBE_UNUSED static constexpr bool IsConvex(ShapeType type) {
        switch (type) {
            case ShapeType::Convex3D:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static constexpr bool IsTriangleMesh(ShapeType type) {
        switch (type) {
            case ShapeType::TriangleMesh3D:
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

    SR_MAYBE_UNUSED static constexpr bool IsShapeHasGeometry(ShapeType type) {
        return IsConvex(type) || IsTriangleMesh(type);
    }

    SR_MAYBE_UNUSED static constexpr bool IsShapeHasRadius(ShapeType type) {
        return IsSphere(type) || IsCapsule(type) || IsCylinder(type);
    }

    SR_MAYBE_UNUSED static constexpr bool IsShapeHasHeight(ShapeType type) {
        return IsCapsule(type) || IsCylinder(type);
    }

    SR_MAYBE_UNUSED static constexpr bool IsShapeHasSize(ShapeType type) {
        return IsBox(type) || IsShapeHasGeometry(type);
    }
}

#endif //SR_ENGINE_PHYSICS_UTILS_H
```


