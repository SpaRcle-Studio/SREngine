//
// Created by Monika on 14.01.2023.
//

#include <Graphics/GUI/ImNodeEditorUtils.h>

namespace SR_GRAPH_NS::GUI {
    bool CanCreateLink(Pin *a, Pin *b) {
        if (!a || !b || a == b)
            return false;

        if (a->GetKind() == b->GetKind()) {
            return false;
        }

        if (a->GetType() != b->GetType()) {
            return false;
        }

        return a->GetNode() != b->GetNode();
    }
}