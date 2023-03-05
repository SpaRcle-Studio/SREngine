//
// Created by innerviewer on 2/28/2023.
//

#ifndef SRENGINE_VEHICLE_H
#define SRENGINE_VEHICLE_H

#include <Physics/PhysicsLib.h>

#include <Utils/ECS/Component.h>
#include <Utils/Common/Measurement.h>
#include <Utils/Types/SafePointer.h>

namespace SR_PTYPES_NS {
    class Vehicle : public SR_UTILS_NS::Component {
    protected:
        using Super = SR_UTILS_NS::Component;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        explicit Vehicle(LibraryPtr pLibrary);
        ~Vehicle() override = default;

    public:
        static ComponentPtr LoadComponent(SR_UTILS_NS::Measurement measurement, SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        SR_NODISCARD virtual SR_UTILS_NS::Measurement GetMeasurement() const;

        SR_NODISCARD virtual void* GetHandle() const noexcept = 0;

        virtual bool InitVehicle();
    };
}

#endif //SRENGINE_VEHICLE_H
