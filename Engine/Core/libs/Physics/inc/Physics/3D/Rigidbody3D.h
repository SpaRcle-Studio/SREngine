//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_RIGIDBODY3D_H
#define SRENGINE_RIGIDBODY3D_H

#include <Physics/Rigidbody.h>

namespace SR_PTYPES_NS {
    class Rigidbody3D : public Rigidbody {
        using Super = Rigidbody;
    public:
        explicit Rigidbody3D(LibraryPtr pLibrary);
        ~Rigidbody3D() override = default;

    public:
        static ComponentPtr LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_NODISCARD SR_UTILS_NS::Measurement GetMeasurement() const override;

    };
}

#endif //SRENGINE_RIGIDBODY3D_H
