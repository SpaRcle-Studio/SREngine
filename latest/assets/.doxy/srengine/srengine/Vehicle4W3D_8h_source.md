

# File Vehicle4W3D.h

[**File List**](files.md) **>** [**3D**](dir_76fb59f6c477226dc34bbfdd38a2ee7d.md) **>** [**Vehicle4W3D.h**](Vehicle4W3D_8h.md)

[Go to the documentation of this file](Vehicle4W3D_8h.md)


```C++
//
// Created by innerviewer on 2/28/2023.
//

#ifndef SR_ENGINE_VEHICLE4W3D_H
#define SR_ENGINE_VEHICLE4W3D_H

#include <Physics/Vehicle.h>
#include <Physics/WheelInternalData.h>

namespace SR_PTYPES_NS {
    class Vehicle4W3D : public Vehicle {
        using Super = Vehicle;
        SR_CLASS()
    public:
        using WheelsData = WheelInternalData[4];

    public:
        SR_NODISCARD WheelsData& GetWheelsData() { return m_wheelsData; }
        SR_NODISCARD void* GetHandle() const noexcept override { return nullptr; }

    private:
        WheelsData m_wheelsData;
    };
}

#endif //SR_ENGINE_VEHICLE4W3D_H
```


