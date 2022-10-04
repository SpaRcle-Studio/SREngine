//
// Created by Monika on 28.09.2022.
//

#include <Physics/CollisionShape.h>

namespace SR_PHYSICS_NS::Types {
    CollisionShape::CollisionShape(ShapeType type)
        : Super()
        , m_scale(SR_MATH_NS::FVector3::One())
        , m_shape(nullptr)
        , m_type(type)
        , m_bounds(btVector3(1, 1, 1))
    {
        Update();
    }

    CollisionShape::~CollisionShape() {
        SR_SAFE_DELETE_PTR(m_shape)
    }

    void CollisionShape::SetHeight(float_t height) {
        m_bounds.setY(height);
        Update();
    }

    void CollisionShape::SetRadius(float_t radius) {
        if (Tools::IsCylinder(m_type) || Tools::IsCapsule(m_type)) {
            m_bounds.setX(radius);
            m_bounds.setZ(radius);
        }
        else if (Tools::IsSphere(m_type)) {
            m_bounds = btVector3(radius, radius, radius);
        }
        Update();
    }

    void CollisionShape::SetSize(const SR_MATH_NS::FVector3& size) {
        m_bounds = btVector3(size.x, size.y, size.z);
        Update();
    }

    float_t CollisionShape::GetHeight() const {
        return m_bounds.y();
    }

    float_t CollisionShape::GetRadius() const {
        if (Tools::IsCylinder(m_type) || Tools::IsCapsule(m_type)) {
            return m_bounds.x();
        }
        else if (Tools::IsSphere(m_type)) {
            return m_bounds.x();
        }

        return 0.f;
    }

    SR_MATH_NS::FVector3 CollisionShape::GetSize() const {
        if (Tools::IsShapeHasSize(m_type)) {
            return Tools::BtV33ToFV(m_bounds);
        }
        else {
            return SR_MATH_NS::FVector3::One();
        }
    }

    SR_MATH_NS::FVector3 CollisionShape::GetScale() const {
        return m_scale;
    }

    void* CollisionShape::GetHandle() const noexcept {
        return (void*)m_shape;
    }

    ShapeType CollisionShape::GetType() const noexcept {
        return m_type;
    }

    void CollisionShape::SetScale(const SR_MATH_NS::FVector3 &scale) {
        m_scale = scale;
    }

    void CollisionShape::Update() {
        switch (m_type) {
            case ShapeType::Plane: {
                auto&& pShape = (btStaticPlaneShape*)(m_shape ? m_shape : (m_shape = new btStaticPlaneShape(btVector3(0, 1, 0), 0.f)));
                pShape->setLocalScaling(Tools::FV3ToBtV3(GetSize() * GetScale()));
                break;
            }
            case ShapeType::Box3D: {
                auto&& pShape = (btBoxShape*)(m_shape ? m_shape : (m_shape = new btBoxShape(btVector3(1, 1, 1))));
                pShape->setLocalScaling(Tools::FV3ToBtV3(GetSize() * GetScale()));
                break;
            }
            case ShapeType::Box2D: {
                auto&& pShape = (btBox2dShape*)(m_shape ? m_shape : (m_shape = new btBox2dShape(btVector3(1, 1, 1))));
                pShape->setLocalScaling(Tools::FV3ToBtV3(GetSize()));
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
                SR_ERROR("CollisionShape::Update() : unsupported shape! Type: " + SR_UTILS_NS::EnumReflector::ToString(m_type));
                return;
        }
    }

    SR_MATH_NS::FVector3 CollisionShape::CalculateLocalInertia(float_t mass) const {
        btVector3 inertia;

        if (m_shape) {
            m_shape->calculateLocalInertia(mass, inertia);
        }

        return Tools::BtV33ToFV(inertia);
    }

    bool CollisionShape::Valid() const noexcept {
        return Tools::IsShapeSupported(m_type);
    }
}