//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_RIGIDBODY2D_H
#define SR_ENGINE_RIGIDBODY2D_H

#include <Physics/Rigidbody.h>

namespace SR_PTYPES_NS {
    class Rigidbody2DImpl : public RigidbodyImpl {

    };

    /// @category(Physics)
    class Rigidbody2D : public Rigidbody {
        SR_CLASS()
        using Super = Rigidbody;
    public:
        SR_NODISCARD SR_UTILS_NS::Measurement GetMeasurement() const override;

    };
}

#endif //SR_ENGINE_RIGIDBODY2D_H
