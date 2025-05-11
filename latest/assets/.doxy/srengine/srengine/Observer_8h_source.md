

# File Observer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**World**](dir_f9b81563eac22e028fcfaca03fb9246b.md) **>** [**Observer.h**](Observer_8h.md)

[Go to the documentation of this file](Observer_8h.md)


```C++
//
// Created by mantsurov-n on 03.12.2021.
//

#ifndef SR_ENGINE_OBSERVER_H
#define SR_ENGINE_OBSERVER_H

#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Common/StringFormat.h>
#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
    class GameObject;
    class SceneObject;
}

namespace SR_WORLD_NS {
    class Scene;

    struct SR_COMMON_DLL_API Offset {
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
            return SR_FORMAT("[ Region: {}, Chunk: {} ]", m_region.ToString().c_str(), m_chunk.ToString().c_str());
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

    class SR_COMMON_DLL_API Observer : public NonCopyable {
        using GameObjectPtr = SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::SceneObject>;
        using ScenePtr = SR_HTYPES_NS::SharedPtr<Scene>;
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
        Offset MathNeighbour(const Math::IVector3& offset) const;
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

    SR_COMMON_DLL_API Math::IVector3 MakeChunk(const Math::IVector3& rawChunkPos, int32_t width);
    SR_COMMON_DLL_API Math::Unit AddOffset(const Math::Unit& value, const Math::Unit& offset);
    SR_COMMON_DLL_API Math::FVector3 AddOffset(const Math::FVector3& chunk, const Math::FVector3& offset);
    SR_COMMON_DLL_API Math::IVector3 AddOffset(const Math::IVector3& chunk, const Math::IVector3& offset);
    SR_COMMON_DLL_API Math::FVector3 AddOffset(const Math::FVector3& region, const Math::IVector3& offset);
}

#endif //SR_ENGINE_OBSERVER_H
```


