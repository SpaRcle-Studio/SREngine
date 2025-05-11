

# File Vehicle.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**Vehicle.h**](Vehicle_8h.md)

[Go to the documentation of this file](Vehicle_8h.md)


```C++
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
```


