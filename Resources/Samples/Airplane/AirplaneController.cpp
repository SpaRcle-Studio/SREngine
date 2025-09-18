//
// Created by Monika on 16.09.2025.
//

#include <Utils/Input/InputSystem.h>
#include <Utils/Input/KeyCodes.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Noise.h>
#include <Utils/Math/VectorRanges.h>
#include <Utils/ECS/EntityRef.h>

#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/Animations/Animator.h>

#include <Physics/3D/Rigidbody3D.h>

#include <Scripting/Cpp/CppBehaviour.h>

namespace SpaRcle::Scripts::Samples {
    namespace Atmosphere {
        constexpr float SeaLevelDensity = 1.225f;     // кг/м^3
        constexpr float SeaLevelTemp = 288.15f;       // K (15 °C)
        constexpr float LapseRate = -0.0065f;         // K/м
        constexpr float GasConstant = 287.05f;        // Дж/(кг·K)
        constexpr float Gravity = 9.80665f;           // м/с^2
        constexpr float Pressure0 = 101325.0f;        // Па

        inline float GetDensity(float altitudeMeters) {
            float T = SeaLevelTemp + LapseRate * altitudeMeters; // температура
            float P = Pressure0 * powf(T / SeaLevelTemp, -Gravity / (LapseRate * GasConstant));
            return P / (GasConstant * T);
        }
    }

    struct AirplaneParams : SR_UTILS_NS::Serializable {
        SR_STRUCT()

        /// @property
        float wingArea = 25.0f;
        /// @property
        float airDensity = 1.225f;
        /// @property
        float maxLiftCoeff = 1.2f;
        /// @property
        float stallAngle = SR_RAD(15.0f);
        /// @property
        float dragCoeff = 0.03f;

        // Двигатель
        /// @property
        float maxThrust = 2100.0f;    // Ньютон (реактивный)
        /// @property
        float maxPower = 160000.0f;   // Вт (винтовой) ~ 215 л.с.
        /// @property
        float propEfficiency = 0.8f;  // КПД винта
    };

    class AirplaneController : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
        /// @property
        float_t acceleration = 0.1f;
        /// @property
        float_t deceleration = 0.1f;
        /// @property
        float_t turnAcceleration = 1.0f;
        /// @property
        float_t turnDeceleration = 0.5f;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> centerMassRef;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> leftWingRef;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> rightWingRef;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> tailRef;
        /// @property
        AirplaneParams params;

        /// @property
        float maxThrust = 200.f;
        /// @property
        float throttleIncrement = 0.1f;
        /// @property
        float responsiveness = 10.0f;
        /// @property
        float liftCoefficient = 0.15f;      // подъемная сила
        /// @property
        float dragCoefficient = 0.02f;      // сопротивление воздуха

        float yaw = 0.f;
        float pitch = 0.f;
        float roll = 0.f;
        float throttle = 0.0f;   // 0..1
        float throttleStep = 0.01f; // скорость изменения

        float AoA(const SR_MATH_NS::FVector3& vel, const SR_MATH_NS::FVector3& forward) {
            auto vNorm = vel.Normalized();
            auto fNorm = forward.Normalized();
            return acosf(vNorm.Dot(fNorm)); // в радианах
        }

        static float ComputeLiftCoeff(float aoa, float maxCl, float stallAngle) {
            float absA = fabsf(aoa);
            if (absA <= stallAngle) {
                // линейная аппроксимация через ноль
                return maxCl * (absA / stallAngle) * (aoa >= 0.0f ? 1.0f : -1.0f);
            }
            // упрощённый спад после срыва
            float over = (absA - stallAngle) / stallAngle;
            float val = maxCl * (1.0f - 0.8f * SR_CLAMP(over, 0.0f, 1.0f)); // 80% падение в примере
            return (aoa >= 0.0f) ? val : -val;
        }

