//
// Created by Igor on 07/12/2022.
//

#ifndef SRENGINE_ANIMATIONPOSE_H
#define SRENGINE_ANIMATIONPOSE_H

#include <Graphics/Animations/Bone.h>

namespace SR_ANIMATIONS_NS {
    struct AnimationMatrixPalette {
        explicit AnimationMatrixPalette(std::vector<glm::mat4> bonesTransforms)
                : bonesTransforms(std::move(bonesTransforms))
        {

        }

        std::vector<glm::mat4> bonesTransforms;
    };

    class AnimationPose {
    public:
        AnimationPose(const AssimpSkeleton* skeleton,
                      const std::vector <BonePose> &bonesPoses)
                : m_skeleton(skeleton),
                  bonesLocalPoses(bonesPoses),
                  m_matrixPalette(std::vector<glm::mat4>(bonesPoses.size(), glm::identity<glm::mat4>())) {

        }

        [[nodiscard]] const AnimationMatrixPalette &getMatrixPalette() const {
            m_matrixPalette.bonesTransforms[0] = bonesLocalPoses[0].getBoneMatrix();

            auto bonesCount = static_cast<uint8_t>(m_matrixPalette.bonesTransforms.size());

            for (uint8_t boneIndex = 1; boneIndex < bonesCount; boneIndex++) {
                m_matrixPalette.bonesTransforms[boneIndex] =
                        m_matrixPalette.bonesTransforms[m_skeleton->bones[boneIndex].parentId] *
                        bonesLocalPoses[boneIndex].getBoneMatrix();
            }

            for (uint8_t boneIndex = 0; boneIndex < bonesCount; boneIndex++) {
                m_matrixPalette.bonesTransforms[boneIndex] *= m_skeleton->bones[boneIndex].inverseBindPoseMatrix;
            }

            return m_matrixPalette;
        }

    public:
        std::vector <BonePose> bonesLocalPoses;

    private:
        const AssimpSkeleton* m_skeleton;
        mutable AnimationMatrixPalette m_matrixPalette;
    };
}


#endif //SRENGINE_ANIMATIONPOSE_H
