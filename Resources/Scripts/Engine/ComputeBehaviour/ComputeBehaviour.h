//
// Created by Monika on 24.05.2022.
//

#ifndef SRENGINE_COMPUTEBEHAVIOUR_H
#define SRENGINE_COMPUTEBEHAVIOUR_H

#include "../Libraries/Behaviour.h"

class ComputeBehaviour : public Behaviour {
public:
    ~ComputeBehaviour() override = default;

public:
    void Update(float_t dt) override {

    }
};

REGISTER_BEHAVIOUR(ComputeBehaviour)

#endif //SRENGINE_COMPUTEBEHAVIOUR_H
