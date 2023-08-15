//
// Created by Monika on 15.08.2023.
//

#ifndef SRENGINE_NODECREATION_H
#define SRENGINE_NODECREATION_H

#include <Utils/Math/Vector2.h>
#include <Utils/Common/Hashes.h>

namespace SR_SRLM_NS {
    static constexpr uint64_t NODE_START_PASS = SR_COMPILE_TIME_CRC32_STR("START_PASS");
    static constexpr uint64_t NODE_END_PASS = SR_COMPILE_TIME_CRC32_STR("END_PASS");
    static constexpr uint64_t NODE_CASCADED_SHADOW_MAP_PASS = SR_COMPILE_TIME_CRC32_STR("CASCADED_SHADOW_MAP_PASS");
    static constexpr uint64_t NODE_FRAME_BUFFER_PASS = SR_COMPILE_TIME_CRC32_STR("FRAME_BUFFER_PASS");
}

namespace SR_GRAPH_GUI_NS {
    class NodeWidget;
    class Node;

    Node* CreateNode(const SR_MATH_NS::FVector2& pos, uint64_t identifier);
}

#endif //SRENGINE_NODECREATION_H