        SR_MATH_NS::FVector3 ComputeDrag(const SR_MATH_NS::FVector3& velocity) {
            float vMag = velocity.Length();
            if (vMag < 1e-4f) return SR_MATH_NS::FVector3(0.f,0.f,0.f);
            float dragMag = params.dragCoeff * 0.5f * params.airDensity * vMag * vMag * params.wingArea;
            return -velocity.Normalized() * dragMag;
        }

        float ComputeThrustJet(float throttle, float altitude) {
            float rho = Atmosphere::GetDensity(altitude);
            return throttle * params.maxThrust * (rho / Atmosphere::SeaLevelDensity);
        }

        float ComputeThrustProp(float throttle, float speed, float altitude) {
            float rho = Atmosphere::GetDensity(altitude);
            float power = throttle * params.maxPower * (rho / Atmosphere::SeaLevelDensity);

            // тяга = мощность * КПД / скорость
            if (speed < 1.0f) speed = 1.0f; // защита от деления на ноль
            return (power * params.propEfficiency) / speed;
        }

        SR_MATH_NS::FVector3 ComputeLift(const SR_MATH_NS::FVector3& velocity, const SR_MATH_NS::FVector3& wingRight, const SR_MATH_NS::FVector3& forward)
        {
            float vMag = velocity.Length();
            if (vMag < 1e-4f) return SR_MATH_NS::FVector3(0.f,0.f,0.f);

            // относительный ветер (откуда «дует» поток) — направление потока воздуха относительно самолёта
            SR_MATH_NS::FVector3 relWind = (-velocity).Normalized();

            // убираем spanwise компонент (компонент вдоль wingRight) — проецируем в плоскость продольной симметрии
            float spanComp = SR_MATH_NS::Dot(relWind, wingRight);
            SR_MATH_NS::FVector3 relOnPlane = relWind - wingRight * spanComp;
            float lenPlane = relOnPlane.Length();
            if (lenPlane < 1e-5f) return SR_MATH_NS::FVector3(0.f,0.f,0.f);
            relOnPlane = relOnPlane / lenPlane; // нормализуем

            // угол атаки: угол между forward и relOnPlane (в радианах)
            float fwdDot = SR_CLAMP(SR_MATH_NS::Dot(forward.Normalized(), relOnPlane), -1.0f, 1.0f);
            float aoa = acosf(fwdDot);

            // знак AoA (положительный если relOnPlane имеет компонент вниз/вверх относительно крыла)
            // вычисляем up через cross: up = forward × right (стандартное правое правило для прямоугольной базы)
            SR_MATH_NS::FVector3 up = SR_MATH_NS::Cross(forward, wingRight).Normalized();
            float sign = (SR_MATH_NS::Dot(relOnPlane, up) >= 0.0f) ? 1.0f : -1.0f;
            aoa *= sign; // signed AoA

            // коэффициент подъёма
            float Cl = ComputeLiftCoeff(aoa, params.maxLiftCoeff, params.stallAngle);

            // сама величина подъёма
            float liftMag = Cl * 0.5f * params.airDensity * vMag * vMag * params.wingArea;

            // направление подъёма: relWind × wingRight  (relative wind × span -> "вверх")
            SR_MATH_NS::FVector3 liftDir = SR_MATH_NS::Cross(relWind, wingRight);
            float llen = liftDir.Length();
            if (llen < 1e-5f) return SR_MATH_NS::FVector3(0.f,0.f,0.f);
            liftDir = liftDir / llen;

            return liftDir * liftMag;
        }

        std::optional<SR_UTILS_NS::CursorLock> cursorLock;

        void OnDisable() override {
            cursorLock.reset();
        }

        /// Y = S × V / p, где Y — это подъёмная сила, S — площадь крыла, V — скорость полёта, а p — плотность воздуха.

