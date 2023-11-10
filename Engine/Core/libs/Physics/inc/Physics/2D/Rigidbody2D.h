//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_RIGIDBODY2D_H
#define SRENGINE_RIGIDBODY2D_H

#include <Physics/Rigidbody.h>

namespace SR_PTYPES_NS {
    class Rigidbody2DImpl : public RigidbodyImpl {

    };

    class Rigidbody2D : public Rigidbody {
        using Super = Rigidbody;
        SR_ENTITY_SET_VERSION(1006);
        SR_INITIALIZE_COMPONENT(Rigidbody2D);
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_NODISCARD SR_UTILS_NS::Measurement GetMeasurement() const override;

    };
}

#endif //SRENGINE_RIGIDBODY2D_H
