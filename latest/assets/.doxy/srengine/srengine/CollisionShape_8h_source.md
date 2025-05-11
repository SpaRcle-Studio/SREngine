

# File CollisionShape.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**CollisionShape.h**](CollisionShape_8h.md)

[Go to the documentation of this file](CollisionShape_8h.md)


```C++
//
// Created by Monika on 28.09.2022.
//

#ifndef SR_ENGINE_PHYSICS_COLLISION_SHAPE_H
#define SR_ENGINE_PHYSICS_COLLISION_SHAPE_H

#include <Physics/macros.h>

#include <Utils/Serialization/Serializable.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/IRawMeshHolder.h>
#include <Utils/Math/Matrix4x4.h>
#include <Utils/TypeTraits/Properties.h>

#include <Physics/PhysicsLib.h>

namespace SR_PHYSICS_NS {
    class PhysicsScene;
    class LibraryImpl;
}

namespace SR_PTYPES_NS {
    class Rigidbody;
    class CollisionShape;

    class CollisionShapeImpl : public SR_UTILS_NS::NonCopyable {
    public:
        virtual void Update(float_t dt) { }
        virtual bool UpdateShape() { return false; }
        virtual bool UpdateMatrix() { return false; }

        void SetShape(CollisionShape* pShape) { m_shape = pShape; }

        SR_NODISCARD virtual SR_MATH_NS::FVector3 CalculateLocalInertia(float_t mass) const {
            return SR_MATH_NS::FVector3::Zero();
        }

        SR_NODISCARD virtual void* GetHandle() const noexcept { return nullptr; }
        SR_NODISCARD CollisionShape* GetShape() const noexcept { return m_shape; }

    private:
        CollisionShape* m_shape = nullptr;

    };

    class CollisionShape final : public SR_HTYPES_NS::SharedPtr<CollisionShape>
        , public SR_HTYPES_NS::IRawMeshHolder
        , public SR_UTILS_NS::Serializable
    {
        SR_CLASS()
        friend class SR_PHYSICS_NS::PhysicsScene;
    public:
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
        using Ptr = SR_HTYPES_NS::SharedPtr<CollisionShape>;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;

    public:
        CollisionShape();
        ~CollisionShape() override;

    public:
        void Update(float_t dt);

        void OnRawMeshChanged() override;

        bool UpdateShape();
        bool UpdateMatrix();

        void UpdateDebugShape();
        void RemoveDebugShape();

        void ReInitDebugShape();

        void SetType(ShapeType type);

        void SetHeight(float_t height);
        void SetRadius(float_t radius);
        void SetSize(const SR_MATH_NS::FVector3& size);
        void SetBounds(const SR_MATH_NS::FVector3& bounds);
        void SetPlaneSize(const SR_MATH_NS::FVector2& size);
        void SetRigidbody(Rigidbody* pRigidbody) { m_rigidbody = pRigidbody; };

        SR_NODISCARD SR_MATH_NS::FVector3 CalculateLocalInertia(float_t mass) const;

        SR_NODISCARD float_t GetHeight() const;
        SR_NODISCARD float_t GetRadius() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetSize() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetBounds() const { return m_bounds; }
        SR_NODISCARD SR_MATH_NS::FVector2 GetPlaneSize() const { return SR_MATH_NS::FVector2(m_bounds.x, m_bounds.z); }
        SR_NODISCARD Rigidbody* GetRigidbody() const;

        SR_NODISCARD bool HasGeometry() const noexcept;
        SR_NODISCARD bool IsShapeValid() const noexcept;
        SR_NODISCARD ShapeType GetType() const noexcept;
        SR_NODISCARD void* GetHandle() const noexcept;

    protected:
        CollisionShapeImpl* m_impl = nullptr;
        Rigidbody* m_rigidbody = nullptr;

        uint64_t m_debugId = SR_ID_INVALID;

    protected:
        ShapeType m_type = ShapeType::Unknown;
        SR_MATH_NS::FVector3 m_bounds = SR_MATH_NS::FVector3::One();

        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY

        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY
        SR_VIRTUAL_PROPERTY

    };
}


#endif //SR_ENGINE_PHYSICS_COLLISION_SHAPE_H
```


