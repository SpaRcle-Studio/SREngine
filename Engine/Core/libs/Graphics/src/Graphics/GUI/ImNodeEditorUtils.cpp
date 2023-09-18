//
// Created by Monika on 14.01.2023.
//

#include <Graphics/GUI/ImNodeEditorUtils.h>

namespace SR_GRAPH_GUI_NS {
    bool IsPinsCompatible(Pin* a, Pin* b) {
        if (a->GetType() != b->GetType()) {
            return false;
        }

        switch (a->GetType()) {
            case SR_SRLM_NS::DataTypeClass::Array:
            case SR_SRLM_NS::DataTypeClass::Struct:
                if (a->GetDataType()->GetMeta() != b->GetDataType()->GetMeta()) {
                    return false;
                }
                break;
            default:
                break;
        }

        return true;
    }

    bool CanCreateLink(Pin* a, Pin* b) {
        if (!a || !b || a == b) {
            return false;
        }

        if (!a->GetDataType() || !b->GetDataType()) {
            return false;
        }

        if (a->GetKind() == b->GetKind()) {
            return false;
        }

        if (!IsPinsCompatible(a, b)) {
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