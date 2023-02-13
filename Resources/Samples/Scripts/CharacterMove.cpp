//
// Created by Monika on 12.02.2023.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>
#include <Libraries/Math/Quaternion.h>

#include <Libraries/Debug.h>
#include <Libraries/Rigidbody3D.h>
#include <Libraries/Input.h>
#include <Libraries/Casts.h>

class CharacterMove : public Behaviour {
public:
    void FixedUpdate() override {
        auto&& pRigidbody3D = DynamicCastComponentToRigidbody3D(gameObject->GetComponent("Rigidbody3D"));

        if (!transform || !pRigidbody3D) {
            return;
        }

        FVector3 velocity;
        float_t speed = Input::GetKey(KeyCode::LShift) ? 0.5f * 1.5f : 0.5f;

        if (Input::GetKey(KeyCode::W)) {
            velocity += FVector3(0, 0, speed);
        }

        if (Input::GetKey(KeyCode::S)) {
            velocity -= FVector3(0, 0, speed);
        }

        if (Input::GetKey(KeyCode::A)) {
            velocity -= FVector3(speed, 0, 0);
        }

        if (Input::GetKey(KeyCode::D)) {
            velocity += FVector3(speed, 0, 0);
        }

        if (Input::GetKeyDown(KeyCode::Space)) {
            velocity += FVector3(0, 5, 0);
        }

        auto&& rotate = transform->GetRotation().Radians();
        auto&& q = Quaternion(rotate);

        auto&& drag = Input::GetMouseDrag();
        if (drag.x != 0.f) {
            transform->Rotate(FVector3(0, drag.x / 10, 0));
        }

        pRigidbody3D->AddLinearVelocity(q * velocity);
    }

    void OnCollisionEnter(const CollisionData& data) override {
        isGrounded = true;
    }

    void OnCollisionExit(const CollisionData& data) override {
        isGrounded = false;
    }

private:
    bool isGrounded = false;

};

REGISTER_BEHAVIOUR(CharacterMove)
