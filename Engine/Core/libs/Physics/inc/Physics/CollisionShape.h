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
    class LibraryImpl;
}

namespace SR_PTYPES_NS {
    class CollisionShape : public SR_UTILS_NS::NonCopyable {
        friend class SR_PHYSICS_NS::PhysicsScene;
    public:
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
        using Ptr = CollisionShape*;
        using Super = SR_UTILS_NS::NonCopyable;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
    public:
        explicit CollisionShape(LibraryPtr pLibrary, ShapeType type);
        ~CollisionShape() override;

    public:
        virtual bool Update() { return false; }

        void SetHeight(float_t height);
        void SetRadius(float_t radius);
        void SetSize(const SR_MATH_NS::FVector3& size);
        void SetScale(const SR_MATH_NS::FVector3& scale);

        SR_NODISCARD virtual SR_MATH_NS::FVector3 CalculateLocalInertia(float_t mass) const;

        SR_NODISCARD float_t GetHeight() const;
        SR_NODISCARD float_t GetRadius() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetSize() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetScale() const;

        SR_NODISCARD bool Valid() const noexcept;
        SR_NODISCARD ShapeType GetType() const noexcept;
        SR_NODISCARD virtual void* GetHandle() const noexcept { return nullptr; }

    protected:
        LibraryPtr m_library = nullptr;

        SR_MATH_NS::FVector3 m_scale;
        SR_MATH_NS::FVector3 m_bounds;

        const ShapeType m_type;

    };
}


#endif //SRENGINE_COLLISIONSHAPE_H
