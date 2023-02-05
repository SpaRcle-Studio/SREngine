//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXCollisionShape.h>

namespace SR_PTYPES_NS {
    PhysXCollisionShape::PhysXCollisionShape(Super::LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    PhysXCollisionShape::~PhysXCollisionShape() {
        if (m_shape) {
            m_shape->release();
            m_shape = nullptr;
        }
    }

    bool PhysXCollisionShape::UpdateShape() {
        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        if (m_shape) {
            m_shape->release();
            m_shape = nullptr;
        }

        /// TODO: physics materials
        physx::PxMaterial* defaultMaterial = pPhysics->createMaterial(0.5f, 0.5f, 0.6f);

        switch (m_type) {
            case ShapeType::Box3D: {
                m_shape = pPhysics->createShape(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetSize())), *defaultMaterial, true);
                break;
            }
            case ShapeType::Sphere3D: {
                m_shape = pPhysics->createShape(physx::PxSphereGeometry(GetRadius()), *defaultMaterial, true);
                break;
            }
            case ShapeType::Capsule3D: {
                m_shape = pPhysics->createShape(physx::PxCapsuleGeometry(GetRadius(), GetHeight()), *defaultMaterial, true);
                break;
            }
            default:
                SR_ERROR("PhysXCollisionShape::Update() : unsupported shape! Type: " + SR_UTILS_NS::EnumReflector::ToString(m_type));
                defaultMaterial->release();
                return false;
        }

        SRAssert(m_shape);

        if (m_shape) {
            m_shape->userData = (void*)dynamic_cast<CollisionShape*>(this);
        }

        if (m_rigidbody->IsTrigger()){
            m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
            m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
        }

        return true;
    }

    bool PhysXCollisionShape::UpdateMatrix() {
        if (!m_shape) {
            return false;
        }

        switch (m_type) {
            case ShapeType::Box3D:
                m_shape->setGeometry(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetSize() * GetScale())));
                break;
            case ShapeType::Capsule3D: {
                auto&& maxXZ = SR_MAX(GetScale().x, GetScale().z);
                m_shape->setGeometry(physx::PxCapsuleGeometry(GetRadius() * maxXZ, GetHeight() *  GetScale().y));
                break;
            }
            case ShapeType::Sphere3D:
                m_shape->setGeometry(physx::PxSphereGeometry(GetRadius() * GetScale().Max()));
                break;
            default:
                break;
        }

        return true;
    }
}
