//
// Created by Monika on 23.08.2022.
//

#ifndef SRENGINE_TRANSFORMZERO_H
#define SRENGINE_TRANSFORMZERO_H

#include <Utils/ECS/Transform.h>

namespace SR_UTILS_NS {
    class GameObject;

    class SR_DLL_EXPORT TransformZero : public Transform {
    friend class GameObject;
    public:
        ~TransformZero() override = default;

    public:
        SR_NODISCARD Measurement GetMeasurement() const override { return Measurement::SpaceZero; }

    };
}


#endif //SRENGINE_TRANSFORMZERO_H
