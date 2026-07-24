//
// Created by innerviewer on 3/4/2023.
//

#ifndef SR_ENGINE_PHYSICSMATERIAL_H
#define SR_ENGINE_PHYSICSMATERIAL_H

#include <Physics/macros.h>

#include <Utils/Resources/Asset.h>
#include <Utils/Common/Enumerations.h>

#include <Physics/Utils/Utils.h>

namespace SR_PHYSICS_NS {
    SR_ENUM_NS_CLASS_T(Combine, uint8_t,
        Minimum,
        Average,
        Maximum,
        Multiply
    )
}

namespace SR_PTYPES_NS {
    class PhysicsMaterialImpl;
    class Rigidbody;

    class PhysicsMaterial final : public SR_UTILS_NS::Asset {
        SR_CLASS()
        using Super = SR_UTILS_NS::Asset;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<PhysicsMaterial>;

    public:
        PhysicsMaterial();
        ~PhysicsMaterial() override;

    public:
        SR_NODISCARD float_t GetDynamicFriction() const { return m_dynamicFriction; }
        SR_NODISCARD float_t GetStaticFriction() const { return m_staticFriction; }
        SR_NODISCARD float_t GetBounciness() const { return m_bounciness; }
        SR_NODISCARD Combine GetFrictionCombine() const { return m_frictionCombine; }
        SR_NODISCARD Combine GetBounceCombine() const { return m_bounceCombine; }
        SR_NODISCARD PhysicsMaterialImpl* GetMaterialImpl(LibraryType libraryType) const;

        void SetDynamicFriction(float_t dynamicFriction) { m_dynamicFriction = dynamicFriction; }
        void SetStaticFriction(float_t staticFriction) { m_staticFriction = staticFriction; }
        void SetBounciness(float_t bounciness) { m_bounciness = bounciness; }
        void SetFrictionCombine(Combine frictionCombine) { m_frictionCombine = frictionCombine; }
        void SetBounceCombine(Combine bounceCombine) { m_bounceCombine = bounceCombine; }
        void SetRigidbody(SR_PTYPES_NS::Rigidbody* pRigidbody);

        void RemoveRigidbody(SR_PTYPES_NS::Rigidbody* pRigidbody);

    private:
        void ResetMaterialImpls();
        void OnAssetLoaded() override;
        bool Unload() override;

    private:
        /// @property
        float_t m_dynamicFriction = 0.6f;
        /// @property
        float_t m_staticFriction = 0.6f;

        /// @property
        float_t m_bounciness = 0.6f;

        /// @property
        Combine m_frictionCombine = Combine::Average;
        /// @property
        Combine m_bounceCombine = Combine::Average;

        SR_UTILS_NS::Set<SR_PTYPES_NS::Rigidbody*> m_rigidbodies;
        SR_UTILS_NS::Map<LibraryType, PhysicsMaterialImpl*> m_implementations;
    };
}
#endif //SR_ENGINE_PHYSICSMATERIAL_H
