//
// Created by Monika on 22.11.2022.
//

#include <Physics/Bullet3/Bullet3CollisionShape.h>

namespace SR_PTYPES_NS {
    Bullet3CollisionShape::Bullet3CollisionShape(LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    Bullet3CollisionShape::~Bullet3CollisionShape() {
        SR_SAFE_DELETE_PTR(m_shape)
    }

    bool Bullet3CollisionShape::UpdateShape() {
        if (!m_library->IsShapeSupported(m_type)) {
            SR_WARN("Bullet3CollisionShape::Update() : shape is not supported! Replace to default...");
            m_type = m_library->GetDefaultShape();
        }

        SR_SAFE_DELETE_PTR(m_shape)

        switch (m_type) {
            case ShapeType::Plane3D: {
                m_shape = new btStaticPlaneShape(btVector3(0, 1, 0), 0.f);
                break;
            }
            case ShapeType::Box3D: {
                m_shape = new btBoxShape(btVector3(1, 1, 1));
                break;
            }
            case ShapeType::Capsule3D: {
                m_shape = new btCapsuleShape(1.f, 1.f);
                break;
            }
            case ShapeType::Sphere3D: {
                m_shape = new btSphereShape(1.f);
                break;
            }
            case ShapeType::Cylinder3D: {
                m_shape = new btCylinderShape(btVector3(1.f, 1.f, 1.f));
                break;
            }
            default:
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

    bool Bullet3CollisionShape::UpdateMatrix() {
        if (!m_shape) {
            return false;
        }

        switch (m_type) {
            case ShapeType::Plane3D:
            case ShapeType::Box3D:
                m_shape->setLocalScaling(SR_PHYSICS_UTILS_NS::FV3ToBtV3(GetSize() * GetScale()));
                break;
            case ShapeType::Capsule3D:
            case ShapeType::Cylinder3D:
                m_shape->setLocalScaling(btVector3(GetRadius(), GetHeight(), GetRadius()));
                break;
            case ShapeType::Sphere3D:
                m_shape->setLocalScaling(btVector3(GetRadius(), GetRadius(), GetRadius()));
                break;
            default:
                break;
        }

        return true;
    }
}