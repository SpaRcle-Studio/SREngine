//
// Created by Monika on 26.03.2026.
//

#ifndef SR_ENGINE_PHYSICS_CHARACTER_CONTROLLER_H
#define SR_ENGINE_PHYSICS_CHARACTER_CONTROLLER_H

#include <Physics/PhysicsScene.h>
#include <Physics/PhysicsMaterial.h>

#include <Utils/ECS/Component.h>
#include <Utils/FileSystem/Path.h>

namespace SR_PHYSICS_NS {
    class PhysicsScene;
    class LibraryImpl;
    class CharacterController;

    SR_ENUM_NS_STRUCT_T(CharacterControllerCollisionFlags, uint8_t,
        None = 0,
        Sides = 1 << 0,
        Up = 1 << 1,
        Down = 1 << 2
    )

    class CharacterControllerImpl : public SR_UTILS_NS::NonCopyable {
    protected:
        using Super = SR_UTILS_NS::NonCopyable;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        SR_NODISCARD virtual void* GetHandle() const noexcept = 0;
        virtual void SetHandle(void* handle) = 0;

    public:
        void SetCharacterController(CharacterController* pController) { m_controller = pController; }

        virtual void Synchronize() { }
        virtual bool UpdateMatrix(bool force) { return true; }

        virtual CharacterControllerCollisionFlags Move(const SR_MATH_NS::FVector3& displacement,
            float_t skinWidth,
            float_t deltaTime
        ) { return CharacterControllerCollisionFlags::None; }

    protected:
        CharacterController* m_controller = nullptr;

    };

    struct CharacterControllerConfig : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        /// @property
        SR_MATH_NS::FVector3 offset;
        /// @property
        float_t radius = 0.5f;
        /// @property
        float_t height = 1.8f;
        /// @property
        float_t stepOffset = 0.5f;
        /// @property
        float_t slopeLimit = 45.f;
        /// @property
        float_t contactOffset = 0.1f;
        /// @property
        float_t invisibleWallHeight = 0.0f;
        /// @property
        float_t maxJumpHeight = 0.0f;
    };

    /// @category(Physics)
    class CharacterController : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        ~CharacterController() override;

        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;
        void OnMatrixDirty() override;

        CharacterControllerCollisionFlags Move(const SR_MATH_NS::FVector3& displacement,
            float_t skinWidth,
            float_t deltaTime
        );

        bool InitController();
        void ReleaseController();

        bool UpdateMatrix(bool force);

        void SetMaterial(const SR_UTILS_NS::Path& path);

        SR_NODISCARD SR_PHYSICS_NS::CharacterControllerImpl* GetImpl() const { return m_impl; }
        SR_NODISCARD const SR_PTYPES_NS::PhysicsMaterial::Ptr& GetMaterialData() const { return m_materialData; }
        SR_NODISCARD const CharacterControllerConfig& GetConfig() const { return m_config; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetTranslation() const noexcept { return m_translation; }
        SR_NODISCARD const SR_MATH_NS::Quaternion& GetRotation() const noexcept { return m_rotation; }
        SR_NODISCARD const SR_MATH_NS::FVector3& GetScale() const noexcept { return m_scale; }

    private:
        SR_NODISCARD const PhysicsScenePtr& GetPhysicsScene() const;
        SR_NODISCARD bool IsMatrixDirty() const noexcept { return m_isMatrixDirty; }

        void SetMatrixDirty(bool dirty) noexcept { m_isMatrixDirty = dirty; }

    private:
        /// @property @setter(SetMaterial)
        /// @customArgs(pick: enabled, filter name: Physics material, relative: resources)
        /// @customArg(filter value: sras)
        SR_UTILS_NS::Path m_material;
        /// @property
        CharacterControllerConfig m_config;

    private:
        CharacterControllerImpl* m_impl = nullptr;
        mutable PhysicsScenePtr m_physicsScene;
        SR_PTYPES_NS::PhysicsMaterial::Ptr m_materialData;
        bool m_isMatrixDirty = false;

        /// decomposed matrix
        SR_MATH_NS::FVector3 m_translation;
        SR_MATH_NS::Quaternion m_rotation;
        SR_MATH_NS::FVector3 m_scale = SR_MATH_NS::FVector3::One();

    };
}

#endif //SR_ENGINE_PHYSICS_CHARACTER_CONTROLLER_H