        void MoveControlSimple() {
            auto&& pRigidbody = gameObject->GetComponent<SR_PTYPES_NS::Rigidbody3D>();
            if (!pRigidbody) {
                return;
            }

            auto velocity = pRigidbody->GetLinearVelocity();
            auto forward  = transform->Forward(); // у тебя это +Z
            auto up       = transform->Up();      // у тебя это +Y
            float altitude = pRigidbody->GetTranslation().y;

            // атмосфера
            float rho = Atmosphere::GetDensity(altitude);

            // гравитация (если у тебя не считается автоматически)
            float mass = pRigidbody->GetMass();
            pRigidbody->AddForce(SR_MATH_NS::FVector3(0.0f, -9.81f * mass, 0.0f));

            // тяга
            float thrustPower = 0.0f;
            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Space)) {
                thrustPower = 5000.0f; // макс тяга двигателя
            }
            pRigidbody->AddForce(forward * thrustPower);

            // подъемная сила
            float liftCoef = 2.0f;
            SR_MATH_NS::FVector3 lift = up * velocity.LengthSqr() * liftCoef * rho;
            if (lift.Length() > 10000.0f)  // ограничение
                lift = lift.Normalized() * 10000.0f;
            pRigidbody->AddForce(lift);

            // сопротивление
            float dragCoef = 0.01f;
            SR_MATH_NS::FVector3 drag = -velocity.Normalized() * velocity.LengthSqr() * dragCoef * rho;
            pRigidbody->AddForce(drag);
        }

        void MoveControl() {
            auto&& pRigidbody = gameObject->GetComponent<SR_PTYPES_NS::Rigidbody3D>();
            if (!pRigidbody) {
                return;
            }

            SR_MATH_NS::FVector3 velocity = pRigidbody->GetLinearVelocity();
            SR_MATH_NS::FVector3 right    = transform->Right();
            SR_MATH_NS::FVector3 forward = transform->Forward();

            SR_MATH_NS::FVector3 lift = ComputeLift(velocity, right, forward);
            SR_MATH_NS::FVector3 drag = ComputeDrag(velocity);

            float altitude = pRigidbody->GetTranslation().y;

            // атмосферные параметры
            float rho = Atmosphere::GetDensity(altitude);
            params.airDensity = rho;

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::W)) {
                throttle = std::min(1.0f, throttle + throttleStep);
            }
            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::S)) {
                throttle = std::max(0.0f, throttle - throttleStep);
            }

            // тяга
            float currentThrust = 0.0f;
            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Space)) {
                // реактивный вариант
                currentThrust = ComputeThrustJet(throttle, altitude);
                // или винтовой
                //currentThrust = ComputeThrustProp(throttle, speed, altitude);
            }

            SR_MATH_NS::FVector3 thrust = forward * currentThrust;

            // Силы от тяги и сопротивления всегда в центр масс
            pRigidbody->AddForce(thrust);
            pRigidbody->AddForce(drag);

            // Центр масс
            const auto com = centerMassRef.Get()->GetTransform()->GetMatrix().GetTranslate();
            // Позиции крыльев
            const auto leftWingPos = leftWingRef.Get()->GetTransform()->GetMatrix().GetTranslate();
            const auto rightWingPos = rightWingRef.Get()->GetTransform()->GetMatrix().GetTranslate();

            const auto tailPos = tailRef.Get()->GetTransform()->GetMatrix().GetTranslate();

            // стабилизирующая сила хвоста
            float pitchRate = pRigidbody->GetAngularVelocity().x; // скорость вращения по тангажу
            SR_MATH_NS::FVector3 tailForce = -transform->Up() * (pitchRate * 50.0f); // сила вниз пропорциональна угловой скорости

            pRigidbody->AddForce(tailForce);
            pRigidbody->AddTorque((tailPos - com).Cross(tailForce));

            // Подъём на крыльях — пока одинаковый, потом можно добавить разницу для элеронов
            SR_MATH_NS::FVector3 liftLeft  = ComputeLift(velocity, right, forward) * 0.5f;
            SR_MATH_NS::FVector3 liftRight = ComputeLift(velocity, right, forward) * 0.5f;

            // Левое крыло
            {
                pRigidbody->AddForce(liftLeft);
                pRigidbody->AddTorque((leftWingPos - com).Cross(liftLeft));
            }

            // Правое крыло
            {
                pRigidbody->AddForce(liftRight);
                pRigidbody->AddTorque((rightWingPos - com).Cross(liftRight));
            }

            /*velocity = pRigidbody->GetLinearVelocity();
            angle = pRigidbody->GetAngularVelocity();
            angle -= angle * (turnDeceleration / 100.0);

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::A)) {
                angle += transform->GetQuaternion() * SR_MATH_NS::FVector3(0.f, 0.f, turnAcceleration / 100.0);
            }
            else if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::D)) {
                angle -= transform->GetQuaternion() * SR_MATH_NS::FVector3(0.f, 0.f, turnAcceleration / 100.0);
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::W)) {
                angle += transform->GetQuaternion() * SR_MATH_NS::FVector3(turnAcceleration / 100.0, 0.f, 0.f);
            }
            else if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::S)) {
                angle -= transform->GetQuaternion() * SR_MATH_NS::FVector3(turnAcceleration / 100.0, 0.f, 0.f);
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Space)) {
                velocity += transform->GetQuaternion() * SR_MATH_NS::FVector3(0.f, 0.f, acceleration);
            }

            pRigidbody->SetLinearVelocity(velocity);
            pRigidbody->SetAngularVelocity(angle);*/


        }

        void MoveControlArcade() {
            if (SR_UTILS_NS::Input::Instance().IsPlayMode()) {
                if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::Space)) {
                    throttle += throttleIncrement;
                }
                else if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::LShift)) {
                    throttle -= throttleIncrement;
                }

                const auto drag = SR_UTILS_NS::Input::Instance().GetMouseDrag();
                yaw = drag.x;
                pitch = -drag.y;

                if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::A)) {
                    roll = 10.0f;
                }
                else if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::D)) {
                    roll = -10.0f;
                }
                else {
                    roll = 0.0f;
                }
            }

            throttle = SR_CLAMP(throttle, 0.0f, 100.0f);

            auto&& pRigidbody = gameObject->GetComponent<SR_PTYPES_NS::Rigidbody3D>();
            if (!pRigidbody) {
                return;
            }

            //pRigidbody->SetLinearVelocity(pRigidbody->GetLinearVelocity().Clamp(-50, 50));

            // Скорость и направление
            //auto velocity = pRigidbody->GetLinearVelocity();
            //float speed = velocity.Length();
            SR_MATH_NS::FVector3 forward = transform->Forward();
            //SR_MATH_NS::FVector3 right = transform->Right();
            //SR_MATH_NS::FVector3 up = transform->Up();

            //const float mass = pRigidbody->GetMass();
            //const float responsivenessFactor = (mass / 10.f) * responsiveness;

// направление немного вперед + вверх для стабильности
            //SR_MATH_NS::FVector3 liftDir = (up * 0.8f + forward * 0.2f).Normalized();
            //float liftStrength = liftCoefficient * speed * speed; // пропорционально квадрату скорости
            //pRigidbody->AddForce(liftDir * liftStrength);
            // --- Сопротивление ---
            //float dragStrength = dragCoefficient * speed * speed;
            //pRigidbody->AddForce(-velocityDir * dragStrength);


            pRigidbody->AddForce(forward * maxThrust * throttle);
            //pRigidbody->AddTorque(transform->Up() * yaw * responsivenessFactor);
            //pRigidbody->AddTorque(transform->Right() * pitch * responsivenessFactor);
            //pRigidbody->AddTorque(transform->Forward() * roll * responsivenessFactor);
        }

        void FixedUpdate() override {
            if (!gameObject) {
                return;
            }

            cursorLock = SR_UTILS_NS::CursorLock(SR_UTILS_NS::CursorLockMode::PlayMode);

            MoveControlArcade();
        }
    };
}

#include <Codegen/AirplaneController.generated.hpp>