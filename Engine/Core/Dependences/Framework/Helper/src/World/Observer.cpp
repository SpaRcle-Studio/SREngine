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

    /*if (offset.x != 0) {
        if (offset.x >= result.x && result.x > 0)
            result.x += static_cast<Math::Unit>(result.x) / abs(result.x);

        if (offset.x <= result.x && result.x < 0)
            result.x += static_cast<Math::Unit>(result.x) / abs(result.x);

        if (result.x == 0)
            result.x += static_cast<Math::Unit>(offset.x) / abs(offset.x);
    }*/

    SR_OFFSET(result.x, offset.x);
    SR_OFFSET(result.y, offset.y);
    SR_OFFSET(result.z, offset.z);

    SRAssert(!result.HasZero())

    return result;
}

IVector2 Framework::Helper::World::AddOffset(const IVector2 &region, const IVector2 &offset) {
    return AddOffset(region.Cast<Math::Unit>(), offset).Cast<int32_t>();
}

FVector2 Framework::Helper::World::AddOffset(const FVector2 &region, const IVector2 &offset) {
    auto result = region + offset;

    SR_OFFSET(result.x, offset.x);
    SR_OFFSET(result.y, offset.y);

    /*if (offset.x != 0 && result.x == 0) {
        result.x += static_cast<Math::Unit>(offset.x) / abs(offset.x);
    }

    if (offset.y != 0 && result.y == 0) {
        result.y += static_cast<Math::Unit>(offset.y) / abs(offset.y);
    }*/

    SRAssert(!result.HasZero())

    return result;
}

IVector3 Framework::Helper::World::AddOffset(const IVector3 &chunk, const IVector3 &offset) {
    return AddOffset(chunk.Cast<Math::Unit>(), offset.Cast<Math::Unit>()).Cast<int32_t>();
}

void Framework::Helper::World::Observer::SetChunk(const IVector3 &chunk) {
    m_chunk = chunk;

    if (abs(m_chunk.x) > m_regionWidth)
        m_chunk.x %= m_regionWidth;

    if (abs(m_chunk.z) > m_regionWidth)
        m_chunk.z %= m_regionWidth;

    if (m_chunk.x == 0)
        m_chunk.x = m_regionWidth * (m_region.x / abs(m_region.x));

    if (m_chunk.z == 0)
        m_chunk.z = m_regionWidth * (m_region.y / abs(m_region.y));
}

void Framework::Helper::World::Observer::Move(const IVector2 &region) {
    m_region += region;

    if (m_region.x == 0)
        m_region.x = -(region.x / abs(region.x));

    if (m_region.y == 0)
        m_region.y = -(region.y / abs(region.y));
}

void Framework::Helper::World::Observer::SetWorldMetrics(const IVector2 &chunkSize, int32_t regionWidth) {
    m_chunkSize = chunkSize;
    m_regionWidth = regionWidth;
}
