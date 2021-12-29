//
// Created by mantsurov-n on 03.12.2021.
//

#ifndef GAMEENGINE_OBSERVER_H
#define GAMEENGINE_OBSERVER_H

#include <Types/SafePointer.h>
#include <Math/Vector3.h>

namespace Framework::Helper {
    class GameObject;
}

namespace Framework::Helper::World {
    struct Offset {
        Offset(const Math::IVector2& region, const Math::IVector3& chunk)
                : m_region(region)
                , m_chunk(chunk) { }

        Offset() : Offset({ 0, 0 }, { 0, 0, 0 }) { }

        [[nodiscard]] bool Empty() const { return m_region.Empty() && m_chunk.Empty(); }

        _FORCE_INLINE_ bool operator==(const Offset &p_v) const {
            return m_chunk == p_v.m_chunk && m_region == p_v.m_region;
        }

        _FORCE_INLINE_ bool operator!=(const Offset &p_v) const {
            return m_chunk != p_v.m_chunk || m_region != p_v.m_region;
        }

        _FORCE_INLINE_ Offset operator-(const Offset &p_v) const {
            return Offset(m_region - p_v.m_region, m_chunk - p_v.m_chunk);
        }

        Math::IVector2 m_region;
        Math::IVector3 m_chunk;
    };

    struct Observer {
    public:
        void SetChunk(const Math::IVector3& chunk);
        void Move(const Math::IVector2& region);
        void SetWorldMetrics(const Math::IVector2& chunkSize, int32_t regionWidth);

    public:
        Math::IVector2 m_chunkSize;
        int32_t m_regionWidth;

        Math::IVector2 m_region;
        Math::IVector2 m_lastRegion;

        Math::IVector3 m_chunk;
        Math::IVector3 m_lastChunk;

        Offset m_offset;

        Types::SafePtr<Helper::GameObject> m_target;
    };

    Math::FVector3 AddOffset(const Math::FVector3& chunk, const Math::FVector3& offset);
    Math::IVector3 AddOffset(const Math::IVector3& chunk, const Math::IVector3& offset);
    Math::IVector2 AddOffset(const Math::IVector2& region, const Math::IVector2& offset);
    Math::FVector2 AddOffset(const Math::FVector2& region, const Math::IVector2& offset);
}

#endif //GAMEENGINE_OBSERVER_H
