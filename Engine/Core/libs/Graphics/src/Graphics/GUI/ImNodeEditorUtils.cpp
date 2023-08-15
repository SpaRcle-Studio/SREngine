//
// Created by Monika on 14.01.2023.
//

#include <Graphics/GUI/ImNodeEditorUtils.h>

namespace SR_GRAPH_GUI_NS {
    bool IsPinsCompatible(PinType first, PinType second) {
        if (first == PinType::Numeric) {
            if (second == PinType::Float || second == PinType::Int) {
                return true;
            }
        }

        if (second == PinType::Numeric) {
            if (first == PinType::Float || first == PinType::Int) {
                return true;
            }
        }

        return first == second;
    }

    bool CanCreateLink(Pin *a, Pin *b) {
        if (!a || !b || a == b) {
            return false;
        }

        if (a->GetKind() == b->GetKind()) {
            return false;
        }

        if (!IsPinsCompatible(a->GetType(), b->GetType())) {
            return false;
        }

        if (a->IsLinked(b) || b->IsLinked(a)) {
            return false;
        }

        if (!a->CanLink() || !b->CanLink()) {
            return false;
        }

        return a->GetNode() != b->GetNode();
    }
}