//
// Created by mantsurov-n on 03.12.2021.
//

#ifndef GAMEENGINE_OBSERVER_H
#define GAMEENGINE_OBSERVER_H

#include <Types/SafePointer.h>
#include <Math/Vector3.h>
#include <Utils/StringFormat.h>

namespace Framework::Helper {
    class GameObject;
}

namespace Framework::Helper::World {
    class Scene;

    struct Offset {
        Offset(const Math::IVector3& region, const Math::IVector3& chunk)
            : m_region(region)
            , m_chunk(chunk)
        { }

        Offset()
            : Offset(Math::IVector3::Zero(), Math::IVector3::Zero())
        { }

        [[nodiscard]] std::string ToString() const {
            return Helper::Format("{ Region: %s, Chunk: %s }", m_region.ToString().c_str(), m_chunk.ToString().c_str());
        }

        [[nodiscard]] bool Empty() const { return m_region.Empty() && m_chunk.Empty(); }

        SR_FORCE_INLINE bool operator==(const Offset &p_v) const {
            return m_chunk == p_v.m_chunk && m_region == p_v.m_region;
        }

        SR_FORCE_INLINE bool operator!=(const Offset &p_v) const {
            return m_chunk != p_v.m_chunk || m_region != p_v.m_region;
        }

        SR_FORCE_INLINE Offset operator-(const Offset &p_v) const {
            return Offset(m_region - p_v.m_region, m_chunk - p_v.m_chunk);
        }

        Math::IVector3 m_region;
        Math::IVector3 m_chunk;
    };

    class Observer {
    public:
        Observer(const Types::SafePtr<Scene>& scene);

    public:
        void SetChunk(Math::IVector3 chunk);
        void MoveRegion(const Math::IVector3& value);
        void SetWorldMetrics(const Math::IVector2& chunkSize, int32_t regionWidth);
        void SetScope(int32_t value) { m_scope = value; }
        void SetShiftDist(int32_t value) { m_shiftDistance = value; }
        Offset MathNeighbour(const Math::IVector3& offset);
        Math::IVector3 WorldPosToChunkPos(const Math::FVector3& position);

        [[nodiscard]] int32_t GetScope() const { return m_scope; }

        [[nodiscard]] Types::SafePtr<Scene> GetScene() const { return m_scene; }

    public:
        Math::IVector2 m_chunkSize;
        int32_t m_regionWidth;
        int32_t m_shiftDistance;
        int32_t m_scope;

        Math::IVector3 m_region;
        Math::IVector3 m_lastRegion;

        Math::IVector3 m_chunk;
        Math::IVector3 m_lastChunk;

        Offset m_offset;

        Types::SafePtr<Scene> m_scene;
        Types::SafePtr<Helper::GameObject> m_target;
    };

    Math::IVector3 MakeChunk(const Math::IVector3& rawChunkPos, int32_t width);
    Math::Unit AddOffset(const Math::Unit& value, const Math::Unit& offset);
    Math::FVector3 AddOffset(const Math::FVector3& chunk, const Math::FVector3& offset);
    Math::IVector3 AddOffset(const Math::IVector3& chunk, const Math::IVector3& offset);
    Math::FVector3 AddOffset(const Math::FVector3& region, const Math::IVector3& offset);
}

#endif //GAMEENGINE_OBSERVER_H
