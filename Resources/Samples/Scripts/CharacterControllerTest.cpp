// 
// Created by innerviewer on 2025-05-11.
//

#include <Utils/Input/InputSystem.h>
#include <Utils/Input/KeyCodes.h>

#include <Utils/Math/Vector2.h>


#include <Scripting/Cpp/CppBehaviour.h>

namespace SpaRcle::Scripts::SREngine {
    class CharacterController : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
        SR_NODISCARD bool ExecuteInEditMode() const noexcept override { return false; }

    public:
        void Start() override { }

        void Update(float_t dt) override {
            if (!transform) {
                return;
            }

            float_t _speed = SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::LShift) ? speed * 5.0f : speed;

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::W)) {
                velocity += SR_MATH_NS::FVector3(0, 0, (_speed / 250.f));
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::S)) {
                velocity -= SR_MATH_NS::FVector3(0, 0, (_speed / 250.f));
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::A)) {
                velocity -= SR_MATH_NS::FVector3((_speed / 250.f), 0, 0);
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::D)) {
                velocity += SR_MATH_NS::FVector3((_speed / 250.f), 0, 0);
            }

            if (SR_UTILS_NS::Input::Instance().GetMouse(SR_UTILS_NS::MouseCode::MouseRight)) {
                auto&& drag = SR_UTILS_NS::Input::Instance().GetMouseDrag();

                drag *= (rotateSpeed / 25.f);

                transform->GlobalRotate(SR_MATH_NS::FVector3(drag.y, drag.x, 0.f));
            }

            transform->Translate(velocity);

            velocity = velocity / 1.025f;
        }

    private:
        SR_MATH_NS::FVector3 velocity;

        /// @property
        float_t speed = 1.f;

        /// @property
        float_t rotateSpeed = 1.f;
    };
}

#include <Codegen/CharacterControllerTest.generated.hpp>
