//
// Created by innerviewer on 3/4/2023.
//

#ifndef SRENGINE_PHYSICSMATERIAL_H
#define SRENGINE_PHYSICSMATERIAL_H

#include <Utils/ResourceManager/IResource.h>
#include <Utils/Common/Enumerations.h>

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

    class PhysicsMaterial final : public SR_UTILS_NS::IResource {
        using Super = SR_UTILS_NS::IResource;
    private:
        PhysicsMaterial();
        ~PhysicsMaterial() override;

    public:
        static PhysicsMaterial* Load(SR_UTILS_NS::Path rawPath);

    public:
        SR_NODISCARD Super* CopyResource(Super* destination) const override;

        SR_NODISCARD float_t GetDynamicFriction() const { return m_dynamicFriction; }
        SR_NODISCARD float_t GetStaticFriction() const { return m_staticFriction; }
        SR_NODISCARD float_t GetBounciness() const { return m_bounciness; }
        SR_NODISCARD Combine GetFrictionCombine() const { return m_frictionCombine; }
        SR_NODISCARD Combine GetBounceCombine() const { return m_bounceCombine; }

        void SetDynamicFriction(float_t dynamicFriction) { m_dynamicFriction = dynamicFriction; }
        void SetStaticFriction(float_t staticFriction) { m_staticFriction = staticFriction; }
        void SetBounciness(float_t bounciness) { m_bounciness = bounciness; }
        void SetFrictionCombine(Combine frictionCombine) { m_frictionCombine = frictionCombine; }
        void SetBounceCombine(Combine bounceCombine) { m_bounceCombine = bounceCombine; }

    private:
        bool Load() override;
        bool Unload() override;

    private:
        float_t m_dynamicFriction = 0.6f;
        float_t m_staticFriction = 0.6f;
        float_t m_bounciness = 0.0f;

        std::map<LibraryType, PhysicsMaterialImpl*> m_implementations;

        Combine m_frictionCombine = Combine::Average;
        Combine m_bounceCombine = Combine::Average;
    };
}
#endif //SRENGINE_PHYSICSMATERIAL_H
