//
// Created by Monika on 12.02.2023.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>
#include <Libraries/Math/Quaternion.h>

#include <Libraries/Debug.h>
#include <Libraries/Rigidbody3D.h>
#include <Libraries/Component.h>
#include <Libraries/Rigidbody.h>
#include <Libraries/Raycast.h>
#include <Libraries/Input.h>
#include <Libraries/Casts.h>

class CharacterMove : public Behaviour {
public:
    void Awake() override {
        Input::LockCursor(true);
    }

    void Close() override {
        Input::LockCursor(false);
    }

    void FixedUpdate() override {
        auto&& pRigidbody3D = DynamicCastComponentToRigidbody3D(gameObject->GetComponent("Rigidbody3D"));

        if (!transform || !pRigidbody3D) {
            return;
        }

        FVector3 velocity;
        float_t speed = Input::GetKey(KeyCode::LShift) ? 0.5f * 1.5f : 0.5f;

        bool isMove = false;

        if (Input::GetKey(KeyCode::W)) {
            velocity += FVector3(0, 0, speed);
            isMove = true;
        }

        if (Input::GetKey(KeyCode::S)) {
            velocity -= FVector3(0, 0, speed);
            isMove = true;
        }

        if (Input::GetKey(KeyCode::A)) {
            velocity -= FVector3(speed, 0, 0);
            isMove = true;
        }

        if (Input::GetKey(KeyCode::D)) {
            velocity += FVector3(speed, 0, 0);
            isMove = true;
        }

        if (Input::GetMouseDown(MouseCode::MouseLeft)){
            auto&& rotate = transform->GetRotation().Radians();
            auto&& q = Quaternion(rotate);

            if (std::vector<RaycastHit> hits = Raycast3D::Cast(transform->GetTranslation(), (q * FVector3(0, 0, 1)), 100, 5); !hits.empty()) {
                for (int i = 0; i < hits.size(); i++){
                    std::cout << "Ray (" << i + 1 << ") hits something. Distance = "  << hits[i].distance << "\t Total hits = " << hits.size() << std::endl;
                }
            }
        }

        if (isGrounded && Input::GetKeyDown(KeyCode::Space)) {
            velocity += FVector3(0, 15, 0);
            isMove = true;
        }

        auto&& drag = Input::GetMouseDrag();
        if (drag.x != 0.f) {
            transform->Rotate(FVector3(0, drag.x / 10, 0));
        }

        if (isMove) {
            auto&& rotate = transform->GetRotation().Radians();
            auto&& q = Quaternion(rotate);
            pRigidbody3D->AddLinearVelocity(q * velocity);
        }
        else if (isGrounded) {
            pRigidbody3D->SetLinearVelocity(pRigidbody3D->GetLinearVelocity() * 0.9);
        }
    }

    void OnCollisionEnter(const CollisionData& data) override {
        auto&& pComponent = DynamicCastRigidbodyToComponent((Rigidbody*)data.pHandler);
        auto&& pParent = pComponent->GetGameObject();
        if (pParent->GetName() == "Ground") {
            isGrounded++;
        }
    }

    void OnCollisionExit(const CollisionData& data) override {
        auto&& pComponent = DynamicCastRigidbodyToComponent((Rigidbody*)data.pHandler);
        auto&& pParent = pComponent->GetGameObject();
        if (pParent->GetName() == "Ground") {
            isGrounded--;
        }
    }

private:
    int isGrounded = 0;

};

REGISTER_BEHAVIOUR(CharacterMove)
