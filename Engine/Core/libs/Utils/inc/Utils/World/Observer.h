//
// Created by mantsurov-n on 03.12.2021.
//

#ifndef GAMEENGINE_OBSERVER_H
#define GAMEENGINE_OBSERVER_H

#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
    class GameObject;
}

namespace SR_WORLD_NS {
    class Scene;

    struct SR_DLL_EXPORT Offset {
        Offset(const SR_MATH_NS::IVector3& region, const SR_MATH_NS::IVector3& chunk)
            : m_region(region)
            , m_chunk(chunk)
        { }

        Offset()
            : Offset(SR_MATH_NS::IVector3::Zero(), SR_MATH_NS::IVector3::Zero())
        { }

        SR_NODISCARD SR_MATH_NS::IVector3 GetRegion() const noexcept { return m_region; }
        SR_NODISCARD SR_MATH_NS::IVector3 GetChunk() const noexcept { return m_chunk; }

        SR_NODISCARD std::string ToString() const {
            return SR_UTILS_NS::Format("{ Region: %s, Chunk: %s }", m_region.ToString().c_str(), m_chunk.ToString().c_str());
        }

        SR_NODISCARD bool Empty() const { return m_region.Empty() && m_chunk.Empty(); }

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

    class SR_DLL_EXPORT Observer : public NonCopyable {
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::GameObject>;
        using ScenePtr = SR_HTYPES_NS::SafePtr<Scene>;
    public:
        explicit Observer(const ScenePtr& scene);
        ~Observer() override = default;

    public:
        void SetTarget(const GameObjectPtr& target);
        void SetChunk(Math::IVector3 chunk);
        void MoveRegion(const Math::IVector3& value);
        void SetWorldMetrics(const Math::IVector2& chunkSize, int32_t regionWidth);
        void SetScope(int32_t value) { m_scope = value; }
        void SetShiftDist(int32_t value) { m_shiftDistance = value; }
        Offset MathNeighbour(const Math::IVector3& offset);
        Math::IVector3 WorldPosToChunkPos(const Math::FVector3& position);

        SR_NODISCARD int32_t GetScope() const noexcept { return m_scope; }
        SR_NODISCARD bool HasTarget() const noexcept { return m_target; }

        SR_NODISCARD SR_MATH_NS::IVector3 GetChunk() const noexcept { return m_chunk; }
        SR_NODISCARD SR_MATH_NS::IVector3 GetRegion() const noexcept { return m_region; }

        SR_NODISCARD SR_MATH_NS::IVector2 GetChunkSize() const noexcept { return m_chunkSize; }
        SR_NODISCARD int32_t GetRegionSize() const noexcept { return m_regionWidth; }

    public:
        SR_MATH_NS::IVector2 m_chunkSize;
        int32_t m_regionWidth;
        int32_t m_shiftDistance;
        int32_t m_scope;

        SR_MATH_NS::IVector3 m_region;
        SR_MATH_NS::IVector3 m_lastRegion;

        SR_MATH_NS::IVector3 m_chunk;
        SR_MATH_NS::IVector3 m_lastChunk;

        Offset m_offset;

        ScenePtr m_scene;

        SR_MATH_NS::FVector3 m_targetPosition;
        GameObjectPtr m_target;
    };

    SR_DLL_EXPORT Math::IVector3 MakeChunk(const Math::IVector3& rawChunkPos, int32_t width);
    SR_DLL_EXPORT Math::Unit AddOffset(const Math::Unit& value, const Math::Unit& offset);
    SR_DLL_EXPORT Math::FVector3 AddOffset(const Math::FVector3& chunk, const Math::FVector3& offset);
    SR_DLL_EXPORT Math::IVector3 AddOffset(const Math::IVector3& chunk, const Math::IVector3& offset);
    SR_DLL_EXPORT Math::FVector3 AddOffset(const Math::FVector3& region, const Math::IVector3& offset);
}

#endif //GAMEENGINE_OBSERVER_H
