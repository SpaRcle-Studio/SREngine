//
// Created by mantsurov-n on 04.12.2021.
//

#include <World/Observer.h>
#include <Debug.h>

using namespace Framework::Helper::Math;

#define SR_OFFSET(result, offset)                                                 \
    if (offset != 0) {                                                            \
        if ((offset >= result && result > 0) || (offset <= result && result < 0)) \
            result += static_cast<Math::Unit>(result) / abs(result);              \
        else if (result == 0)                                                     \
            result += static_cast<Math::Unit>(offset) / abs(offset);              \
    }

FVector3 Framework::Helper::World::AddOffset(const FVector3 &chunk, const FVector3 &offset) {
    auto result = chunk + offset;

    SR_OFFSET(result.x, offset.x);
    SR_OFFSET(result.y, offset.y);
    SR_OFFSET(result.z, offset.z);

    return result;
}

IVector2 Framework::Helper::World::AddOffset(const IVector2 &region, const IVector2 &offset) {
    return AddOffset(region.Cast<Math::Unit>(), offset).Cast<int32_t>();
}

FVector2 Framework::Helper::World::AddOffset(const FVector2 &region, const IVector2 &offset) {
    auto result = region + offset;

    SR_OFFSET(result.x, offset.x);
    SR_OFFSET(result.y, offset.y);

    return result;
}

IVector3 Framework::Helper::World::AddOffset(const IVector3 &chunk, const IVector3 &offset) {
    return AddOffset(chunk.Cast<Math::Unit>(), offset.Cast<Math::Unit>()).Cast<int32_t>();
}

Math::Unit Framework::Helper::World::AddOffset(const Unit &value, const Unit &offset) {
    if (value == 0 && offset == 0)
        return 0;

    auto result = value + offset;

    SR_OFFSET(result, offset);

    return result;
}

Math::IVector3 Framework::Helper::World::MakeChunk(const IVector3 &rawChunkPos, int32_t width) {
    Math::IVector3 chunk = rawChunkPos;

    if (abs(chunk.x) > width) chunk.x %= width;
    if (abs(chunk.z) > width) chunk.z %= width;

    if (chunk.x == 0)
        chunk.x = rawChunkPos.x > 0 ? width : 1;
    else
        chunk.x = chunk.x > 0 ? chunk.x : width - (abs(chunk.x) - 1);

    if (chunk.z == 0)
        chunk.z = rawChunkPos.z > 0 ? width : 1;
    else
        chunk.z = chunk.z > 0 ? chunk.z : width - (abs(chunk.z) - 1);

    return chunk;
}

void Framework::Helper::World::Observer::SetChunk(IVector3 chunk) {
    m_chunk = MakeChunk(chunk, m_regionWidth);
}

void Framework::Helper::World::Observer::Move(const IVector2 &value) {
    m_region += value;

    if (m_region.x == 0)
        m_region.x = -(value.x / abs(value.x));

    if (m_region.y == 0)
        m_region.y = -(value.y / abs(value.y));
}

void Framework::Helper::World::Observer::SetWorldMetrics(const IVector2 &chunkSize, int32_t regionWidth) {
    m_chunkSize = chunkSize;
    m_regionWidth = regionWidth;
}

Framework::Helper::World::Observer::Observer(const Types::SafePtr<Scene>& scene)
    : m_regionWidth(0)
    , m_shiftDistance(0)
    , m_scope(0)
    , m_scene(scene)
{ }

Offset Observer::MathNeighbour(const IVector3 &offset) {
    Math::IVector2 region;

    if (offset.x >= 0)
        region.x = (m_chunk.x - 1) + offset.x;
    else
        region.x = (m_chunk.x - m_regionWidth) + offset.x;

    if (offset.z >= 0)
        region.y = (m_chunk.z - 1) + offset.z;
    else
        region.y = (m_chunk.z - m_regionWidth) + offset.z;

    const auto chunk = AddOffset(m_chunk, offset);
    return { AddOffset(m_region, region / m_regionWidth), MakeChunk(chunk, m_regionWidth) };
}

