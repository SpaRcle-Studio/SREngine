//
// Created by Monika on 19.08.2021.
//

#include <Graphics/Animations/Bone.h>

Framework::Graphics::Animations::BoneComponent::BoneComponent(uint32_t parentId, const glm::mat4& inverseBindPoseMatrix)
        : parentId(parentId), m_inverseBindPoseMatrix(inverseBindPoseMatrix) {
}
