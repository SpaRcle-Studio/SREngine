//
// Created by Monika on 26.12.2022.
//

#include <Utils/ECS/TransformZero.h>

namespace SR_UTILS_NS {
    Transform *TransformZero::Copy() const {
        return new TransformZero();
    }
}