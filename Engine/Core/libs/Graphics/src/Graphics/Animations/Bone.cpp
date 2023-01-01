//
// Created by Monika on 19.08.2021.
//

#include <Graphics/Animations/Bone.h>

Framework::Graphics::Animations::Bone::Bone(uint8_t parentId, const glm::mat4& inverseBindPoseMatrix)
        : parentId(parentId), inverseBindPoseMatrix(inverseBindPoseMatrix) {
    SR_UTILS_NS::Component::InitComponent<Bone>();
}
