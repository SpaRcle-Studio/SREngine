//
// Created by Monika on 14.07.2024.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>
#include <Libraries/Math/Quaternion.h>

#include <Libraries/Debug.h>
#include <Libraries/Rigidbody3D.h>
#include <Libraries/Animator.h>
#include <Libraries/Transform.h>
#include <Libraries/GameObject.h>
#include <Libraries/Component.h>
#include <Libraries/Rigidbody.h>
#include <Libraries/Raycast.h>
#include <Libraries/Input.h>
#include <Libraries/Casts.h>

class Raptoid : public Behaviour {
public:
    FVector3 velocity;
    float_t maxSpeed = 5.5f;
    float_t acceleration = 0.3f;
    float_t deceleration = 5.0f;
    float_t rotateSpeed = 0.05f;
    GameObjectPtr cameraTarget;
    GameObjectPtr camera;
    float_t rotateY = 0.f;
    float_t rotateYLim = 0.f;
    bool rotateState = false;

    GameObjectPtr GetCameraTarget() {
        if (!cameraTarget) {
            cameraTarget = gameObject
                ->Find("Dummy058_$AssimpFbx$_PreRotation")
                ->Find("Dummy058_$AssimpFbx$_Rotation")
                ->Find("Dummy058")
                ->Find("Bip001");
        }
        return cameraTarget;
    }

    void MoveControl(AnimationGraph* pGraph) {
        auto&& pParent = gameObject->GetParent();
        if (!pParent) {
            return;
        }

        auto&& pRigidbody = DynamicCastComponentToRigidbody3D(pParent->GetComponent("Rigidbody3D"));
        if (!pRigidbody) {
            return;
        }

        if (Input::GetKey(KeyCode::W)) {
            if (velocity.z < maxSpeed) {
                velocity.z += acceleration;
            }
            pGraph->SetBool("IsRunning", true);
        } else {
            if (velocity.z > 0) {
                velocity.z -= deceleration;
                if (velocity.z < 0) {
                    velocity.z = 0;
                }
            }
            pGraph->SetBool("IsRunning", false);
        }

        pRigidbody->SetLinearVelocity(pParent->GetTransform()->GetQuaternion() * velocity);
    }

    void RotateControl(AnimationGraph* pGraph) {
        auto&& pParent = gameObject->GetParent();
        if (!pParent) {
            return;
        }

        if (rotateYLim > 1) {
            rotateYLim /= 1.1f;
        }
        else {
            rotateState = false;
        }

        if (abs(rotateY) >= 10) {
            float_t value = rotateY / 10.f;
            rotateY -= value;
            pParent->GetTransform()->Rotate(FVector3(0.f, value, 0.f));
            pGraph->SetBool("IsRunning", true);
        }

        FVector2 drag = Input::GetMouseDrag();
        if (drag.x == 0 || abs(rotateYLim > 65.f) || rotateState) {
            if (abs(rotateYLim > 65.f)) {
                rotateState = true;
            }
            return;
        }

        rotateY += drag.x * rotateSpeed;
        rotateYLim += abs(drag.x) * rotateSpeed;

       ///if (rotateState && abs(rotateY) < 1.f) {
       ///    rotateState = false;
       ///}

       ///if (abs(rotateYLim) >= 40.f || rotateState) {
       ///    rotateState = true;
       ///    float_t value = rotateY / 10.f;
       ///    rotateY -= value;
       ///    rotateYLim /= 5.f;
       ///    pParent->GetTransform()->Rotate(FVector3(0.f, value, 0.f));
       ///    pGraph->SetBool("IsRunning", true);
       ///}

       ///FVector2 drag = Input::GetMouseDrag();
       ///if (drag.x == 0 || (rotateState && abs(rotateYLim > 15.f))) {
       ///    return;
       ///}
       ///rotateY += drag.x * rotateSpeed;
       ///rotateYLim += abs(drag.x * rotateSpeed);
    }

    void AnimateCamera() {
        auto&& pCameraGameObject = gameObject->Find("Camera");
        auto&& pCameraSourceGameObject = gameObject->Find("CameraSource");
        auto&& pCameraTargetGameObject = GetCameraTarget();
        if (!pCameraGameObject || !pCameraTargetGameObject) {
            return;
        }

        FVector3 postion = pCameraSourceGameObject->GetTransform()->GetTranslation();
        postion = postion.Lerp(pCameraTargetGameObject->GetTransform()->GetTranslation(), 0.6f);

        pCameraGameObject->GetTransform()->SetTranslation(postion);
    }

    void FixedUpdate() override {
        if (!gameObject) {
            return;
        }

        auto&& pAnimator = DynamicCastComponentToAnimator(gameObject->GetComponent("Animator"));

        if (!pAnimator) {
            Debug::Error("Animator is not set");
            return;
        }

        auto&& pGraph = pAnimator->GetGraph();
        if (!pGraph) {
            Debug::Error("Graph is not set");
            return;
        }

        pGraph->SetBool("IsThreaten", Input::GetKey(KeyCode::F));

        if (!pGraph->IsStateActive("Dummy058|Dummy058|Threaten")) {
            MoveControl(pGraph);
            RotateControl(pGraph);
        }

        AnimateCamera();
    }
};

REGISTER_BEHAVIOUR(Raptoid)
