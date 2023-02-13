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

class CameraUpDownMove : public Behaviour {
public:
    void FixedUpdate() override {
        auto&& drag = Input::GetMouseDrag();
        auto&& rotate = transform->GetRotation();

        auto&& q = Quaternion(rotate.Radians());
        auto&& rotated = q * Quaternion(FVector3(drag.y / 10, 0, 0).Radians());
        auto&& eulerAngles = rotated.EulerAngles();

        transform->SetRotation(eulerAngles);
    }
};

REGISTER_BEHAVIOUR(CameraUpDownMove)
