//
// Created by Monika on 28.09.2022.
//

#ifndef SR_ENGINE_PHYSICS_COLLISION_SHAPE_H
#define SR_ENGINE_PHYSICS_COLLISION_SHAPE_H

#include <Physics/PhysicsLib.h>
#include <Physics/PhysicsMaterial.h>

#include <Utils/Serialization/Serializable.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/IRawMeshHolder.h>
#include <Utils/Types/FastMemoryArray.h>
#include <Utils/Math/Matrix4x4.h>
#include <Utils/ECS/Transform.h>

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
        virtual std::optional<bool> UpdateShape() { return false; }
        virtual bool UpdateMatrix() { return false; }

        void SetShape(CollisionShape* pShape) { m_shape = pShape; }

        SR_NODISCARD virtual SR_MATH_NS::FVector3 CalculateLocalInertia(float_t mass) const {
            return SR_MATH_NS::FVector3::Zero();
        }

        SR_NODISCARD virtual const std::vector<void*>& GetHandles() const noexcept {
            static std::vector<void*> emptyHandles;
            return emptyHandles;
        }

        SR_NODISCARD CollisionShape* GetShape() const noexcept { return m_shape; }

    private:
        CollisionShape* m_shape = nullptr;

    };

    /// @category(Physics)
    class CollisionShape final : public SR_UTILS_NS::Component, public SR_HTYPES_NS::IRawMeshHolder {
        SR_CLASS()
        friend class SR_PHYSICS_NS::PhysicsScene;
        using Super = SR_UTILS_NS::Component;
        struct CustomTriangleMeshData {
            SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3> vertices;
            SR_HTYPES_NS::FastMemoryArray<uint32_t> indices;
        };
    public:
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
        using Ptr = SR_HTYPES_NS::SharedPtr<CollisionShape>;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;

    public:
        ~CollisionShape() override;

    public:
        bool ExecuteInEditMode() const override { return true; }

        void Update(float_t dt) override;
        void OnDetached() override;
        void OnMatrixDirty() override;

        void OnDisable() override;
        void OnEnable() override;

        void OnRigidbodyDetached();

        void OnRawMeshChanged() override;

        std::optional<bool> UpdateShape();
        bool UpdateMatrix();

        void UpdateDebugShape();
        void RemoveDebugShape();

        void SetType(ShapeType type);
        void SetRigidbody(Rigidbody* pRigidbody);

        void SetHeight(float_t height);
        void SetRadius(float_t radius);
        void SetSize(const SR_MATH_NS::FVector3& size);
        void SetBounds(const SR_MATH_NS::FVector3& bounds);
        void SetPlaneSize(const SR_MATH_NS::FVector2& size);

        void SwapCustomTriangleMeshIndices(SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices);
        void SetCustomTriangleMeshIndices(const SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices);
        void SwapCustomTriangleMeshVertices(SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3>& vertices);

        void SwapBoxes(SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::AABB>& boxes);
        SR_NODISCARD const SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::AABB>& GetBoxes() const { return m_boxes; }

        SR_NODISCARD SR_MATH_NS::FVector3 GetCenter() const noexcept { return m_center; }
        SR_NODISCARD SR_MATH_NS::FVector3 GetCenterDirection() const noexcept;

        SR_NODISCARD SR_MATH_NS::FVector3 CalculateLocalInertia(float_t mass) const;

        SR_NODISCARD float_t GetHeight() const;
        SR_NODISCARD float_t GetRadius() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetSize() const;
        SR_NODISCARD SR_MATH_NS::FVector3 GetBounds() const { return m_bounds; }
        SR_NODISCARD SR_MATH_NS::FVector2 GetPlaneSize() const { return SR_MATH_NS::FVector2(m_bounds.x, m_bounds.z); }
        SR_NODISCARD Rigidbody* GetRigidbody() const;

        SR_NODISCARD const SR_MATH_NS::FVector3& GetTranslation() const noexcept { return m_translation; }
        SR_NODISCARD const SR_MATH_NS::Quaternion& GetRotation() const noexcept { return m_rotation; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetScale() const noexcept { return m_scale; }
        SR_NODISCARD PhysicsMaterial::Ptr GetPhysicsMaterial() const noexcept { return m_materialData; }
        SR_NODISCARD const CustomTriangleMeshData& GetCustomTriangleMeshData() const noexcept { return m_customTriangleMeshData; }

        SR_NODISCARD bool HasGeometry() const noexcept;
        SR_NODISCARD bool IsShapeValid() const noexcept;
        SR_NODISCARD ShapeType GetType() const noexcept;
        SR_NODISCARD const std::vector<void*>& GetHandles() const noexcept;

        virtual void SetCenter(const SR_MATH_NS::FVector3& center);

    private:
        void ReInitRigidbody();
        void OnShapeDirty();
        void SetMaterial(const SR_UTILS_NS::Path& path);

    protected:
        Rigidbody* m_currentRigidbody = nullptr;
        CollisionShapeImpl* m_impl = nullptr;
        uint64_t m_debugId = SR_ID_INVALID;
        bool m_isShapeDirty = true;

        /// decomposed matrix
        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::Quaternion m_rotation;
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();

        SR_PTYPES_NS::PhysicsMaterial::Ptr m_materialData;
        SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::AABB> m_boxes;

        CustomTriangleMeshData m_customTriangleMeshData;

    protected:
        /// @property @onChanged(ReInitRigidbody)
        SR_UTILS_NS::EntityRef<Rigidbody> m_rigidbody;
        /// @property @setter(SetType) @getter(GetType)
        ShapeType m_type = ShapeType::Unknown;
        /// @property @setter(SetMaterial)
        /// @customArgs(pick: enabled, filter name: Physics material, relative: resources)
        /// @customArg(filter value: sras)
        SR_UTILS_NS::Path m_material;
        /// @property @setter(SetCenter) @getter(GetCenter) @drag(0.01f)
        SR_MATH_NS::FVector3 m_center;
        /// @property @setter(SetBounds) @getter(GetBounds) @hidden
        SR_MATH_NS::FVector3 m_bounds = SR_MATH_NS::FVector3::One();

        /// @virtualProperty(size) @setter(SetSize) @getter(GetSize) @dontSave @drag(0.01f) @resetValue(SR_MATH_NS::FVector3::One())
        /// @condition(SR_PHYSICS_UTILS_NS::IsShapeHasSize(This.GetType())) @dontClone
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(height) @setter(SetHeight) @getter(GetHeight) @dontSave @drag(0.01f) @resetValue(1.f)
        /// @condition(SR_PHYSICS_UTILS_NS::IsShapeHasHeight(This.GetType())) @dontClone
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(radius) @setter(SetRadius) @getter(GetRadius) @dontSave @drag(0.01f) @resetValue(1.f)
        /// @condition(SR_PHYSICS_UTILS_NS::IsShapeHasRadius(This.GetType())) @dontClone
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(plane) @setter(SetPlaneSize) @getter(GetPlaneSize) @dontSave @drag(0.01f) @resetValue(1.f)
        /// @condition(SR_PHYSICS_UTILS_NS::IsPlane(This.GetType())) @dontClone
        SR_VIRTUAL_PROPERTY

        /// @virtualProperty(geometryName) @getter(GetGeometryName) @dontSave @readOnly
        /// @condition(This.HasGeometry())
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(meshPath) @getter(GetMeshPath) @setter(SetRawMesh)
        /// @customArgs(pick: enabled, filter name: Meshes, relative: resources)
        /// @customArg(filter value: fbx,blend,obj,pmx,stl,dae)
        /// @condition(This.HasGeometry())
        SR_VIRTUAL_PROPERTY
        /// @virtualProperty(meshId) @getter(GetMeshId) @setter(SetMeshId)
        /// @condition(This.HasGeometry())
        SR_VIRTUAL_PROPERTY

    };
}


#endif //SR_ENGINE_PHYSICS_COLLISION_SHAPE_H
