//
// Created by Monika on 22.11.2022.
//

#include <Physics/Bullet3/Bullet3CollisionShape.h>

namespace SR_PTYPES_NS {
    Bullet3CollisionShape::Bullet3CollisionShape(LibraryPtr pLibrary, ShapeType type)
        : Super(pLibrary, type)
    { }

    Bullet3CollisionShape::~Bullet3CollisionShape() {
        SR_SAFE_DELETE_PTR(m_shape)
    }

    bool Bullet3CollisionShape::Update() {
        switch (m_type) {
            case ShapeType::Plane3D: {
                auto&& pShape = (btStaticPlaneShape*)(m_shape ? m_shape : (m_shape = new btStaticPlaneShape(btVector3(0, 1, 0), 0.f)));
                pShape->setLocalScaling(SR_PHYSICS_UTILS_NS::FV3ToBtV3(GetSize() * GetScale()));
                break;
            }
            case ShapeType::Box3D: {
                auto&& pShape = (btBoxShape*)(m_shape ? m_shape : (m_shape = new btBoxShape(btVector3(1, 1, 1))));
                pShape->setLocalScaling(SR_PHYSICS_UTILS_NS::FV3ToBtV3(GetSize() * GetScale()));
                break;
            }
            case ShapeType::Box2D: {
                auto&& pShape = (btBox2dShape*)(m_shape ? m_shape : (m_shape = new btBox2dShape(btVector3(1, 1, 1))));
                pShape->setLocalScaling(SR_PHYSICS_UTILS_NS::FV3ToBtV3(GetSize()));
                break;
            }
            case ShapeType::Capsule3D: {
                auto&& pShape = (btCapsuleShape*)(m_shape ? m_shape : (m_shape = new btCapsuleShape(1.f, 1.f)));
                pShape->setLocalScaling(btVector3(GetRadius(), GetHeight(), GetRadius()));
                break;
            }
            case ShapeType::Sphere3D: {
                auto&& pShape = (btSphereShape*)(m_shape ? m_shape : (m_shape = new btSphereShape(1.f)));
                pShape->setLocalScaling(btVector3(GetRadius(), GetRadius(), GetRadius()));
                break;
            }
            case ShapeType::Cylinder3D: {
                auto&& pShape = (btCylinderShape*)(m_shape ? m_shape : (m_shape = new btSphereShape(1.f)));
                pShape->setLocalScaling(btVector3(GetRadius(), GetHeight(), GetRadius()));
                break;
            }
            case ShapeType::Unknown:
            case ShapeType::Cylinder2D:
            case ShapeType::Capsule2D:
            case ShapeType::Sphere2D:
            case ShapeType::TriangleMesh2D:
            case ShapeType::Convex2D:
            case ShapeType::TriangleMesh3D:
            case ShapeType::Cone2D:
            case ShapeType::Cone3D:
            case ShapeType::Convex3D:
                SR_ERROR("Bullet3CollisionShape::Update() : unsupported shape! Type: " + SR_UTILS_NS::EnumReflector::ToString(m_type));
                return false;
        }

        return true;
    }

    SR_MATH_NS::FVector3 Bullet3CollisionShape::CalculateLocalInertia(float_t mass) const {
        btVector3 inertia;

        if (m_shape) {
            m_shape->calculateLocalInertia(mass, inertia);
        }

        return SR_PHYSICS_UTILS_NS::BtV33ToFV(inertia);
    }
}