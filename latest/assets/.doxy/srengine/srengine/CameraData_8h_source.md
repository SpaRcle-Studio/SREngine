

# File CameraData.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**CameraData.h**](CameraData_8h.md)

[Go to the documentation of this file](CameraData_8h.md)


```C++
//
// Created by Monika on 13.06.2022.
//

#ifndef SR_ENGINE_CAMERADATA_H
#define SR_ENGINE_CAMERADATA_H

#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/Marshal.h>

namespace SR_WORLD_NS {
    class SR_COMMON_DLL_API CameraData : public NonCopyable {
        ~CameraData() override = default;
    public:
        static CameraData* Load(SR_HTYPES_NS::Marshal& marshal) {
            auto&& cameraData = new CameraData();

            cameraData->m_region = marshal.Read<SR_MATH_NS::IVector2>();
            cameraData->m_regionOffset = marshal.Read<SR_MATH_NS::IVector2>();

            cameraData->m_chunk = marshal.Read<SR_MATH_NS::IVector3>();
            cameraData->m_chunkOffset = marshal.Read<SR_MATH_NS::IVector3>();

            cameraData->m_position = marshal.Read<SR_MATH_NS::FVector3>();

            return cameraData;
        }

        SR_NODISCARD SR_HTYPES_NS::Marshal Save() const {
            SR_HTYPES_NS::Marshal marshal;

            marshal.Write(m_region);
            marshal.Write(m_regionOffset);

            marshal.Write(m_chunk);
            marshal.Write(m_chunkOffset);

            marshal.Write(m_position);

            return marshal;
        }

    public:
        SR_MATH_NS::IVector2 m_region;
        SR_MATH_NS::IVector2 m_regionOffset;
        SR_MATH_NS::IVector3 m_chunk;
        SR_MATH_NS::IVector3 m_chunkOffset;
        SR_MATH_NS::FVector3 m_position;

    };
}

#endif //SR_ENGINE_CAMERADATA_H
```


