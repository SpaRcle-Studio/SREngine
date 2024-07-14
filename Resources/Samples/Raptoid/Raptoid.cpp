//
// Created by Monika on 14.07.2024.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>
#include <Libraries/Math/Quaternion.h>

#include <Libraries/Debug.h>
#include <Libraries/Rigidbody3D.h>
#include <Libraries/Animator.h>
#include <Libraries/Component.h>
#include <Libraries/Rigidbody.h>
#include <Libraries/Raycast.h>
#include <Libraries/Input.h>
#include <Libraries/Casts.h>

class Raptoid : public Behaviour {
public:
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

        pGraph->SetBool("IsRunning", Input::GetKey(KeyCode::W));
    }
};

REGISTER_BEHAVIOUR(Raptoid)
