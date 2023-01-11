//
// Created by Igor on 08/12/2022.
//

#ifndef SRENGINE_SKELETON_H
#define SRENGINE_SKELETON_H

#include <Graphics/Animations/Bone.h>

namespace SR_ANIMATIONS_NS {

    struct SR_DEPRECATED AssimpSkeleton {
        std::vector<Bone> bones;
    };

}

#endif //SRENGINE_SKELETON_H
