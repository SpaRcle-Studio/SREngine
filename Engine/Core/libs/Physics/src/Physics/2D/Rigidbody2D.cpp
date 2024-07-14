//
// Created by Monika on 27.11.2022.
//

#include <Physics/2D/Rigidbody2D.h>

namespace SR_PTYPES_NS {
    SR_UTILS_NS::Measurement Rigidbody2D::GetMeasurement() const {
        return SR_UTILS_NS::Measurement::Space2D;
    }
}
