//
// Created by Monika on 24.05.2022.
//

#ifndef SRENGINE_CHARACTER_CONTROLLER_H
#define SRENGINE_CHARACTER_CONTROLLER_H

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>

#include <Libraries/Debug.h>
#include <Libraries/Input.h>

class CharacterController : public Behaviour {
public:
    void FixedUpdate() override {
        if (!transform) {
            return;
        }

        float_t _speed = Input::GetKey(KeyCode::LShift) ? speed * 5.0f : speed;

        if (Input::GetKey(KeyCode::W)) {
            velocity += FVector3(0, 0, (_speed / 250.f));
        }

        if (Input::GetKey(KeyCode::S)) {
            velocity -= FVector3(0, 0, (_speed / 250.f));
        }

        if (Input::GetKey(KeyCode::A)) {
            velocity -= FVector3((_speed / 250.f), 0, 0);
        }

        if (Input::GetKey(KeyCode::D)) {
            velocity += FVector3((_speed / 250.f), 0, 0);
        }

        if (Input::GetMouse(MouseCode::MouseRight)) {
            auto&& drag = Input::GetMouseDrag();

            drag *= (rotateSpeed / 25.f);

            transform->GlobalRotate(FVector3(drag.y, drag.x, 0.f));
        }

        transform->Translate(velocity);

        velocity = velocity / 1.025f;
    }

private:
    FVector3 velocity;

    SR_PROPERTY(speed)
    float_t speed = 1.f;

    SR_PROPERTY(rotateSpeed)
    float_t rotateSpeed = 1.f;

};

#endif //SRENGINE_CHARACTER_CONTROLLER_H
