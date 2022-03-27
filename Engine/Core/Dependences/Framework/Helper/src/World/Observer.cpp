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

IVector3 Framework::Helper::World::AddOffset(const IVector3 &region, const IVector3 &offset) {
    return AddOffset(region.Cast<Math::Unit>(), offset).Cast<int32_t>();
}

FVector3 Framework::Helper::World::AddOffset(const FVector3 &region, const IVector3 &offset) {
    auto result = region + offset;

    SR_OFFSET(result.x, offset.x);
    SR_OFFSET(result.y, offset.y);
    SR_OFFSET(result.z, offset.z);

    return result;
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

    #define SR_MAKE_CHUNK(value, width, chunk) {                                          \
        Framework::Helper::Math::IVector3 temp = chunk;                                   \
        if (abs(chunk.value) > width) chunk.value %= width;                               \
        if (chunk.value == 0)                                                             \
            chunk.value = temp.value > 0 ? width : 1;                                     \
        else                                                                              \
            chunk.value = chunk.value > 0 ? chunk.value : width - (abs(chunk.value) - 1); \
    }                                                                                     \

    SR_MAKE_CHUNK(x, width, chunk);
    SR_MAKE_CHUNK(y, width, chunk);
    SR_MAKE_CHUNK(z, width, chunk);

    return chunk;
}

void Framework::Helper::World::Observer::SetChunk(IVector3 chunk) {
    m_chunk = MakeChunk(chunk, m_regionWidth);
}

void Framework::Helper::World::Observer::MoveRegion(const IVector3 &value) {
    m_region += value;

    if (m_region.x == 0)
        m_region.x = -(value.x / abs(value.x));

    if (m_region.y == 0)
        m_region.y = -(value.y / abs(value.y));

    if (m_region.z == 0)
        m_region.z = -(value.z / abs(value.z));
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
    Math::IVector3 region;

    /*if (offset.x >= 0)
        region.x = (m_chunk.x - 1) + offset.x;
    else
        region.x = (m_chunk.x - m_regionWidth) + offset.x;

    if (offset.z >= 0)
        region.y = (m_chunk.z - 1) + offset.z;
    else
        region.y = (m_chunk.z - m_regionWidth) + offset.z;*/

    #define SR_REGION_NEIGHBOUR(chunk, region, width, offset, value) \
        if (offset.value >= 0)                                       \
            region.value = (chunk.value - 1) + offset.value;         \
        else                                                         \
            region.value = (chunk.value - width) + offset.value;     \

    SR_REGION_NEIGHBOUR(m_chunk, region, m_regionWidth, offset, x);
    SR_REGION_NEIGHBOUR(m_chunk, region, m_regionWidth, offset, y);
    SR_REGION_NEIGHBOUR(m_chunk, region, m_regionWidth, offset, z);

    const auto chunk = AddOffset(m_chunk, offset);
    return Offset(
            AddOffset(m_region, region / m_regionWidth),
            MakeChunk(chunk, m_regionWidth)
    );
}

Math::IVector3 Observer::WorldPosToChunkPos(const Math::FVector3& position) {
    const auto chunkSize = Math::IVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x);

    return AddOffset(
            position.Singular(Math::FVector3(m_chunkSize.x, m_chunkSize.y, m_chunkSize.x)).Cast<int>() / chunkSize,
            m_offset.m_chunk
    );
}

