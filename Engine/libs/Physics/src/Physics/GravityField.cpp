//
// Created by Monika on 28.11.2026.
//

#include <Physics/GravityField.h>
#include <Physics/3D/Rigidbody3D.h>

#include <Utils/ECS/Transform.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/Types/Time.h>

#include <Codegen/GravityField.generated.hpp>

namespace SR_PTYPES_NS {
    SR_UTILS_NS::Vector<GravityField*>& GravityField::GetActiveFields() {
        static SR_UTILS_NS::Vector<GravityField*> fields;
        return fields;
    }

    void GravityField::OnEnable() {
        Super::OnEnable();
        Register();
    }

    void GravityField::OnDisable() {
        Unregister();
        Super::OnDisable();
    }

    void GravityField::OnDestroy() {
        Unregister();
        Super::OnDestroy();
    }

    void GravityField::Register() {
        if (m_isRegistered) {
            return;
        }
        GetActiveFields().emplace_back(this);
        m_isRegistered = true;
    }

    void GravityField::Unregister() {
        if (!m_isRegistered) {
            return;
        }
        GetActiveFields().erase_if([this](GravityField* pField) {
            return pField == this;
        });
        m_isRegistered = false;
    }

    SR_MATH_NS::FVector3 GravityField::GetGravityAt(const SR_MATH_NS::FVector3& position) const {
        if (m_shape == GravityFieldShape::Directional) {
            const float_t length = m_direction.Length();
            if (length < 1e-6f) {
                return SR_MATH_NS::FVector3(0.f);
            }
            return m_direction * (m_strength / length);
        }

        auto&& pTransform = GetTransform();
        if (!pTransform) {
            return SR_MATH_NS::FVector3(0.f);
        }

        const SR_MATH_NS::FVector3 toCenter = pTransform->GetGlobalTranslation() - position;
        const float_t distance = toCenter.Length();
        if (distance < 1e-3f) {
            return SR_MATH_NS::FVector3(0.f);
        }

        if (m_maxRadius > 0.f && distance > m_maxRadius) {
            return SR_MATH_NS::FVector3(0.f);
        }

        /// Ниже поверхности ускорение не растёт: в пещерах и под землёй ходить так же, как наверху
        float_t acceleration = m_strength;
        if (m_surfaceRadius > 0.f && distance > m_surfaceRadius) {
            acceleration *= std::pow(m_surfaceRadius / distance, m_falloffExponent);
        }

        return toCenter * (acceleration / distance);
    }

    SR_MATH_NS::FVector3 GravityField::Sample(const SR_MATH_NS::FVector3& position) {
        SR_MATH_NS::FVector3 gravity(0.f);
        for (auto&& pField : GetActiveFields()) {
            gravity += pField->GetGravityAt(position);
        }
        return gravity;
    }

    void GravityBody::FixedUpdate() {
        Super::FixedUpdate();

        auto&& pTransform = GetTransform();
        auto&& pSceneObject = GetSceneObject();
        if (!pTransform || !pSceneObject) {
            return;
        }

        m_gravity = GravityField::Sample(pTransform->GetGlobalTranslation()) * m_gravityScale;

        auto&& pRigidbody = pSceneObject->GetComponent<Rigidbody3D>();
        if (!pRigidbody || pRigidbody->IsStatic()) {
            return;
        }

        /// Встроенная гравитация физики направлена по -Y и с полями несовместима
        if (pRigidbody->IsUseGravity()) {
            pRigidbody->SetUseGravity(false);
        }

        /// Скорость, а не сила: не зависит от массы и от того, как реализация копит силы между шагами
        pRigidbody->AddLinearVelocity(m_gravity * SR_HTYPES_NS::Time::Instance().FixedDeltaTime());
    }
}
