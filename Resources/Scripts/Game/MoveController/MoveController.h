//
// Created by Monika on 24.05.2022.
//

#ifndef SRENGINE_MOVECONTROLLER_H
#define SRENGINE_MOVECONTROLLER_H

#include "../Libraries/Behaviour.h"

class MoveController : public Behaviour {
public:
    ~MoveController() override = default;

public:
    void Update() override {

    }
};

REGISTER_BEHAVIOUR(MoveController)

#endif //SRENGINE_MOVECONTROLLER_H
