//
// Created by Monika on 13.06.2022.
//

#ifndef SR_ENGINE_CAMERADATA_H
#define SR_ENGINE_CAMERADATA_H

#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Types/Marshal.h>
#include <Utils/ECS/ISavable.h>

namespace SR_WORLD_NS {
    class SR_DLL_EXPORT CameraData : public NonCopyable {
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
