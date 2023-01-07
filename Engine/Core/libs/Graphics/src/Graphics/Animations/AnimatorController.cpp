//
// Created by Monika on 07.01.2023.
//

#include <Graphics/Animations/AnimatorController.h>

namespace SR_ANIMATIONS_NS {
    SR_UTILS_NS::Component* AnimatorController::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        auto&& pController = new AnimatorController();
        return pController;
    }

    SR_UTILS_NS::Component *AnimatorController::CopyComponent() const {
        return Super ::CopyComponent();
    }

    SR_HTYPES_NS::Marshal::Ptr AnimatorController::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        return Super::Save(pMarshal, flags);
    }

    void AnimatorController::OnAttached() {
        Super::OnAttached();
    }

    void AnimatorController::OnDestroy() {
        Super::OnDestroy();
    }

    void AnimatorController::OnEnable() {
        Super::OnEnable();
    }

    void AnimatorController::OnDisable() {
        Super::OnDisable();
    }
}