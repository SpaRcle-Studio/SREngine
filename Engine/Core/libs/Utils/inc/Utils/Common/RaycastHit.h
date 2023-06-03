//
// Created by innerviewer on 2/13/2023.
//

#ifndef SRENGINE_RAYCASTHIT_H
#define SRENGINE_RAYCASTHIT_H


namespace SR_UTILS_NS {
    struct RaycastHit {
        void* pHandler = nullptr;
        SR_MATH_NS::FVector3 position;
        SR_MATH_NS::FVector3 normal;
        float_t distance;
    };
}

#endif //SRENGINE_RAYCASTHIT_H
