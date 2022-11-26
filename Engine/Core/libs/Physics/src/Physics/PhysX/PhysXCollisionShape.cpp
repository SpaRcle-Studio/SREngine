//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXCollisionShape.h>

namespace SR_PTYPES_NS {
    PhysXCollisionShape::PhysXCollisionShape(Super::LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    PhysXCollisionShape::~PhysXCollisionShape() {
        SRAssert(!m_shape);
    }

    bool PhysXCollisionShape::UpdateShape() {
        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        if (m_shape) {
            m_shape->release();
            m_shape = nullptr;
        }

        /// TODO: physics materials
        physx::PxMaterial* defaultMaterial = pPhysics->createMaterial(0.f, 0.f, 0.f);

        switch (m_type) {
            case ShapeType::Plane3D: {
                m_shape = pPhysics->createShape(physx::PxPlaneGeometry(), *defaultMaterial, true);
                break;
            }
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

        return true;
    }
}
