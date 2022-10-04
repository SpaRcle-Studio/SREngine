//
// Created by Monika on 28.09.2022.
//

#ifndef SRENGINE_COLLISIONSHAPE_H
#define SRENGINE_COLLISIONSHAPE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Math/Matrix4x4.h>

#include <Physics/PhysicsLib.h>

namespace SR_PHYSICS_NS {
    class PhysicsScene;
}

namespace SR_PHYSICS_NS::Types {
    class CollisionShape : public SR_UTILS_NS::NonCopyable {
        friend class SR_PHYSICS_NS::PhysicsScene;
    public:
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
        using Ptr = CollisionShape*;
        using Super = SR_UTILS_NS::NonCopyable;

    public:
        explicit CollisionShape(ShapeType type);
        ~CollisionShape() override;

    public:
        void Update();

        void SetHeight(float_t height);
        void SetRadius(float_t radius);
        void SetSize(const SR_MATH_NS::FVector3& size);
        void SetScale(const SR_MATH_NS::FVector3& scale);

        SR_NODISCARD SR_MATH_NS::FVector3 CalculateLocalInertia(float_t mass) const;

        SR_NODISCARD float_t GetHeight() const;
        SR_NODISCARD float_t GetRadius() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetSize() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const;

        SR_NODISCARD bool Valid() const noexcept;
        SR_NODISCARD ShapeType GetType() const noexcept;
        SR_NODISCARD void* GetHandle() const noexcept;

    private:
        SR_MATH_NS::FVector3 m_scale;

        btCollisionShape* m_shape = nullptr;
        const ShapeType m_type;

        btVector3 m_bounds;
    };
}


#endif //SRENGINE_COLLISIONSHAPE_H
