//
// Created by Monika on 24.05.2022.
//

#ifndef SRENGINE_MOVECONTROLLER_H
#define SRENGINE_MOVECONTROLLER_H

#include "../../Libraries/Types/Behaviour.h"

class MoveController : public Behaviour {
public:
    ~MoveController() override = default;

public:
    void Update(float_t dt) override {

    }

private:
    SR_PROPERTY(speed)
    float_t speed;

    SR_PROPERTY(checkbox)
    bool checkbox;

};

REGISTER_BEHAVIOUR(MoveController)

#endif //SRENGINE_MOVECONTROLLER_H
