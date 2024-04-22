//
// Created by innerviewer on 3/4/2023.
//

#ifndef SR_ENGINE_PHYSICSMATERIAL_H
#define SR_ENGINE_PHYSICSMATERIAL_H

#include <Utils/Resources/IResource.h>
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

    struct PhysicsMaterialData {
        float_t dynamicFriction = 0.6f;
        float_t staticFriction = 0.6f;

        float_t bounciness = 0.0f;

        Combine frictionCombine = Combine::Average;
        Combine bounceCombine = Combine::Average;
    };

    class PhysicsMaterial final : public SR_UTILS_NS::IResource {
        using Super = SR_UTILS_NS::IResource;
    private:
        PhysicsMaterial();
        ~PhysicsMaterial() override;

    public:
        static PhysicsMaterial* Load(const SR_UTILS_NS::Path& rawPath);
        static bool Save(const SR_UTILS_NS::Path& path, const PhysicsMaterialData& materialData);

    public:
        SR_NODISCARD Super* CopyResource(Super* destination) const override;

        SR_NODISCARD float_t GetDynamicFriction() const { return m_materialData.dynamicFriction; }
        SR_NODISCARD float_t GetStaticFriction() const { return m_materialData.staticFriction; }
        SR_NODISCARD float_t GetBounciness() const { return m_materialData.bounciness; }
        SR_NODISCARD Combine GetFrictionCombine() const { return m_materialData.frictionCombine; }
        SR_NODISCARD Combine GetBounceCombine() const { return m_materialData.bounceCombine; }
        SR_NODISCARD PhysicsMaterialImpl* GetMaterialImpl(LibraryType libraryType) const;

        void SetDynamicFriction(float_t dynamicFriction) { m_materialData.dynamicFriction = dynamicFriction; }
        void SetStaticFriction(float_t staticFriction) { m_materialData.staticFriction = staticFriction; }
        void SetBounciness(float_t bounciness) { m_materialData.bounciness = bounciness; }
        void SetFrictionCombine(Combine frictionCombine) { m_materialData.frictionCombine = frictionCombine; }
        void SetBounceCombine(Combine bounceCombine) { m_materialData.bounceCombine = bounceCombine; }
        void SetRigidbody(SR_PTYPES_NS::Rigidbody* pRigidbody);

        void RemoveRigidbody(SR_PTYPES_NS::Rigidbody* pRigidbody);
    private:
        bool Load() override;
        bool Unload() override;

    private:
        PhysicsMaterialData m_materialData;

        std::set<SR_PTYPES_NS::Rigidbody*> m_rigidbodies;
        std::map<LibraryType, PhysicsMaterialImpl*> m_implementations;
    };
}
#endif //SR_ENGINE_PHYSICSMATERIAL_H
