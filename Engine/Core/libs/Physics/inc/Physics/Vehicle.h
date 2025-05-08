//
// Created by innerviewer on 2/28/2023.
//

#ifndef SR_ENGINE_VEHICLE_H
#define SR_ENGINE_VEHICLE_H

#include <Physics/macros.h>

#include <Physics/PhysicsLib.h>
#include <Physics/VehicleInternalData.h>

#include <Utils/ECS/Component.h>
#include <Utils/Common/Measurement.h>
#include <Utils/Types/SafePointer.h>

namespace SR_PTYPES_NS {
    /// @category(Physics)
    class Vehicle : public SR_UTILS_NS::Component {
        SR_CLASS()
    protected:
        using Super = SR_UTILS_NS::Component;
        using LibraryPtr = SR_PHYSICS_NS::LibraryImpl*;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;

    public:
        SR_NODISCARD virtual SR_UTILS_NS::Measurement GetMeasurement() const;
        SR_NODISCARD VehicleInternalData& GetVehicleData() { return m_internalData; }
        SR_NODISCARD virtual void* GetHandle() const noexcept = 0;
        virtual bool InitVehicle();

        void OnDestroy() override;

    private:
        VehicleInternalData m_internalData;

    };
}

#endif //SR_ENGINE_VEHICLE_H
