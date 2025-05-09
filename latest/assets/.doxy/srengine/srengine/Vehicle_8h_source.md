

# File Vehicle.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**Vehicle.h**](Vehicle_8h.md)

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


