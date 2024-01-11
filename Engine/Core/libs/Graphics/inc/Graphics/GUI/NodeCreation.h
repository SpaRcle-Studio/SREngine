//
// Created by Monika on 15.08.2023.
//

#ifndef SR_ENGINE_NODECREATION_H
#define SR_ENGINE_NODECREATION_H

#include <Utils/Math/Vector2.h>
#include <Utils/Common/Hashes.h>

namespace SR_GRAPH_GUI_NS {
    class NodeWidget;
    class Node;

    Node* CreateNode(const SR_MATH_NS::FVector2& pos, uint64_t identifier);
}

#endif //SR_ENGINE_NODECREATION_H
