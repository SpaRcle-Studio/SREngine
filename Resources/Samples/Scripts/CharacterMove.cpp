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
    void FixedUpdate() override {
        if (!gameObject) {
            return;
        }

        auto&& pRigidbody3D = DynamicCastComponentToRigidbody3D(gameObject->GetComponent("Rigidbody3D"));

        if (!transform || !pRigidbody3D) {
            return;
        }

        velocity = pRigidbody3D->GetLinearVelocity();
        velocity = FVector3(velocity.x * 0.8, velocity.y, velocity.z * 0.8);

        auto&& q = Quaternion(transform->GetRotation().Radians());
        float_t speed = Input::GetKey(KeyCode::LShift) ? 2.5f : 1.5f;

        if (Input::GetKey(KeyCode::W)) {
            velocity += q * FVector3(0, 0, speed);
        }

        if (Input::GetKey(KeyCode::S)) {
            velocity -= q * FVector3(0, 0, speed);
        }

        if (Input::GetKey(KeyCode::A)) {
            velocity -= q * FVector3(speed, 0, 0);
        }

        if (Input::GetKey(KeyCode::D)) {
            velocity += q * FVector3(speed, 0, 0);
        }

        velocity = velocity.Clamp(25.f, -25.f);

        pRigidbody3D->SetLinearVelocity(velocity);

        RaycastHit hit;

        if (Input::GetMouseDown(MouseCode::MouseLeft)) {
            auto&& rotate = transform->GetRotation().Radians();
            auto&& q = Quaternion(rotate);

            if (std::vector<RaycastHit> hits = Raycast3D::Cast(transform->GetTranslation(), (q * FVector3(0, 0, 1)), 100, 5); !hits.empty()) {
                /*for (int i = 0; i < hits.size(); i++){
                    std::cout << "Ray (" << i + 1 << ") hits something. Distance = "  << hits[i].distance << "\t Total hits = " << hits.size() << std::endl;
                }*/
                hit = hits[0];
                std::cout << "Ray hits something. Distance = "  << hit.distance << std::endl;
            }
        }

        if (isGrounded && Input::GetKeyDown(KeyCode::Space)) {
            pRigidbody3D->AddLinearVelocity(FVector3(0, 5, 0));
        }

        auto&& drag = Input::GetMouseDrag();
        if (drag.x != 0.f) {
            transform->Rotate(FVector3(0, drag.x / 10, 0));
        }

/*        if (auto&& pRigidbody = (Rigidbody*)hit.pHandler) {
            if (auto&& pGameObject = pRigidbody->GetGameObject()) {
                std::cout << "HIT on GameObject: '" << pGameObject->GetName() << "'\n";
            }
        }*/
    }

    void OnCollisionEnter(const CollisionData& data) override {
        auto&& pComponent = DynamicCastRigidbodyToComponent((Rigidbody*)data.pHandler);
        auto&& pParent = pComponent->GetGameObject();
        if (pParent->GetTagString() == "Ground") {
            isGrounded++;
        }
    }

    void OnCollisionExit(const CollisionData& data) override {
        auto&& pComponent = DynamicCastRigidbodyToComponent((Rigidbody*)data.pHandler);
        auto&& pParent = pComponent->GetGameObject();
        if (pParent->GetTagString() == "Ground") {
            isGrounded--;
        }
    }

private:
    int isGrounded = 0;
    FVector3 velocity;

};

REGISTER_BEHAVIOUR(CharacterMove)
