//
// Created by Monika on 28.11.2026.
//

#ifndef SR_ENGINE_PHYSICS_GRAVITY_FIELD_H
#define SR_ENGINE_PHYSICS_GRAVITY_FIELD_H

#include <Physics/stdInclude.h>

#include <Utils/ECS/Component.h>

namespace SR_PTYPES_NS {
    SR_ENUM_NS_CLASS_T(GravityFieldShape, uint8_t,
        Spherical,
        Directional
    )

    /// Источник гравитации (планета, луна, зона). Поля складываются, см. GravityField::Sample.
    /// Глобальная гравитация физики на них не влияет: тела, которые должны подчиняться полям, получают GravityBody,
    /// а контроллеры персонажей берут ускорение из Sample сами.
    /// @category(Physics)
    class SR_PHYSICS_DLL_API GravityField : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void OnEnable() override;
        void OnDisable() override;
        void OnDestroy() override;

        /// Ускорение этого поля в мировой точке, м/с^2
        /// @method @evaluate
        SR_NODISCARD SR_MATH_NS::FVector3 GetGravityAt(const SR_MATH_NS::FVector3& position) const;

        /// Сумма ускорений всех активных полей в мировой точке, м/с^2. Только поток сцены
        SR_NODISCARD static SR_MATH_NS::FVector3 Sample(const SR_MATH_NS::FVector3& position);

    private:
        void Register();
        void Unregister();

        SR_NODISCARD static SR_UTILS_NS::Vector<GravityField*>& GetActiveFields();

    private:
        /// @property
        GravityFieldShape m_shape = GravityFieldShape::Spherical;
        /// @property @drag(0.01f) @tooltip(Ускорение на поверхности, м/с^2)
        float_t m_strength = 9.81f;
        /// @property @tooltip(Spherical: радиус поверхности от центра объекта. Ниже него ускорение постоянное)
        float_t m_surfaceRadius = 1000.f;
        /// @property @tooltip(Spherical: степень спада выше поверхности. 2 - закон Ньютона, больше - атмосфера тоньше)
        float_t m_falloffExponent = 2.f;
        /// @property @tooltip(Spherical: дальше этого радиуса поля нет. 0 - без ограничения)
        float_t m_maxRadius = 0.f;
        /// @property @tooltip(Directional: направление в мировых осях)
        SR_MATH_NS::FVector3 m_direction = SR_MATH_NS::FVector3(0.f, -1.f, 0.f);

        bool m_isRegistered = false;

    };

    /// Тело, на которое действуют GravityField вместо глобальной гравитации физики.
    /// Ставится на объект с Rigidbody3D, у тела отключается встроенная гравитация.
    /// @category(Physics)
    class SR_PHYSICS_DLL_API GravityBody : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void FixedUpdate() override;

        /// Ускорение, применённое на последнем шаге, м/с^2
        /// @method @evaluate
        SR_NODISCARD SR_MATH_NS::FVector3 GetGravity() const noexcept { return m_gravity; }

    private:
        /// @property @drag(0.01f)
        float_t m_gravityScale = 1.f;

        /// @property @readOnly @dontSave
        SR_MATH_NS::FVector3 m_gravity;

    };
}

#endif //SR_ENGINE_PHYSICS_GRAVITY_FIELD_H
