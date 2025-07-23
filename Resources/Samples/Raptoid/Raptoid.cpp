//
// Created by Monika on 14.07.2024.
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
    class RaptoidController : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
        /// @property @dontSave @readOnly
        SR_MATH_NS::FVector3 velocity;
        /// @property @dontSave @readOnly
        bool rotateState = false;
        /// @property @dontSave @readOnly
        float_t rotateY = 0.f;

        /// @property
        float_t cameraDistance = 0.6f;
        /// @property
        float_t maxSpeed = 5.5f;
        /// @property
        float_t acceleration = 0.3f;
        /// @property
        float_t deceleration = 5.0f;
        /// @property
        float_t rotateSpeed = 0.05f;
        /// @property
        float_t rotateYLim = 0.f;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> cameraTarget;

        std::optional<SR_UTILS_NS::CursorLock> cursorLock;

        void OnDisable() override {
            cursorLock.reset();
        }

        void MoveControl(SR_ANIMATIONS_NS::AnimationGraph* pGraph) {
            auto&& pRigidbody = gameObject->GetComponent<SR_PTYPES_NS::Rigidbody3D>();
            if (!pRigidbody) {
                return;
            }

            if (SR_UTILS_NS::Input::Instance().GetKey(SR_UTILS_NS::KeyCode::W)) {
                if (velocity.z < maxSpeed) {
                    velocity.z += acceleration;
                }
                pGraph->SetBool("IsRunning", true);
            }
            else {
                if (velocity.z > 0) {
                    velocity.z -= deceleration;
                    if (velocity.z < 0) {
                        velocity.z = 0;
                    }
                }
                pGraph->SetBool("IsRunning", false);
            }

            pRigidbody->SetLinearVelocity(transform->GetQuaternion() * velocity);
        }

        void RotateControl(SR_ANIMATIONS_NS::AnimationGraph* pGraph) {
            if (rotateYLim > 1) {
                rotateYLim /= 1.1f;
            }
            else {
                rotateState = false;
            }

            //if (abs(rotateY) >= 10) {
            //    float_t value = rotateY / 10.f;
            //    rotateY -= value;
            //    transform->Rotate(SR_MATH_NS::FVector3(0.f, value, 0.f));
            //    pGraph->SetBool("IsRunning", true);
            //}

            if (abs(rotateY) > 0) {
                transform->Rotate(SR_MATH_NS::FVector3(0.f, rotateY, 0.f));
                rotateY = 0.f;
                pGraph->SetBool("IsRunning", true);
            }

            SR_MATH_NS::FVector2 drag = SR_UTILS_NS::Input::Instance().GetMouseDrag();
            if (drag.x == 0 || abs(rotateYLim) > 65.f || rotateState) {
                if (abs(rotateYLim) > 65.f) {
                    rotateState = true;
                }
                return;
            }

            rotateY += drag.x * rotateSpeed;
            rotateYLim += abs(drag.x) * rotateSpeed;
        }

        void AnimateCamera() {
            auto&& pCameraGameObject = gameObject->Find("Camera"_atom).StaticCast<SR_UTILS_NS::GameObject>();
            auto&& pCameraSourceGameObject = gameObject->Find("CameraSource"_atom).StaticCast<SR_UTILS_NS::GameObject>();
            auto&& pCameraTargetGameObject = cameraTarget.Get();
            if (!pCameraGameObject || !pCameraTargetGameObject) {
                return;
            }

            SR_MATH_NS::FVector3 position = pCameraSourceGameObject->GetTransform()->GetTranslation();
            position = position.Lerp(pCameraTargetGameObject->GetTransform()->GetTranslation(), cameraDistance);

            pCameraGameObject->GetTransform()->SetTranslation(position);
        }

        void FixedUpdate() override {
            if (!gameObject) {
                return;
            }

            if (!SR_UTILS_NS::Input::Instance().IsPlayMode()) {
                return;
            }

            cursorLock = SR_UTILS_NS::CursorLock(SR_UTILS_NS::CursorLockMode::PlayMode);

            auto&& pAnimator = gameObject->GetComponent<SR_ANIMATIONS_NS::Animator>();

            if (!pAnimator) {
                SR_ERROR("Animator is not set");
                return;
            }

            auto&& pGraph = pAnimator->GetGraph();
            if (!pGraph) {
                SR_ERROR("Graph is not set");
                return;
            }

            pGraph->SetBool("IsThreaten", SR_UTILS_NS::Input::Instance().GetKeyDown(SR_UTILS_NS::KeyCode::F));

            if (!pGraph->IsStateActive("Dummy058|Dummy058|Threaten")) {
                MoveControl(pGraph);
                RotateControl(pGraph);
            }

            AnimateCamera();
        }
    };
}

#include <Codegen/Raptoid.generated.hpp>